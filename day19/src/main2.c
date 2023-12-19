#include "AOC.h"

void	solve_pieces_intervals(t_pieces *tentative_pieces, t_list **accepted_pieces, t_hash_table *ht);

void	print_pieces(t_pieces *pieces)
{
	printf("Piece intervals:  ");
	printf("x [%d\t%d]\t\tm [%d\t%d]\t\ta [%d\t%d]\t\ts [%d\t%d]\n", pieces->x1, pieces->x2, pieces->m1, pieces->m2, pieces->a1, pieces->a2, pieces->s1, pieces->s2);
	//printf("Workflow: %s\n", pieces->workflow);
}

long long	calc_combs_pieces(t_pieces *pieces)
{
	long long res = 1;

	res *= (pieces->x2 - pieces->x1 + 1);
	res *= (pieces->m2 - pieces->m1 + 1);
	res *= (pieces->a2 - pieces->a1 + 1);
	res *= (pieces->s2 - pieces->s1 + 1);
	return (res);
}

t_pieces	*new_pieces_interval(int x1, int x2, int m1, int m2, int a1, int a2, int s1, int s2)
{
	t_pieces	*new;

	new = malloc(sizeof(t_pieces));
	new->x1 = x1;
	new->x2 = x2;
	new->m1 = m1;
	new->m2 = m2;
	new->a1 = a1;
	new->a2 = a2;
	new->s1 = s1;
	new->s2 = s2;
	new->workflow = malloc(10);
	ft_bzero(new->workflow, 10);
	return (new);
}

en_bool		evaluate_instruction_x(t_pieces *tentative_pieces, char *instruction, t_list **accepted_pieces, t_hash_table *ht)
{
	char		comp;
	long long	instruction_n;
	t_pieces	*new_pieces;

	comp = instruction[1];
	new_pieces = NULL;
	instruction_n = atoll(&instruction[2]);
	if ((comp == '<' && tentative_pieces->x2 < instruction_n) || (comp == '>' && tentative_pieces->x1 > instruction_n)) //Whole interval is in
	{
		ft_strcpy(tentative_pieces->workflow, ft_strchr(instruction, ':') + 1);
		solve_pieces_intervals(tentative_pieces, accepted_pieces, ht);
		return (true);
	}
	else if ((comp == '<' && tentative_pieces->x1 > instruction_n) || (comp == '>' && tentative_pieces->x2 < instruction_n)) //Whole interval is out
		return (false);
	else if (comp == '<') //Left interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, instruction_n - 1, tentative_pieces->m1, tentative_pieces->m2, tentative_pieces->a1, tentative_pieces->a2, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->x1 = instruction_n;
	}
	else if (comp == '>') //Right interval is in
	{
		new_pieces = new_pieces_interval(instruction_n + 1, tentative_pieces->x2, tentative_pieces->m1, tentative_pieces->m2, tentative_pieces->a1, tentative_pieces->a2, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->x2 = instruction_n;
	}
	ft_strcpy(new_pieces->workflow, ft_strchr(instruction, ':') + 1);
	solve_pieces_intervals(new_pieces, accepted_pieces, ht);
	return (false);
}

en_bool		evaluate_instruction_m(t_pieces *tentative_pieces, char *instruction, t_list **accepted_pieces, t_hash_table *ht)
{
	char		comp;
	long long	instruction_n;
	t_pieces	*new_pieces;

	comp = instruction[1];
	new_pieces = NULL;
	instruction_n = atoll(&instruction[2]);
	if ((comp == '<' && tentative_pieces->m2 < instruction_n) || (comp == '>' && tentative_pieces->m1 > instruction_n)) //Whole interval is in
	{
		ft_strcpy(tentative_pieces->workflow, ft_strchr(instruction, ':') + 1);
		solve_pieces_intervals(tentative_pieces, accepted_pieces, ht);
		return (true);
	}
	else if ((comp == '<' && tentative_pieces->m1 > instruction_n) || (comp == '>' && tentative_pieces->m2 < instruction_n)) //Whole interval is out
		return (false);
	else if (comp == '<') //Left interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, tentative_pieces->m1, instruction_n - 1, tentative_pieces->a1, tentative_pieces->a2, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->m1 = instruction_n;
	}
	else if (comp == '>') //Right interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, instruction_n + 1, tentative_pieces->m2, tentative_pieces->a1, tentative_pieces->a2, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->m2 = instruction_n;
	}
	ft_strcpy(new_pieces->workflow, ft_strchr(instruction, ':') + 1);
	solve_pieces_intervals(new_pieces, accepted_pieces, ht);
	return (false);
}

en_bool		evaluate_instruction_a(t_pieces *tentative_pieces, char *instruction, t_list **accepted_pieces, t_hash_table *ht)
{
	char		comp;
	long long	instruction_n;
	t_pieces	*new_pieces;

	comp = instruction[1];
	new_pieces = NULL;
	instruction_n = atoll(&instruction[2]);
	if ((comp == '<' && tentative_pieces->a2 < instruction_n) || (comp == '>' && tentative_pieces->a1 > instruction_n)) //Whole interval is in
	{
		ft_strcpy(tentative_pieces->workflow, ft_strchr(instruction, ':') + 1);
		solve_pieces_intervals(tentative_pieces, accepted_pieces, ht);
		return (true);
	}
	else if ((comp == '<' && tentative_pieces->a1 > instruction_n) || (comp == '>' && tentative_pieces->a2 < instruction_n)) //Whole interval is out
		return (false);
	else if (comp == '<') //Left interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, tentative_pieces->m1, tentative_pieces->m2, tentative_pieces->a1, instruction_n - 1, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->a1 = instruction_n;
	}
	else if (comp == '>') //Right interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, tentative_pieces->m1, tentative_pieces->m2, instruction_n + 1, tentative_pieces->a2, tentative_pieces->s1, tentative_pieces->s2);
		tentative_pieces->a2 = instruction_n;
	}
	ft_strcpy(new_pieces->workflow, ft_strchr(instruction, ':') + 1);
	solve_pieces_intervals(new_pieces, accepted_pieces, ht);
	return (false);
}

en_bool		evaluate_instruction_s(t_pieces *tentative_pieces, char *instruction, t_list **accepted_pieces, t_hash_table *ht)
{
	char		comp;
	long long	instruction_n;
	t_pieces	*new_pieces;

	comp = instruction[1];
	new_pieces = NULL;
	instruction_n = atoll(&instruction[2]);
	if ((comp == '<' && tentative_pieces->s2 < instruction_n) || (comp == '>' && tentative_pieces->s1 > instruction_n)) //Whole interval is in
	{
		ft_strcpy(tentative_pieces->workflow, ft_strchr(instruction, ':') + 1);
		solve_pieces_intervals(tentative_pieces, accepted_pieces, ht);
		return (true);
	}
	else if ((comp == '<' && tentative_pieces->s1 > instruction_n) || (comp == '>' && tentative_pieces->s2 < instruction_n)) //Whole interval is out
		return (false);
	else if (comp == '<') //Left interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, tentative_pieces->m1, tentative_pieces->m2, tentative_pieces->a1, tentative_pieces->a2, tentative_pieces->s1,  instruction_n - 1);
		tentative_pieces->s1 = instruction_n;
	}
	else if (comp == '>') //Right interval is in
	{
		new_pieces = new_pieces_interval(tentative_pieces->x1, tentative_pieces->x2, tentative_pieces->m1, tentative_pieces->m2, tentative_pieces->a1, tentative_pieces->a2, instruction_n + 1, tentative_pieces->s2);
		tentative_pieces->s2 = instruction_n;
	}
	ft_strcpy(new_pieces->workflow, ft_strchr(instruction, ':') + 1);
	solve_pieces_intervals(new_pieces, accepted_pieces, ht);
	return (false);
}

void	send_to_workflow(t_pieces *tentative_pieces, t_list **accepted_pieces, t_hash_table *ht)
{
	if (ft_strcmp(tentative_pieces->workflow, "A") == 0)
	{
		ft_lstadd_back(accepted_pieces, ft_lstnew(tentative_pieces));
		printf("\nAdded\n");
	}
	else if (ft_strcmp(tentative_pieces->workflow, "R") == 0)
		free(tentative_pieces);
	else
		solve_pieces_intervals(tentative_pieces, accepted_pieces, ht);
}

void	solve_pieces_intervals(t_pieces *tentative_pieces, t_list **accepted_pieces, t_hash_table *ht)
{
	char		**instructions;
	char		*aux;

	if (ft_strcmp(tentative_pieces->workflow, "A") == 0 || ft_strcmp(tentative_pieces->workflow, "R") == 0)
	{
		send_to_workflow(tentative_pieces, accepted_pieces, ht);
		return ;
	}
	instructions = ft_split(ht_search(ht, tentative_pieces->workflow), ',');
	print_pieces(tentative_pieces);
	print_strs(instructions);
	for (int i = 0; instructions[i] != NULL; i++)
	{
		printf("Evaluate for: %s\n", instructions[i]);
		aux = ft_strchr(instructions[i], ':');
		if (aux == NULL)
		{
			ft_strcpy(tentative_pieces->workflow, instructions[i]);
			send_to_workflow(tentative_pieces, accepted_pieces, ht);
			break ;
		}
		if (instructions[i][0] == 'x')
		{
			if (evaluate_instruction_x(tentative_pieces, instructions[i], accepted_pieces, ht))
				break ;
		}
		else if (instructions[i][0] == 'm')
		{
			if (evaluate_instruction_m(tentative_pieces, instructions[i], accepted_pieces, ht))
				break ;
		}
		else if (instructions[i][0] == 'a')
		{
			if (evaluate_instruction_a(tentative_pieces, instructions[i], accepted_pieces, ht))
				break ;
		}
		else if (instructions[i][0] == 's')
		{
			if (evaluate_instruction_s(tentative_pieces, instructions[i], accepted_pieces, ht))
				break ;
		}
	}
	free_strs(instructions);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	t_hash_table	*ht;
	t_list			*accepted_pieces;
	t_pieces		*initial_tent_pieces;
	t_pieces		*initial_acc_pieces;
	char			str[SIZE];
	char			*aux;
	char			**strs;
	long long		res = 0;

	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	ht = create_table(SIZE);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		if (str[0] == '\n') break ;
		aux = ft_strtrim(str, "\n}");
		strs = ft_split(aux, '{');
		ht_insert(ht, strs[0], strs[1]);
		free(aux);
		free_strs(strs);
	}
	initial_tent_pieces = new_pieces_interval(1, 4000, 1, 4000, 1, 4000, 1, 4000);
	initial_acc_pieces = new_pieces_interval(0, 0, 0, 0, 0, 0, 0, 0);
	ft_strcpy(initial_tent_pieces->workflow, "in");
	accepted_pieces = ft_lstnew(initial_acc_pieces);
	solve_pieces_intervals(initial_tent_pieces, &accepted_pieces, ht);
	accepted_pieces = accepted_pieces->next;
	while (accepted_pieces != NULL)
	{
		t_pieces	*aux;
		aux = (t_pieces *)accepted_pieces->content;
		print_pieces(aux);
		res += calc_combs_pieces(aux);
		accepted_pieces = accepted_pieces->next;
	}
	printf("Result: %lld\n", res);
	ft_lstclear(&accepted_pieces, free);
	free_htable(ht);
	fclose(f);
	exit (0);
}
