/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:41:31 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/24 11:41:31 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

t_node	*node_dup(t_node *node)
{
	t_node *node_dup;

	node_dup = malloc(sizeof(t_node));
	node_dup->cost = node->cost;
	node_dup->i = node->i;
	node_dup->j = node->j;
	node_dup->current_movement = node->current_movement;
	node_dup->straight_movements = node->straight_movements;
	return (node_dup);
}

t_node	*new_node(int i, int j, int cost, t_movement movement, int straight_movements)
{
	t_node	*node;
	
	node = malloc(sizeof(t_node));
	node->i = i;
	node->j = j;
	node->cost = cost;
	node->current_movement = movement;
	node->straight_movements = straight_movements;
	return (node);
}

int	node_cmp(void *node_a, void *node_b)
{
	t_node	*node1 = (t_node *) node_a;
	t_node	*node2 = (t_node *) node_b;
	if (node1->i == node2->i
		&& node1->j == node2->j
		&& node1->current_movement == node2->current_movement
		&& node1->straight_movements == node2->straight_movements)
		return (1);
	return (0);
}

void	free_nodes_matrix(t_node ***node_matrix)
{
	for (int i = 0; node_matrix[i] != NULL; i++)
	{
		for (int j = 0; node_matrix[i][j] != NULL; j++)
			free(node_matrix[i][j]);
		free(node_matrix[i]);
	}
	free(node_matrix);
}