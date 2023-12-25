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

t_node	*new_node(int i, int j, int weight)
{
	t_node	*node;
	
	node = malloc(sizeof(t_node));
	node->i = i;
	node->j = j;
	node->cost = 99999;
	node->weight = weight;
	node->previous = NULL;
	node->closed = false;
	return (node);
}

t_node	***create_nodes_matrix(int size, int **map)
{
	t_node	***node_matrix;

	node_matrix = malloc(sizeof(t_node **) * (size + 1));
	node_matrix[size] = NULL;
	for (int i = 0; i < size; i++)
	{
		node_matrix[i] = malloc(sizeof(t_node *) * (size + 1));
		node_matrix[i][size] = NULL;
		for (int j = 0; j < size; j++)
		{
			node_matrix[i][j] = new_node(i, j, map[i][j]);
		}
	}
	return (node_matrix);
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