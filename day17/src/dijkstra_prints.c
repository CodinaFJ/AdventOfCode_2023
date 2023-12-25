/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_prints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:54:37 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/24 11:54:37 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

void	print_node_matrix_costs(t_node ***node_matrix)
{
	printf("COSTS MATRIX\n---------------\n");
	for (int i = 0; node_matrix[i] != NULL; i++)
	{
		for (int j = 0; node_matrix[i][j] != NULL; j++)
		{
			printf("%d[%d]\t", node_matrix[i][j]->weight, node_matrix[i][j]->cost);
		}
		printf("\n");
	}
	printf("---------------\n");
}

void	print_nodes_list(t_list *list)
{
	t_node	*node;

	while (list != NULL)
	{
		node = list->content;
		if (node->previous == NULL)
			printf("Node (%d, %d): Weight [%d] -> Previous (null) \n", node->i, node->j, node->weight);
		else
			printf("Node (%d, %d): Weight [%d] -> Previous (%d, %d) \n", node->i, node->j, node->weight, node->previous->i, node->previous->j);
		list = list->next;
	}
}