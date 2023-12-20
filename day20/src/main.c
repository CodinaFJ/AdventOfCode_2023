#include "AOC.h"

long long	g_low_pulses = 0;
long long	g_high_pulses = 0;
int			g_priority_queue = 1;

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
	module_receiver->incoming_pulse = pulse;
	module_receiver->in_priority = g_priority_queue;
	g_priority_queue++;
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
	if (module_sender->send_pulse == NONE)
		return ;
	if (module_sender->module_type == FLIP_FLOP)
		process_pulse_flip_flop(module_sender->send_pulse, module_sender, modules);
	else if (module_sender->module_type == CONJUCTION)
		process_pulse_conjuction(module_sender->send_pulse, module_sender, modules);
	else if (module_sender->module_type == BROADCAST)
		process_pulse_broadcast(module_sender->send_pulse, module_sender, modules);
	module_sender->send_pulse = NONE;
}

void	prepare_for_sending(t_module *module)
{
	if (module->incoming_pulse == NONE)
		return ;
	module->send_pulse = module->incoming_pulse;
	module->incoming_pulse = NONE;
	module->send_priority = module->in_priority;
	module->in_priority = 0;
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
	for (int k = 0; k < 1000; k++)
	{
		//printf("BUTTON!!!\n");
		g_low_pulses++;
		find_module((t_module *) modules, "broadcaster")->send_pulse = LOW;
		find_module((t_module *) modules, "broadcaster")->send_priority = g_priority_queue;
		g_priority_queue++;
		for (i = 0; i < 300; i++)
		{
			//print_modules((t_module *) modules);
			//printf("Low pulses: %lld | High pulses: %lld \n", g_low_pulses, g_high_pulses);
			//print_modules((t_module *) modules);
			int	aux = g_priority_queue;
			g_priority_queue = 1;
			for(int j = 1; j < aux + 1; j++)
			{
				//printf("g_priority: %d\n", g_priority_queue);
				t_module	*module_aux = get_module_priority((t_module *) modules, j);
				if (module_aux == NULL)
					break ;
				process_pulse(module_aux, (t_module *) modules);
			}
			for(int j = 0; j < N_MODULES; j++)
				prepare_for_sending((t_module *) &modules[j]);
			
		}
		//print_modules((t_module *) modules);
		//printf("Low pulses: %lld | High pulses: %lld \n", g_low_pulses, g_high_pulses);
		/*for(int j = 0; j < N_MODULES; j++)
			process_pulse((t_module *) &modules[j], (t_module *) modules);*/
	}
	//print_modules((t_module *) modules);
	(void) res;
	printf("Low pulses: %lld | High pulses: %lld | ", g_low_pulses, g_high_pulses);
	printf("Result: %lld\n", g_low_pulses * g_high_pulses);
	free_htable(modules_types_table);
	fclose(f);
	exit (0);
}
