#include "AOC.h"

long long	solve_piece(t_hash_table *ht, char **piece, char *workflow);

long long	calculate_piece_value(char **piece)
{
	long long	res = 0;

	for (int i = 0; i < 4; i++)
	{
		res += atoll(&piece[i][2]);	
	}
	return (res);
}

long long	send_to_workflow(t_hash_table *ht, char **piece, char *workflow)
{
	if (ft_strcmp(workflow, "R") == 0)
		return (0);
	else if (ft_strcmp(workflow, "A") == 0)
		return (calculate_piece_value(piece));
	else
		return (solve_piece(ht, piece, workflow));
}

en_bool		evaluate_instruction(char *piece_prop, char *instruction)
{
	char		comp;
	long long	piece_n;
	long long	instruction_n;

	comp = instruction[1];
	piece_n = atoll(&piece_prop[2]);
	instruction_n = atoll(&instruction[2]);
	if ((comp == '>' && piece_n > instruction_n) || (comp == '<' && piece_n < instruction_n))
		return (true);
	return (false);
}

long long	solve_piece(t_hash_table *ht, char **piece, char *workflow)
{
	char	**instructions;
	char	*aux;	

	instructions = ft_split(ht_search(ht, workflow), ',');
	print_strs(instructions);
	for (int i = 0; instructions[i] != NULL; i++)
	{
		aux = ft_strchr(instructions[i], ':');
		if (aux == NULL)
		{
			return (send_to_workflow(ht, piece, instructions[i]));
			break ;
		}
		if (instructions[i][0] == 'x')
		{
			if (evaluate_instruction(piece[0], instructions[i]))
				return (send_to_workflow(ht, piece, aux + 1));
			continue;
		}
		else if (instructions[i][0] == 'm')
		{
			if (evaluate_instruction(piece[1], instructions[i]))
				return (send_to_workflow(ht, piece, aux + 1));
			continue;
		}
		else if (instructions[i][0] == 'a')
		{
			if (evaluate_instruction(piece[2], instructions[i]))
				return (send_to_workflow(ht, piece, aux + 1));
			continue;
		}
		else if (instructions[i][0] == 's')
		{
			if (evaluate_instruction(piece[3], instructions[i]))
				return (send_to_workflow(ht, piece, aux + 1));
			continue;
		}
	}
	free_strs(instructions);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	t_hash_table	*ht;
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
	print_table(ht);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		aux = ft_strtrim(str, "{}");
		strs = ft_split(aux, ',');
		res += solve_piece(ht, strs, "in");
		free(aux);
		free_strs(strs);
	}
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
