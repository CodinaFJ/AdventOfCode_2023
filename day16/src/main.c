#include "AOC.h"

void	solve_beam(char **map, int i, int j, e_movement incoming_side, char **map_energy, int n);

long long	calculate_energy(char **energized_map)
{
	long long count = 0;

	for (int i = 0; energized_map[i] != NULL; i++)
	{
		for (int j = 0; energized_map[i][j]; j++)
		{
			if (energized_map[i][j] == '#')
				count++;
		}
	}
	return count;
}

void	move_beam(char **map, int i, int j, e_movement incoming_side, char **map_energy, int n)
{
	if (incoming_side == NORTH && map[i + 1] != NULL)
		solve_beam(map, i + 1, j, NORTH, map_energy, n);
	else if (incoming_side == EAST && j > 0)
		solve_beam(map, i, j - 1, EAST, map_energy, n);
	else if (incoming_side == SOUTH && i > 0)
		solve_beam(map, i - 1, j, SOUTH, map_energy, n);
	else if (incoming_side == WEST && map[i][j + 1])
		solve_beam(map, i, j + 1, WEST, map_energy, n);
}

void	solve_beam(char **map, int i, int j, e_movement incoming_side, char **map_energy, int n)
{
	char	c;

	c = map[i][j];
	if (map_energy[i][j] == '#')
		n++;
	else
		n = 0;
	map_energy[i][j] = '#';
	if (n > 100)
		return ;
	//print_strs(map_energy);
	//printf("Solve beam: %d, %d\n", i, j);
	if ((c == '\\' && incoming_side == EAST) || (c == '/' && incoming_side == WEST)) //Mirror going up
		move_beam(map, i, j, SOUTH, map_energy, n);
	else if ((c == '\\' && incoming_side == WEST) || (c == '/' && incoming_side == EAST)) //Mirror going down
		move_beam(map, i , j, NORTH, map_energy, n);
	else if ((c == '\\' && incoming_side == NORTH) || (c == '/' && incoming_side == SOUTH)) //Mirror going right
		move_beam(map, i , j, WEST, map_energy, n);
	else if ((c == '\\' && incoming_side == SOUTH) || (c == '/' && incoming_side == NORTH)) //Mirror going left
		move_beam(map, i , j, EAST, map_energy, n);
	else if (c == '|' && (incoming_side == EAST || incoming_side == WEST)) //Vertical split
	{
		move_beam(map, i, j, SOUTH, map_energy, n);
		move_beam(map, i, j, NORTH, map_energy, n);
	}
	else if(c == '-' && (incoming_side == NORTH || incoming_side == SOUTH)) //Horizontal split
	{
		move_beam(map, i, j, EAST, map_energy, n);
		move_beam(map, i, j, WEST, map_energy, n);
	}
	else //Continue
		move_beam(map, i, j, incoming_side, map_energy, n);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			strs[SIZE][SIZE];
	char			energized_map[SIZE][SIZE];
	int				aux_n = 0;
	int				res = 0;
	int				rows = 0;
	int				cols = 0;

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
		rows++;
		add_line(str, (char **) strs);
		add_line(str, (char **) energized_map);
	}

	for(int i = 0; ((char **)strs)[i] != NULL; i++)
	{
		ft_strscpy((char **) energized_map, (char **) strs);
		solve_beam((char **) strs, i, 0, WEST, (char **) energized_map, 0);
		aux_n = calculate_energy((char **)energized_map);
		if (aux_n > res)
			res = aux_n;
	}
	for(int i = 0; ((char **)strs)[0][i]; i++)
	{
		ft_strscpy((char **) energized_map, (char **) strs);
		solve_beam((char **) strs, 0, i, NORTH, (char **) energized_map, 0);
		aux_n = calculate_energy((char **)energized_map);
		cols++;
		if (aux_n > res)
			res = aux_n;
	}
	for(int i = 0; ((char **)strs)[i] != NULL; i++)
	{
		ft_strscpy((char **) energized_map, (char **) strs);
		solve_beam((char **) strs, i, rows - 1, EAST, (char **) energized_map, 0);
		aux_n = calculate_energy((char **)energized_map);
		if (aux_n > res)
			res = aux_n;
	}
	for(int i = 0; ((char **)strs)[0][i]; i++)
	{
		ft_strscpy((char **) energized_map, (char **) strs);
		solve_beam((char **) strs, cols - 1, i, SOUTH, (char **) energized_map, 0);
		aux_n = calculate_energy((char **)energized_map);
		if (aux_n > res)
			res = aux_n;
	}
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
