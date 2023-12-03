#include "day3.h"


int	evaluate_number(char **map, int i, int j)
{
	int		x = -1;
	int		y = -1;
	char	c;
	int		nbr;

	nbr = atoi(&map[i][j]);
	printf("Evaluating %d\n", nbr);
	while (ft_isdigit(map[i][j]))
	{
		x = -1;
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
				if (!ft_isdigit(c) && c != '.' && c != '\n' && c != '\0')
				{
					printf("Adding: %d\n", nbr);
					return (nbr);
				}
				y++;
			}
			x++;
		}
		j = j + 1;
	}
	return (0);
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
			if (ft_isdigit((int) map[i][j]))
			{
				res += evaluate_number(map, i, j);
				while (ft_isdigit((int) map[i][j]))
					j++;
				continue ;
			}
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