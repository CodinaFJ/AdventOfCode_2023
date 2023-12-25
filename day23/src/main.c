#include "AOC.h"

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

int	main(int argc, char **argv)
{
	FILE			*f;
	t_list			*path;
	char			str[SIZE];
	char			*aux;
	char			map[SIZE][SIZE];
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
	t_pos2d pos1;
	t_pos2d pos2;
	pos1.i = 0;
	pos1.j = 1;
	pos2.i = len - 1;
	pos2.j = len - 2;
	path = dijkstra_find_path((char **) map, len, pos1, pos2);
	print_hike(path, (char **) map);
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
