#include "AOC.h"

void	print_step(char order, char *instruction, char *commands)
{
	printf("ORDER [%c] -> Instruction [%s] -> commands [%s] \n", order, instruction, commands);
}

long long	follow_map(char *commands, t_hash_table *map_ht)
{
	long long	res = 0;
	char		*str;
	char		instruction[4] = "AAA";
	size_t		i = 0;

	while (1)
	{
		str = ht_search(map_ht, instruction);
		if (ft_strcmp(instruction, "ZZZ") == 0)
			break ;
		if (commands[i] == 'L')
		{
			ft_memcpy(instruction, &str[0], 3);
			instruction[3] = '\0';
		}
		else if (commands[i] == 'R')
		{
			ft_memcpy(instruction, &str[5], 3);
			instruction[3] = '\0';
		}
		//print_step(commands[i], instruction, str);
		i++;
		res++;
		if (commands[i] != 'L' && commands[i] != 'R')
			i = 0;
	}

	return (res);
}

void	fill_table(char *str, t_hash_table *ht)
{
	char	**strs;

	strs = ft_split(str, '=');
	strs[0] = ft_strtrim(strs[0], " ");
	strs[1] = ft_strtrim(strs[1], " ()\n");
	ht_insert(ht, strs[0], strs[1]);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[500];
	char			*aux;
	long long		res = 0;
	char			commands[300];
	t_hash_table	*ht = create_table(HT_CAPACITY);

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	aux = fgets(commands, 500, f);
	aux = fgets(str, 500, f);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		fill_table(str, ht);
	}
	//print_table(ht);
	//print_search(ht, "FKL");
	res = follow_map(commands, ht);
	printf("Result: %lld\n", res);
	fclose(f);
	free_htable(ht);
	exit (0);
}
