/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 00:32:15 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/21 00:32:15 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _QUEUE_H
# define _QUEUE_H
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef struct s_queue 
{
    int		front;
	int		rear;
	int		size;
    size_t	capacity;
    char	**str_array;
}	t_queue;

t_queue*	queue_create(size_t capacity);
int			queue_is_full(t_queue* queue);
int			queue_is_empty(t_queue* queue);
void		enqueue(t_queue* queue, char *item);
char		*dequeue(t_queue* queue);
char		*queue_front(t_queue* queue);
char		*queue_rear(t_queue* queue);
void		free_queue(t_queue *queue);

#endif