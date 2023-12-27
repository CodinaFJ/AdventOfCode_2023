/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:37:48 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/24 11:37:48 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"AOC.h"

int	ft_lst_contains(t_list *lst, void *content, int (*compare)(void *, void *))
{
	t_list	*aux;

	if (lst != NULL && compare(content, lst->content))
	{
		return (1);
	}
	aux = lst;
	while (aux != NULL)
	{
		if (compare(content, aux->content))
			return (1);
		aux = aux->next;
	}
	return (0);
}

t_list	*ft_lst_remove(t_list *lst, void *content)
{
	t_list	*aux;
	t_list	*node;

	if (lst->content == content)
	{
		aux = lst->next;
		return (aux);
	}
	node = lst;
	while (node != NULL)
	{
		if (node->next->content == content)
		{
			aux = node->next;
			node->next = aux->next;
			return (lst);
		}
		node = node->next;
	}
	return (lst);
}