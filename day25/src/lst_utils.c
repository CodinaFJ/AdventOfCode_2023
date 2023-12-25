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
		{
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

t_list	*ft_lst_remove(t_list *lst, void *content, int (*compare)(void *, void *))
{
	t_list	*aux;
	t_list	*node;

	if (compare(content, lst->content))
	{
		aux = lst->next;
		return (aux);
	}
	node = lst;
	while (node != NULL && node->next != NULL)
	{
		if (compare(content, node->next->content))
		{
			aux = node->next;
			node->next = aux->next;
			free_edge(aux->content);
			free(aux);
			return (lst);
		}
		node = node->next;
	}
	return (lst);
}

void	*ft_lst_pop(t_list **lst, void *content, int (*compare)(void *, void *))
{
	void	*aux;
	t_list	*node_aux;
	t_list	*node;

	aux = NULL;
	if (compare(content, (*lst)->content))
	{
		aux = (*lst)->content;
		*lst = (*lst)->next;
		return (aux);
	}
	node = *lst;
	while (node != NULL && node->next != NULL)
	{
		if (compare(content, node->next->content))
		{
			node_aux = node->next;
			node->next = node_aux->next;
			aux = node_aux->content;
			free(node_aux);
			return (aux);
		}
		node = node->next;
	}
	return (NULL);
}

t_list	*ft_lst_remove_all(t_list *lst, void *content, int (*compare)(void *, void *))
{
	t_list	*aux;
	t_list	*node;

	if (compare(content, lst->content))
	{
		aux = lst->next;
	}
	node = lst;
	while (node != NULL)
	{
		if (compare(content, node->content))
		{
			aux = node->next;
			if (aux != NULL)
				node->next = aux->next;
			else
				node->next = NULL;
		}
		node = node->next;
	}
	return (lst);
}

t_list	*ft_lst_dup(t_list *lst_src, void *(*dup)(void *))
{
	t_list	*lst_dst;

	lst_dst = ft_lstnew(dup(lst_src->content));
	lst_src = lst_src->next;
	while (lst_src != NULL)
	{
		ft_lstadd_back(&lst_dst, ft_lstnew(dup(lst_src->content)));
		lst_src = lst_src->next;
	}
	return (lst_dst);
}

void	*ft_lst_remove_at(t_list **lst, int index)
{
	int		i;
	void	*content;
	t_list	*node;
	t_list	*aux;

	i = 0;
	node = *lst;
	if (index == 0)
	{
		content = node->content;
		*lst = node->next;
		node->next = NULL;
		free(node);
		node = NULL;
	}
	while (node != NULL)
	{
		i++;
		if (i == index && node->next != NULL)
		{
			content = node->next->content;
			aux = node->next;
			node->next = aux->next;
			aux->next = NULL;
			free(aux);
		}
		node = node->next;
	}
	return (content);
}