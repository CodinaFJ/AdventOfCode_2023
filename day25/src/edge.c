/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:51:19 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/25 08:51:19 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

t_edge	*new_edge(char *vertex_a, char *vertex_b)
{
	t_edge	*edge;

	edge = malloc(sizeof(t_edge));
	edge->vertex_a = malloc(4 * sizeof(char));
	edge->vertex_a_og = malloc(4 * sizeof(char));
	edge->vertex_b = malloc(4 * sizeof(char));
	edge->vertex_b_og = malloc(4 * sizeof(char));
	edge->chain_vertex_a = malloc(SIZE);
	edge->chain_vertex_b = malloc(SIZE);
	ft_strcpy(edge->vertex_a, vertex_a);
	ft_strcpy(edge->vertex_a_og, vertex_a);
	ft_strcpy(edge->vertex_b, vertex_b);
	ft_strcpy(edge->vertex_b_og, vertex_b);
	return (edge);
}

void	*dup_edge(void *src)
{
	t_edge	*edge;
	t_edge	*edge_src;

	edge_src = (t_edge *) src;
	edge = new_edge("", "");
	ft_strcpy(edge->vertex_a, edge_src->vertex_a);
	ft_strcpy(edge->vertex_a_og, edge_src->vertex_a_og);
	ft_strcpy(edge->vertex_b, edge_src->vertex_b);
	ft_strcpy(edge->vertex_b_og, edge_src->vertex_b_og);
	return ((void *) edge);
}

int	edges_cmp(void *edge_a, void *edge_b)
{
	t_edge	*edge_1;
	t_edge	*edge_2;

	edge_1 = (t_edge *) edge_a;
	edge_2 = (t_edge *) edge_b;

	if (ft_strcmp(edge_1->vertex_a, edge_2->vertex_a) == 0
		&& ft_strcmp(edge_1->vertex_b, edge_2->vertex_b) == 0)
		return (1);
	if (ft_strcmp(edge_1->vertex_b, edge_2->vertex_a) == 0
		&& ft_strcmp(edge_1->vertex_a, edge_2->vertex_b) == 0)
		return (1);
	return (0);
}

void	free_edge(void *edge)
{
	t_edge *edge_free;

	edge_free = (t_edge *) edge;
	free(edge_free->vertex_a);
	free(edge_free->vertex_b);
	free(edge_free->vertex_a_og);
	free(edge_free->vertex_b_og);
	free(edge_free);
}

void	print_edge(t_edge *edge)
{
	printf("Edge: %s <-> %s\n", edge->vertex_a, edge->vertex_b);
}

void	print_edge_og(t_edge *edge)
{
	printf("Edge: %s <-> %s\n", edge->vertex_a_og, edge->vertex_b_og);
}

void	print_edge_chain(t_edge *edge)
{
	printf("Edge: %s <-> %s\n", edge->chain_vertex_a, edge->chain_vertex_b);
}

void	print_edges(t_list *edges)
{
	while(edges != NULL)
	{
		print_edge((t_edge *) edges->content);
		edges = edges->next;
	}
	printf("\n");
}

void	print_edges_og(t_list *edges)
{
	while(edges != NULL)
	{
		print_edge_og((t_edge *) edges->content);
		edges = edges->next;
	}
	printf("\n");
}

void	print_edges_chains(t_list *edges)
{
	while(edges != NULL)
	{
		print_edge_chain((t_edge *) edges->content);
		edges = edges->next;
		
	}
	printf("\n");
}