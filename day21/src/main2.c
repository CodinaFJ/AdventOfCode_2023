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

long long	solve_pos(char **map, int steps, int x, int y)
{
	long long	res = 0;

	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j] == REACHED)
				map[i][j] = PLOT;
		}
	}
	map[x][y] = REACHED;
	for (int i = 0; i < steps; i++)
		walk_one_step(map);
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
	t_position		start_pos;

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
	start_pos = ft_strschr((char **) strs, START);
	strs[start_pos.i][start_pos.j] = PLOT;
	int len = strs_len((char **) strs);
	long long grid_width = (STEPS_N / len) - 1;

	long long odd_tiles_n = ((grid_width / 2) * 2) + 1;
	odd_tiles_n *= odd_tiles_n;
	long long even_tiles_n = ((grid_width + 1) / 2) * 2;
	even_tiles_n *= even_tiles_n;
	printf("Size %d Grid width %lld Odd tiles %lld Even tiles %lld\n", len, grid_width, odd_tiles_n, even_tiles_n);

	long long tile_even = solve_pos((char **) strs, (len * 2) / 2, start_pos.i, start_pos.j);
	long long tile_odd = solve_pos((char **) strs, (len * 2) / 2 + 1, start_pos.i, start_pos.j);

	long long tile_top = solve_pos((char **) strs, len - 1, len - 1, start_pos.j);
	long long tile_right = solve_pos((char **) strs, len - 1, start_pos.i, 0);
	long long tile_left = solve_pos((char **) strs, len - 1, start_pos.i, len - 1);
	long long tile_bot = solve_pos((char **) strs, len - 1, 0, start_pos.j);

	long long tile_sm_tr = solve_pos((char **) strs, (len / 2) - 1, len - 1, 0);
	long long tile_sm_tl = solve_pos((char **) strs, (len / 2) - 1, len - 1, len - 1);
	long long tile_sm_br = solve_pos((char **) strs, (len / 2) - 1, 0, 0);
	long long tile_sm_bl = solve_pos((char **) strs, (len / 2) - 1, 0, len - 1);

	long long tile_lg_tr = solve_pos((char **) strs, (3 * len / 2) - 1, len - 1, 0);
	long long tile_lg_tl = solve_pos((char **) strs, (3 * len / 2) - 1, len - 1, len - 1);
	long long tile_lg_br = solve_pos((char **) strs, (3 * len / 2) - 1, 0, 0);
	long long tile_lg_bl = solve_pos((char **) strs, (3 * len / 2) - 1, 0, len - 1);

	res = (tile_even * even_tiles_n) + (tile_odd * odd_tiles_n) 
			+ tile_bot + tile_left + tile_right + tile_top 
			+ ((tile_sm_tr + tile_sm_tl + tile_sm_br + tile_sm_bl) * (grid_width + 1)) 
			+ ((tile_lg_tr + tile_lg_tl + tile_lg_br + tile_lg_bl) * grid_width);
	(void) tile_bot;
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
