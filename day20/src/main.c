#include "AOC.h"

long long	g_low_pulses = 0;
long long	g_high_pulses = 0;
t_queue		*g_queue;

void	send_pulse(e_pulse pulse, t_module *module_sender, t_module *module_receiver)
{
	if (pulse == LOW)
			g_low_pulses++;
	else
		g_high_pulses++;
	if (module_receiver == NULL)
		return ;
	if (module_receiver->module_type == CONJUCTION)
	{
		char	pulse_c[2] = "";

		if (pulse == HIGH)
			pulse_c[0] = '1';
		else
			pulse_c[0] = '0';
		pulse_c[1] = '\0';
		ht_insert(module_receiver->cjt_inputs_states, module_sender->name, pulse_c);
	}
	if (pulse == HIGH && module_receiver->module_type == FLIP_FLOP)
		return ;
	module_receiver->pulse[module_receiver->pulse_rear] = pulse;
	module_receiver->pulse_rear++;
	enqueue(g_queue, module_receiver->name);
}

void	process_pulse_flip_flop(e_pulse pulse, t_module *module_sender, t_module *modules)
{
	e_pulse 	sending_pulse = NONE;

	if (pulse == HIGH || pulse == NONE)
		return ;
	if (module_sender->ff_state == false)
	{
		sending_pulse = HIGH;
		module_sender->ff_state = true;
	}
	else if (module_sender->ff_state == true)
	{
		sending_pulse = LOW;
		module_sender->ff_state = false;
	}
	for (int i = 0; module_sender->outputs[i] != NULL; i++)
	{
		send_pulse(sending_pulse, module_sender, find_module(modules, module_sender->outputs[i]));
	}
}

en_bool is_input_high(t_module *module_sender)
{
	en_bool	all_high = true;
	size_t	i;
	size_t	bucket = 0;
	t_list	*aux;

	i = 0;
	while (i < module_sender->cjt_inputs_states->size)
	{
		if (module_sender->cjt_inputs_states->items && module_sender->cjt_inputs_states->items[i])
        {
			if (module_sender->cjt_inputs_states->items[i]->value[0] == '0')
				all_high = false;
			aux = module_sender->cjt_inputs_states->overflow_buckets[i];
			bucket = 0;
			while (aux != NULL)
			{
				if (((t_ht_item *)aux->content)->value[0] == '0')
					all_high = false;
				aux = aux->next;
				bucket++;
			}
        }
		i++;
	}
	return (all_high);
}

void	process_pulse_conjuction(e_pulse pulse, t_module *module_sender, t_module *modules)
{
	en_bool	all_high = true;
	e_pulse	sending_pulse = NONE;

	(void) pulse;
	all_high = is_input_high(module_sender);
	if (all_high)
		sending_pulse = LOW;
	else
		sending_pulse = HIGH;
	for (int i = 0; module_sender->outputs[i] != NULL; i++)
		send_pulse(sending_pulse, module_sender, find_module(modules, module_sender->outputs[i]));
}

void	process_pulse_broadcast(e_pulse pulse, t_module *module_sender, t_module *modules)
{
	for (int i = 0; module_sender->outputs[i] != NULL; i++)
		send_pulse(pulse, module_sender, find_module(modules, module_sender->outputs[i]));
}

void	process_pulse(t_module *module_sender, t_module *modules)
{
	e_pulse pulse;

	pulse = module_sender->pulse[module_sender->pulse_front];
	module_sender->pulse_front++;
	if (pulse == NONE)
		return ;
	if (module_sender->module_type == FLIP_FLOP)
		process_pulse_flip_flop(pulse, module_sender, modules);
	else if (module_sender->module_type == CONJUCTION)
		process_pulse_conjuction(pulse, module_sender, modules);
	else if (module_sender->module_type == BROADCAST)
		process_pulse_broadcast(pulse, module_sender, modules);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			**strs;
	long long		res = 0;
	t_module		modules[N_MODULES];
	t_hash_table	*modules_types_table;
	size_t			i = 0;


	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	f = fopen(argv[1], "r");
	modules_types_table = create_table(HT_CAPACITY);
	(void) strs;
	ft_bzero((void *) modules, sizeof(t_module) * N_MODULES);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		add_module((t_module *) modules, i, str);
		ht_insert(modules_types_table, modules[i].name, (char *) &(modules[i].module_type));
		i++;
	}
	fill_conjuction_inputs(modules, modules_types_table, i);
	g_queue = queue_create(200);
	for (int k = 0; k < 1000; k++)
	{
		t_module	*broadcaster_module = find_module((t_module *) modules, "broadcaster");
		broadcaster_module->pulse[broadcaster_module->pulse_rear] = LOW;
		broadcaster_module->pulse_rear++;
		g_low_pulses++;
		enqueue(g_queue, "broadcaster");
		//print_modules(modules);
		while (!queue_is_empty(g_queue))
		{
			char	*name = dequeue(g_queue);
			process_pulse(find_module(modules, name), modules);
			free(name);
		}			
	}
	(void) res;
	printf("Low pulses: %lld | High pulses: %lld | ", g_low_pulses, g_high_pulses);
	printf("Result: %lld\n", g_low_pulses * g_high_pulses);
	//free_queue(g_queue);
	free_htable(modules_types_table);
	fclose(f);
	exit (0);
}
