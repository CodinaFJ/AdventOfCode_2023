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

en_bool	assert_bounds(int i, int j, int size)
{
	if (i < 0 || j < 0 || i >=size || j >= size)
		return (false);
	return (true);
}

void calc_movement(int *i, int *j, t_movement movement)
{
	if (movement == NORTH) (*i) = (*i) - 1;
	else if (movement == EAST) (*j) = (*j) + 1;
	else if (movement == SOUTH) (*i) = (*i) + 1;
	else if (movement == WEST) (*j) = (*j) - 1;
}

t_list	*get_min_cost_node(t_list **nodes_list)
{
	for (int i = 0; i < 1000; i++)
	{
		if (nodes_list[i] != NULL)
			return (nodes_list[i]);
	}
	return (NULL);
}

void	add_turn_nodes(t_node *current_node, int min_movements, int size, t_list **open_list, int **map, t_list *closed_list)
{
	if (current_node->straight_movements < min_movements)
		return ;
	for (int mov = 0; mov < 4; mov++)
	{
		if ((int)(current_node->current_movement % 2) == mov % 2) // If moving in same direction forwards or backwards
			continue ;
		int	new_i = current_node->i;
		int new_j = current_node->j;
		calc_movement(&new_i, &new_j, mov);
		if (assert_bounds(new_i, new_j, size))
		{
			t_node *next_node = new_node(new_i, new_j, current_node->cost + map[new_i][new_j], mov, 1);
			if (!ft_lst_contains(closed_list, next_node, &node_cmp))
				ft_lstadd_front(&(open_list[next_node->cost]), ft_lstnew(next_node));
			else
				free(next_node);
		}
	}
}

void	bake_open_list(t_list **open_list, int **map, int size, t_pos2d end, int min_movements, int max_movements)
{
	t_node	*current_node;
	t_list	*closed_list;

	closed_list = NULL;
	for (int i = 0; i < 1000; i++)
	{
		while (open_list[i] != NULL)
		{
			current_node = open_list[i]->content;
			if (current_node->cost % 50 == 0)
				printf("(%d, %d) Selected for min cost -> %d\n", current_node->i, current_node->j, current_node->cost);
			
			if (current_node->i == end.i && current_node->j == end.j && current_node->straight_movements >= min_movements)
			{
				printf("Solution found: %d\n", current_node->cost);
				ft_lstclear(&closed_list, &free);
				return ;
			}
			if (ft_lst_contains(closed_list, current_node, &node_cmp))
			{
				ft_lstadd_front(&closed_list, ft_lstnew(current_node));
				open_list[current_node->cost] = ft_lst_remove(open_list[current_node->cost], current_node);
				continue;
			}
			if (current_node->current_movement != NONE && current_node->straight_movements < max_movements) //Keep moving straight
			{
				int	new_i = current_node->i;
				int new_j = current_node->j;
				calc_movement(&new_i, &new_j, current_node->current_movement);
				if (assert_bounds(new_i, new_j, size))
				{
					t_node *next_node = new_node(new_i, new_j, current_node->cost + map[new_i][new_j], current_node->current_movement, current_node->straight_movements + 1);
					if (!ft_lst_contains(closed_list, next_node, &node_cmp))
						ft_lstadd_front(&(open_list[next_node->cost]), ft_lstnew(next_node));
					else
						free(next_node);
				}
			}
			add_turn_nodes(current_node, min_movements, size, open_list, map, closed_list);
			ft_lstadd_front(&closed_list, ft_lstnew(current_node));
			open_list[current_node->cost] = ft_lst_remove(open_list[current_node->cost], current_node);
		}
	}	
	ft_lstclear(&closed_list, &free);
}	

void	dijkstra_find_path(int **map, int size, t_pos2d start, t_pos2d end, int min_movements, int max_movements)
{
	t_list	**open_list;
	t_node	*start_node;

	open_list = malloc(sizeof(t_list *) * 1000);
	for (int i = 0; i < 1000; i++)
	{
		open_list[i] = NULL;
	}
	start_node = new_node(start.i, start.j, 0, EAST, 0);
	ft_lstadd_front(&(open_list[start_node->cost]), ft_lstnew((void *) start_node));
	start_node = new_node(start.i, start.j, 0, SOUTH, 0);
	ft_lstadd_front(&(open_list[start_node->cost]), ft_lstnew((void *) start_node));
	bake_open_list( open_list, map, size, end, min_movements, max_movements);
	for (int i = 0; i < 1000; i++)
	{
		ft_lstclear(&(open_list[i]), &free);
	}
	free(open_list);
}