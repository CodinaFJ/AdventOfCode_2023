/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modules_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:07:02 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/20 12:07:02 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

void	print_module(t_module module)
{
	if (module.outputs == NULL)
		return ;
	printf("Module: [%c]%s -> ", module.module_type, module.name);
	for (int i = 0; module.outputs[i] != NULL; i++)
		printf("%s ", module.outputs[i]);
	//print_array((long long *) module.pulse, 10000);
	if (module.module_type == FLIP_FLOP)
		printf("\tFlipFlop State: %d\n", module.ff_state);
	else if (module.module_type == CONJUCTION)
	{
		printf("\nINPUTS");
		print_table(module.cjt_inputs_states);
	}
	else
		printf("\n");
}

void	print_modules(t_module *modules)
{
	printf("\nPRINT MODULES\n...........................................\n");
	for (int i = 0; i < N_MODULES; i++)
	{
		print_module(modules[i]);
	}
	printf("...........................................\n");

}

t_module	*find_module(t_module *modules, char *name)
{
	if (ft_strcmp(name, "output") == 0 || ft_strcmp(name, "rx") == 0)
		return (NULL);
	for(int i = 0; i < N_MODULES; i++)
	{
		if (ft_strcmp(modules[i].name, name) == 0)
			return (&modules[i]);
	}
	printf("\n[ERROR] module not found -> %s\n", name);
	return (NULL);
}

void	add_module(t_module *modules, size_t i, char *str)
{
	char			**strs;
	char			*name;
	char			*output_aux;
	char			**outputs;
	e_module_type	type;

	strs = ft_split(str, '-');
	type = strs[0][0];

	name = ft_strtrim(strs[0], " %&");

	output_aux = ft_strtrim(strs[1], " >\n");
	outputs = ft_split(output_aux, ',');
	free(output_aux);
	for (int i = 0; outputs[i] != NULL; i++)
	{
		output_aux = outputs[i];
		outputs[i] = ft_strtrim(outputs[i], ", ");
		free(output_aux);
	}

	modules[i].name = name;
	modules[i].outputs = outputs;
	modules[i].module_type = type;
	modules[i].pulse = malloc(sizeof(int) * 100000);
	ft_bzero(modules[i].pulse, sizeof(int) * 100000);
	modules[i].pulse_front = 0;
	modules[i].pulse_rear = 0;
	modules[i].ff_state = false;
	modules[i].cjt_inputs_states = NULL;
	if (type == CONJUCTION)
		modules[i].cjt_inputs_states = create_table(HT_CAPACITY);
	free_strs(strs);
}

void	fill_conjuction_inputs(t_module *modules, t_hash_table *modules_types_table, size_t size)
{
	char	*module_name;
	for (size_t n = 0; n < size; n++) //Through all modules
	{
		for (size_t i = 0; modules[n].outputs[i] != NULL; i++) //Through all outputs of a module
		{
			module_name = modules[n].outputs[i];
			if (ft_strcmp(module_name, "rx") == 0 || ft_strcmp(module_name, "output") == 0)
				continue ;
			if (ht_search(modules_types_table, module_name)[0] == CONJUCTION) //Check if outputs to a conjuction
			{
				for (size_t j = 0; j < size; j++) //Search through the modules
				{
					if (ft_strcmp(modules[j].name, module_name) == 0) //Add module n as input of searched module
					{
						ht_insert(modules[j].cjt_inputs_states, modules[n].name, "0");
						break ;
					}
				}
			}
		}
	}
}