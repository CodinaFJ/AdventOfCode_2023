#include "AOC.h"

int	g_num[SIZE];
int	g_index = 0;

void print_hike(t_list *list, char **map)
{
	t_node	*node;

	while (list != NULL)
	{
		node = list->content;
		map[node->i][node->j] = 'O';
		list = list->next;
	}
	print_strs(map);

}

en_bool	evaluate_step(int i, int j, char **map, int x, int y)
{
	if (abs(x + y) != 1) //Adyacents
		return (false);
	if (x + i < 0 || map[x + i] == NULL || y + j < 0 || map[x + i][y + j] == '\0') //In map
		return (false);
	if ( map[i + x][j + y] == '#') //Forest
		return (false);
	return (true);
}

void	hike_flood_fill(int **map_int, char **map, int i, int j, t_pos2d end, int count, int len)
{
	int	**new_map_int;

	//printf("Hike flood fill node (%d, %d) count -> %d\n", i, j, count);	
	if (i == end.i && j == end.j)
	{
		for (int i = 0; i < len; i++)
			free(map_int[i]);
		free(map_int);
		if (count < 6078)
			return ;
		g_num[g_index] = count;
		g_index++;
		printf("Finished with count: %d\n", count);
		return ;
	}
	map_int[i][j] = count;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (evaluate_step(i, j, map, x, y))
			{
				if (map_int[i + x][j + y] == 0)
				{
					new_map_int = malloc (sizeof (int *) * len);
					for (int i = 0; i < len; i++)
					{
						new_map_int[i] = malloc (sizeof (int) * len);
						for (int j = 0; j < len; j++)
						{
							new_map_int[i][j] = map_int[i][j];
						}
					}
					hike_flood_fill((int **) new_map_int, map, i + x, j + y, end, count + 1, len);
				}
			}
		}
	}
	for (int i = 0; i < len; i++)
		free(map_int[i]);
	free(map_int);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			map[SIZE][SIZE];
	int				**map_int;
	long long		res = 0;
	int				len;

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
		aux = ft_strtrim(str, "\n");
		add_line(aux, (char **) map);
	}
	len = strs_len((char **) map);
	map_int = malloc(sizeof(int *) * len);
	for (int i = 0; i < len; i++)
	{
		map_int[i] = malloc(sizeof(int) * len);
		for (int j = 0; j < len; j++)
		{
			map_int[i][j] = 0;
		}
	}
	t_pos2d pos2;
	pos2.i = len - 1;
	pos2.j = len - 2;
	hike_flood_fill((int **) map_int, (char **) map, 0, 1, pos2, 1, len);
	int max = 0;
	for (int i = 0; i < g_index; i++)
	{
		if (g_num[i] > max)
			max = g_num[i];
	}

	/*for (int i = 0; i < len; i++)
	{
		print_array_int(map_int[i], len);
	}*/
	printf("res: %d\n", max - 1);
	fclose(f);
	exit (0);
}
