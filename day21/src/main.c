#include "AOC.h"

long long	count_reached(char **map)
{
	long long res = 0;

	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j] == REACHED)
				res++;
		}
	}
	return (res);
}

void	step_around(char **map, int i, int j)
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (i + x < 0 || j + y < 0 || map[i + x] == NULL || !map[i + x][j + y])
				continue ;
			if (abs(y + x) != 1 || map[i + x][j + y] == ROCK)
				continue ;
			if (map[i + x][j + y] == PLOT)
				map[i + x][j + y] = STEPPED;
		}
	}
}

void	walk_one_step(char **map)
{
	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j] == REACHED)
			{
				step_around(map, i, j);
				map[i][j] = PLOT;
			}
		}
	}
	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j] == STEPPED)
				map[i][j] = REACHED;
		}
	}
}

long long	solve(char **map)
{
	long long	res = 0;
	t_position	start_pos;

	start_pos = ft_strschr(map, START);
	map[start_pos.i][start_pos.j] = REACHED;
	for (int i = 0; i < 64; i++)
	{
		walk_one_step(map);
	}
	print_strs(map);
	res = count_reached(map);
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			strs[SIZE][SIZE];
	long long		res = 0;

	(void) res;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		add_line(str, (char **) strs);
	}
	res = solve((char **) strs);
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
