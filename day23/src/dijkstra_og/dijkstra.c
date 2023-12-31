/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:12:24 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/23 12:12:24 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

t_list	*calculate_path(t_node *end_node)
{
	t_list	*path;
	t_node	*aux_node;

	if (end_node->previous == NULL)
		return (NULL);
	path = ft_lstnew(end_node);
	aux_node = end_node->previous;
	while (aux_node != NULL)
	{
		ft_lstadd_front(&path, ft_lstnew(aux_node));
		aux_node = aux_node->previous;
	}
	return (path);
}

t_list	*get_min_cost_node(t_list *nodes_list)
{
	t_list	*min_cost_lst_node;
	t_node	*aux_node;

	min_cost_lst_node = nodes_list;
	while (nodes_list != NULL)
	{
		aux_node = (t_node *) nodes_list->content;
		if (aux_node->cost < ((t_node *) min_cost_lst_node->content)->cost)
			min_cost_lst_node = nodes_list;
		nodes_list = nodes_list->next;
	}
	return (min_cost_lst_node);
}


t_list	*create_neighbours_list(t_node ***node_matrix, t_node *current_node)
{
	t_list	*neighbours_list;
	t_list	*aux;

	neighbours_list = ft_lstnew(NULL); // TODO: this should not be necessary
	if (current_node->i > 0)
		ft_lstadd_back(&neighbours_list, ft_lstnew(node_matrix[current_node->i - 1][current_node->j]));
	if (node_matrix[current_node->i + 1] != NULL)
		ft_lstadd_back(&neighbours_list, ft_lstnew(node_matrix[current_node->i + 1][current_node->j]));
	if (current_node->j > 0)
		ft_lstadd_back(&neighbours_list, ft_lstnew(node_matrix[current_node->i][current_node->j - 1]));
	if (node_matrix[current_node->i][current_node->j + 1] != NULL)
		ft_lstadd_back(&neighbours_list, ft_lstnew(node_matrix[current_node->i][current_node->j + 1]));
	aux = neighbours_list->next;
	free(neighbours_list); // TODO: together with this
	return (aux);
}

void	bake_neighbours_list(t_list *neighbours_list, t_list *open_list, t_node *current_node)
{
	t_node	*neighbour_node;
	t_list	*neighbour_list_node;

	neighbour_list_node = neighbours_list;
	while (neighbour_list_node != NULL)
	{
		neighbour_node = neighbour_list_node->content;
		if (neighbour_node == NULL || neighbour_node->closed)
		{
			neighbour_list_node = neighbour_list_node->next;
			continue;
		}
		if (current_node->cost + neighbour_node->weight < neighbour_node->cost)
		{
			neighbour_node->cost = current_node->cost + neighbour_node->weight;
			neighbour_node->previous = current_node;
			if (!ft_lst_contains(open_list, neighbour_node))
				ft_lstadd_back(&open_list, ft_lstnew(neighbour_node));
		}
		neighbour_list_node = neighbour_list_node->next;
	}
	ft_lstclear(&neighbours_list, NULL);
}

void	bake_open_list(t_list *open_list, t_node ***nodes_matrix, t_pos2d end)
{
	t_node	*current_node;
	t_list	*neighbours_list;

	while (open_list != NULL)
	{
		current_node = get_min_cost_node(open_list)->content;
		printf("(%d, %d) Selected for min cost -> %d\n", current_node->i, current_node->j, current_node->cost);
		if (current_node->i == end.i && current_node->j == end.j)
			return ;
		neighbours_list = create_neighbours_list(nodes_matrix, current_node);
		bake_neighbours_list(neighbours_list, open_list, current_node, end.i);
		open_list = ft_lst_remove(open_list, current_node);
		current_node->closed = true;
	}
}	

t_list	*dijkstra_find_path(int **map, int size, t_pos2d start, t_pos2d end)
{
	t_node	***nodes_matrix;
	t_list	*open_list;
;
	nodes_matrix = create_nodes_matrix(size, map);
	nodes_matrix[start.i][start.j]->cost = 0;
	open_list = ft_lstnew((void *) nodes_matrix[start.i][start.j]);
	bake_open_list(open_list, nodes_matrix, end);
	return (calculate_path(nodes_matrix[end.i][end.j]));
}