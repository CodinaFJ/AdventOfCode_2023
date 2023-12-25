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

long long	count_heat(t_list *list)
{
	t_node		*node;
	long long	heat = 0;

	list = list->next;
	while (list != NULL)
	{
		node = list->content;
		heat += node->weight;
		list = list->next;
	}
	return (heat);
}

en_bool	evaluate_next_node(t_node *next_node, t_node *current_node)
{
	int		horizontal_moves = 0;
	int		vertical_moves = 0;
	t_node	*aux_node;

	aux_node = current_node;
	while (aux_node != NULL && aux_node->i == next_node->i)
	{
		horizontal_moves++;
		aux_node = aux_node->previous;
	}
	aux_node = current_node;
	while (aux_node != NULL && aux_node->j == next_node->j)
	{
		vertical_moves++;
		aux_node = aux_node->previous;
	}
	if (vertical_moves > 3 || horizontal_moves > 3)
		return (false);
	printf("(%d, %d) -> (%d, %d) Evaluate neighbour node: H[%d] V[%d]\n", current_node->i, current_node->j, next_node->i, next_node->j, horizontal_moves, vertical_moves);
	return (true);
}

void	bake_neighbours_list_heat(t_list *neighbours_list, t_list *open_list, t_node *current_node)
{
	t_node	*neighbour_node;
	t_list	*neighbour_list_node;
	int		cost;

	neighbour_list_node = neighbours_list;
	while (neighbour_list_node != NULL)
	{
		neighbour_node = neighbour_list_node->content;
		if (neighbour_node == NULL || neighbour_node->closed)
		{
			neighbour_list_node = neighbour_list_node->next;
			continue;
		}
		cost = current_node->cost + neighbour_node->weight;
		if (cost < neighbour_node->cost)
		{
			printf("(%d, %d) -> Update cost -> %d\n", neighbour_node->i, neighbour_node->j, cost);
			neighbour_node->cost = cost;
			neighbour_node->previous = current_node;
			if (!ft_lst_contains(open_list, neighbour_node))
				ft_lstadd_back(&open_list, ft_lstnew(neighbour_node));
		}
		else if (cost == neighbour_node->cost)
		{
			printf("(%d, %d) -> Update extra cost -> %d\n", neighbour_node->i, neighbour_node->j, cost);
			neighbour_node = node_dup(neighbour_node);
			neighbour_node->cost = cost;
			neighbour_node->previous = current_node;
			if (!ft_lst_contains(open_list, neighbour_node))
				ft_lstadd_back(&open_list, ft_lstnew(neighbour_node));
		}
		neighbour_list_node = neighbour_list_node->next;
	}
	ft_lstclear(&neighbours_list, NULL);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	t_list			*path;
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
	path = dijkstra_find_path(mtrx, len, pos1, pos2);
	print_map(path, mtrx, len);
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
