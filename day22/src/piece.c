/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:03:50 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/22 21:03:50 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

t_position3d	*get_point_from_str(char *str)
{
	t_position3d	*point;
	char			**strs;

	point = malloc(sizeof(t_position3d));
	strs = ft_split(str, ',');
	point->x = atoi(strs[0]);
	point->y = atoi(strs[1]);
	point->z = atoi(strs[2]);
	free_strs(strs);
	return (point);
}

t_position3d	new_point3d(int x, int y, int z)
{
	t_position3d	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_position3d	*new_point3d_malloc(int x, int y, int z)
{
	t_position3d	*point;

	point = malloc(sizeof (t_position3d));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}



t_piece	*create_piece(t_position3d *start, t_position3d *end)
{
	t_piece	*piece;

	piece = malloc(sizeof(t_piece));
	piece->start = start;
	piece->end = end;
	return (piece);
}

void	free_piece(t_piece *piece)
{
		free(piece->start);
		free(piece->end);
		free(piece);
}

void	free_pieces(t_piece **pieces)
{
	for (int i = 0; i < PIECES; i++)
	{
		if (pieces[i] == NULL)
			continue;
		free_piece(pieces[i]);
	}
	free(pieces);
}