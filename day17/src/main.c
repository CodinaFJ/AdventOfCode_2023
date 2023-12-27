#include "AOC.h"

void print_map(t_list *list, int **map, int size)
{
	t_node	*node;

	while (list != NULL)
	{
		node = list->content;
		map[node->i][node->j] = 0;
		list = list->next;
	}
	for(int i = 0; i < size; i++)
	{
		print_array_path(map[i], size);
	}
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	int				**mtrx;
	long long		res = 0;
	int				len;
	int				line = 0;

	(void) res;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	f = fopen(argv[1], "r");
	mtrx = malloc(sizeof(int *) * SIZE);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		len = ft_strlen(str);
		if (str[len - 1] == '\n')
			len--;
		mtrx[line] = malloc(sizeof(int) * SIZE);
		for(int i = 0; i < len; i++)
		{
			mtrx[line][i] = str[i] - '0';
		}
		line++;
	}
	t_pos2d pos1;
	t_pos2d pos2;
	pos1.i = 0;
	pos1.j = 0;
	pos2.i = len - 1;
	pos2.j = len - 1;
	dijkstra_find_path(mtrx, len, pos1, pos2, 4, 10);
	//print_map(path, mtrx, len);
	//printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
