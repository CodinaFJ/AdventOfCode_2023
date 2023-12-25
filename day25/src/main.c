#include "AOC.h"

void	add_edges(t_list *edges_list, char *vertex1, char *str)
{
	char	**strs;
	t_edge	*edge;
	int		i;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i] != NULL)
	{
		edge = new_edge(vertex1, strs[i]);
		if (!ft_lst_contains(edges_list, (void *)edge, &edges_cmp))
			ft_lstadd_back(&edges_list,ft_lstnew((void *) edge));
		else
			free_edge(edge);
		i++;
	}
	free(strs);
}

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(dest + i) != 0)
		i++;
	while (*(src + j) != 0)
	{
		*(dest + i + j) = *(src + j);
		j++;
	}
	*(dest + i + j) = 0;
	return (dest);
}

void	edges_list_substitute_vertex(t_list *edges_lst, t_edge *edge)
{
	t_edge	*edge_aux;

	while (edges_lst != NULL)
	{
		edge_aux = edges_lst->content;
		if (ft_strcmp(edge_aux->vertex_a, edge->vertex_b) == 0)
		{
			ft_strcat(edge_aux->chain_vertex_a, " ");
			ft_strcat(edge_aux->chain_vertex_a, edge_aux->vertex_a);
			ft_strcpy(edge_aux->vertex_a, edge->vertex_a);
		}
		if (ft_strcmp(edge_aux->vertex_b, edge->vertex_b) == 0)
		{
			ft_strcat(edge_aux->chain_vertex_b, " ");
			ft_strcat(edge_aux->chain_vertex_b, edge_aux->vertex_b);
			ft_strcpy(edge_aux->vertex_b, edge->vertex_a);
		}
		edges_lst = edges_lst->next;
	}
}

int	are_only_two_vertex(t_list *edges_lst)
{
	int		res;
	char	*str_a;
	char	*str_b;
	t_list	*node;
	t_edge	*edge_aux;

	node = edges_lst;
	res = 1;
	str_a = ft_strdup(((t_edge *)edges_lst->content)->vertex_a);
	str_b = ft_strdup(((t_edge *)edges_lst->content)->vertex_a);
	while (node != NULL)
	{
		free(str_b);
		str_b = ft_strdup(((t_edge *)node->content)->vertex_a);
		if (ft_strcmp(str_a, str_b) != 0)
			break;
		free(str_b);
		str_b = ft_strdup(((t_edge *)node->content)->vertex_b);
		if (ft_strcmp(str_a, str_b) != 0)
			break;
		node = node->next;
	}
	edges_lst = edges_lst->next;
	while (edges_lst != NULL)
	{
		edge_aux = (t_edge *) edges_lst->content;
		if (ft_strcmp(edge_aux->vertex_a, str_a) != 0 && ft_strcmp(edge_aux->vertex_a, str_b) != 0)
			res = 0;
		if (ft_strcmp(edge_aux->vertex_b, str_a) != 0 && ft_strcmp(edge_aux->vertex_b, str_b) != 0)
			res = 0;
		edges_lst = edges_lst->next;
	}
	free(str_a);
	free(str_b);
	return (res);
}

void	remove_redundant(t_list **edges_lst)
{
	t_edge	*edge;
	t_list	*node;
	int		i = 0;

	node = *edges_lst;
	while (node != NULL)
	{
		edge = node->content;
		if (ft_strcmp(edge->vertex_a, edge->vertex_b) == 0)
		{
			free(ft_lst_remove_at(edges_lst, i));
			node = *edges_lst; 
			i = 0;
		}
		else
		{
			i++;
			node = node->next;
		}
	}
}

int min_cut_karger(t_list **edges_lst)
{
	int 	r;
	int		size;
	t_edge	*edge_aux;

	while (are_only_two_vertex(*edges_lst) != 1)
	{
		size = ft_lstsize(*edges_lst);
		r = rand() % size;
		edge_aux = (t_edge *) ft_lst_remove_at(edges_lst, r);
		edges_list_substitute_vertex(*edges_lst, edge_aux);
		remove_redundant(edges_lst);
		free_edge(edge_aux);
	}
	size = ft_lstsize(*edges_lst);
	return (size);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	t_list			*edges_lst;
	t_list			*edges_lst_cpy;
	char			str[SIZE];
	char			*aux;
	char			**strs;
	long long		res = 0;

	(void) res;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	f = fopen(argv[1], "r");
	edges_lst = ft_lstnew(ft_lstnew((void *) new_edge("c", "c")));
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		aux = ft_strtrim(str, "\n");
		strs = ft_split(aux, ':');
		add_edges(edges_lst, strs[0], strs[1]);
		free(strs);
		free(aux);
	}
	ft_lst_remove_at(&edges_lst, 0);
	//print_edges(edges_lst);
	srand(time(NULL));
	edges_lst_cpy = ft_lst_dup(edges_lst, dup_edge);
	int size = min_cut_karger(&edges_lst_cpy);
	while (size != 3)
	{
		ft_lstclear(&edges_lst_cpy, free_edge);
		edges_lst_cpy = ft_lst_dup(edges_lst, dup_edge);
		size = min_cut_karger(&edges_lst_cpy);
	}
	print_edges_og(edges_lst_cpy);
	print_edges_chains(edges_lst_cpy);
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
