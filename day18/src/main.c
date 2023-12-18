#include "AOC.h"

void	dig(char direction, t_trench_map *trench_map)
{
	if (direction == NORTH)
		trench_map->i--;
	else if (direction == EAST)
		trench_map->j++;
	else if (direction == SOUTH)
		trench_map->i++;
	else if (direction == WEST)
		trench_map->j--;
	trench_map->map[trench_map->i][trench_map->j] = DUG;
}

void	dig_trench(char *str, t_trench_map *trench_map)
{
	char	**strs;
	int		n;
	char	c;

	strs = ft_split(str, ' ');
	c = strs[0][0];
	n = atoi(strs[1]);
	for (int i = 0; i < n; i++)
		dig(c, trench_map);
	free_strs(strs);
}

void	init_trench(t_trench_map *trench_map)
{
	trench_map->map = malloc(MAP_SIZE * sizeof(char *));
	for (int i = 0; i < MAP_SIZE; i++)
	{
		trench_map->map[i] = malloc(MAP_SIZE * sizeof(char));
		for (int j = 0; j < MAP_SIZE; j++)
		{
			trench_map->map[i][j] = GROUND;
		}
		trench_map->map[i][MAP_SIZE - 1] = '\0';
	}
	trench_map->map[MAP_SIZE - 1] = NULL;
	trench_map->i = 200;
	trench_map->j = 200;
	trench_map->map[200][200] = DUG;
}

void	flood_fill_trench(t_trench_map *trench_map, int i, int j)
{
	trench_map->map[i][j] = DUG;

	if (i > 0 && trench_map->map[i - 1][j] == GROUND) //NORTH
		flood_fill_trench(trench_map, i - 1, j);
	if (trench_map->map[i][j + 1] && trench_map->map[i][j + 1] == GROUND) //EAST
		flood_fill_trench(trench_map, i, j + 1);
	if (trench_map->map[i] != NULL && trench_map->map[i + 1][j] == GROUND) //SOUTH
		flood_fill_trench(trench_map, i + 1, j);
	if (j > 0 && trench_map->map[i][j - 1] == GROUND) //WEST
		flood_fill_trench(trench_map, i, j - 1);
}

long long	count_area(t_trench_map *t_trench_map)
{
	long long	res = 0;
	for (int i = 0; t_trench_map->map[i] != NULL; i++)
	{
		for (int j = 0; t_trench_map->map[i][j]; j++)
		{
			if (t_trench_map->map[i][j] == DUG)
				res++;
		}
	}
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	t_trench_map	*trench_map;
	int				res = 0;


	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	trench_map = malloc(sizeof(t_trench_map));
	init_trench(trench_map);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, SIZE, f);
		if (aux == NULL) break ;
		dig_trench(str, trench_map);
	}
	//flood_fill_trench(trench_map, 200, 201);
	res = count_area(trench_map);
	//print_strs(trench_map->map);
	(void) res;
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
