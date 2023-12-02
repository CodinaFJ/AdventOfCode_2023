#include "day2.h"

en_bool	evaluate_cubes(int	nbr, char	*color)
{
	ft_printf("Evaluate color: %s\n", color);
	if (strncmp(color, "blue", 4) == 0)
		return (nbr <= max_blue);
	else if (strncmp(color, "red", 3) == 0)
		return (nbr <= max_red);
	else if (strncmp(color, "green", 5) == 0)
		return (nbr <= max_green);
	return (false);
}

en_bool	evaluate_draw(char *draw)
{
	char	**cubes;
	char	**color_cubes;
	int		i = 0;

	ft_printf("Evaluate draw: %s\n", draw);
	cubes = ft_split(draw, ',');
	while (cubes[i] != NULL)
	{
		color_cubes = ft_split(cubes[i], ' ');
		if (evaluate_cubes(ft_atoi(color_cubes[0]), color_cubes[1]) == false)
			return (false);
		i++;
	}
	free_strs(cubes);
	free_strs(color_cubes);
	return (true);
}

int	evaluate_game(char *game)
{
	char 	**strs;
	char	**games;
	char	**game_def;
	int		game_nbr;
	int		i = 0;

	ft_printf("Evaluate game: %s", game);
	strs = ft_split(game, ':');
	games = ft_split(strs[1], ';');
	while (games[i] != NULL)
	{
		if (evaluate_draw(games[i]) == false)
			return (0);
		i++;
	}
	game_def = ft_split(strs[0], ' ');
	game_nbr = ft_atoi(game_def[1]);
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