/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:18:31 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/27 18:18:31 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

t_line	*calc_line(char **strs)
{
	char	**strs_pos;
	char	**strs_vel;
	t_line	*line;

	line = malloc(sizeof(t_line));
	strs_pos = ft_split(strs[0], ',');
	strs_vel = ft_split(strs[1], ',');
	line->x = atof(strs_pos[0]);
	line->y = atof(strs_pos[1]);
	line->z = atof(strs_pos[2]);
	line->vx = atof(strs_vel[0]);
	line->vy = atof(strs_vel[1]);
	line->vz = atof(strs_vel[2]);
	line->m = line->vy/line->vx;
	line->n = line->y - (line->x * line->m);
	free_strs(strs);
	free_strs(strs_pos);
	free_strs(strs_vel);
	return (line);
}

void	print_line(t_line *line)
{
	printf("y = %fx + %f", line->m, line->n);;
}

void	print_line_r3(t_line *line)
{
	printf("(x, y, z) = (%f, %f, %f)t + (%f, %f, %f)\n", line->vx, line->vy, line->vz, line->x, line->y, line->z);
}

void	print_lines(t_line **lines)
{
	printf("\nPRINT LINES\n\n");
	for (int i = 0; lines[i] != NULL; i++)
	{
		printf("[%d] y = %fx + %f\n", i, lines[i]->m, lines[i]->n);
	}
	printf("\n");
}