#include "day3.h"

int	get_nbr(char **map, int i, int j)
{
	while ( j - 1 >= 0 && ft_isdigit(map[i][j - 1]))
		j--;
	printf("Get nbr: %d\n", atoi(&map[i][j]));
	return (atoi(&map[i][j]));
}

int	evaluate_gear(char **map, int i, int j)
{
	int		x = -1;
	int		y = -1;
	char	c;
	int		nbr1 = 0;
	int		nbr2 = 0;

	printf("Evaluate gear\n");
	while (x < 2)
	{
		y = -1;
		while (y < 2)
		{
			if (i + x < 0 || j + y < 0 || !map[i + x][j + y] || (x == 0 && y == 0))
			{
				y++;
				continue ;
			}
			c = map[i + x][j + y];
			if (ft_isdigit(c))
			{
				if (nbr1 == 0)
					nbr1 = get_nbr(map, i + x, j + y);
				else if (nbr2 == 0)
					nbr2 = get_nbr(map, i + x, j + y);
				while (ft_isdigit(c))
				{
					c = map[i + x][j + y];
					y++;
				}
				continue ;
			}
			y++;
		}
		x++;
	}
	j = j + 1;
	return (nbr1 * nbr2);
}

void	evaluate_map(char **map)
{
	int	i = 0;
	int	j = 0;
	int res = 0;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '*')
				res += evaluate_gear(map, i, j);
			j++;
		}
		i++;
	}
	printf("Result: %d", res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[200];
	char			*aux;
	char			**txt;
	int				i = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	txt = ft_calloc(201, sizeof(char*));
	txt[200] = NULL;
	while (i < 200)
	{
		txt[i] = ft_calloc(200, sizeof(char));
		i++;
	}
	i = 0;
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 200, f);
		if (aux == NULL) break;
		ft_strlcpy(txt[i], str, 200);
		i++;
	}
	i = 0;
	fclose(f);
	evaluate_map(txt);
	exit (0);
}