#include "day2.h"

void	evaluate_cubes(int	nbr, char	*color, t_cube_set *cube_set)
{
	ft_printf("Evaluate color: %s\n", color);
	if (strncmp(color, "blue", 4) == 0)
	{
		if (cube_set->min_blue < nbr)
			cube_set->min_blue = nbr;
	}
	else if (strncmp(color, "red", 3) == 0)
	{
		if (cube_set->min_red < nbr)
			cube_set->min_red = nbr;
	}
	else if (strncmp(color, "green", 5) == 0)
	{
		if (cube_set->min_green < nbr)
			cube_set->min_green = nbr;
	}
}

void	evaluate_draw(char *draw, t_cube_set *cube_set)
{
	char	**cubes;
	char	**color_cubes;
	int		i = 0;

	ft_printf("Evaluate draw: %s\n", draw);
	cubes = ft_split(draw, ',');
	while (cubes[i] != NULL)
	{
		color_cubes = ft_split(cubes[i], ' ');
		evaluate_cubes(ft_atoi(color_cubes[0]), color_cubes[1], cube_set);
		i++;
	}
	free_strs(cubes);
	free_strs(color_cubes);
}

void	init_set(t_cube_set *cube_set)
{
	cube_set->min_blue = 0;
	cube_set->min_green = 0;
	cube_set->min_red = 0;
}

int	calculate_set_power(t_cube_set *cube_set)
{
	int	nbr;

	nbr = cube_set->min_blue * cube_set->min_green * cube_set->min_red;
	return (nbr);
}

int	evaluate_game(char *game)
{
	char 		**strs;
	char		**games;
	char		**game_def;
	int			game_nbr;
	t_cube_set	cube_set;
	int			i = 0;

	init_set(&cube_set);
	ft_printf("Evaluate game: %s", game);
	strs = ft_split(game, ':');
	games = ft_split(strs[1], ';');
	while (games[i] != NULL)
	{
		evaluate_draw(games[i], &cube_set);
		i++;
	}
	game_def = ft_split(strs[0], ' ');
	game_nbr = calculate_set_power(&cube_set);
	free_strs(strs);
	free_strs(games);
	free_strs(game_def);
	return (game_nbr);
}

int	main(int argc, char **argv)
{
	FILE	*f;
	char	str[500];
	char	*aux;
	long long		res = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		res += evaluate_game(aux);
	}
	fclose(f);
	ft_printf("Result: %d\n", res);
	exit (0);
}