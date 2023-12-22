/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 00:33:57 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/21 00:33:57 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

// function to create a queue of given capacity.
// It initializes size of queue as 0
t_queue	*queue_create(size_t capacity)
{
    t_queue	*queue = malloc(sizeof(t_queue));
    queue->capacity = capacity;
    queue->front = 0;
	queue->size = 0;
 
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->str_array = malloc(queue->capacity * sizeof(char *));
    return (queue);
}

// Queue is full when size becomes equal to the capacity
int	queue_is_full(t_queue *queue)
{
    return (queue->size == (int) queue->capacity);
}

// Queue is empty when size is 0
int	queue_is_empty(t_queue *queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void	enqueue(t_queue *queue, char *item)
{
    if (queue_is_full(queue))
        return ;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->str_array[queue->rear] = ft_strdup(item);
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
char	*dequeue(t_queue *queue)
{
	char	*item;
    if (queue_is_empty(queue))
        return (NULL);
    item = queue->str_array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return (item);
}

// Function to get front of queue
char	*queue_front(t_queue *queue)
{
    if (queue_is_empty(queue))
        return (NULL);
    return queue->str_array[queue->front];
}

// Function to get rear of queue
char	*queue_rear(t_queue *queue)
{
    if (queue_is_empty(queue))
        return (NULL);
    return queue->str_array[queue->rear];
}

void	free_queue(t_queue *queue)
{
	for (int i = 0; i < queue->size; i++)
		free(queue->str_array[queue->front + 1]);
	free(queue->str_array);
	free(queue);
}