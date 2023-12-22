/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tower.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:04:31 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/22 20:04:31 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOC.h"

void	print_tower(int ***tower)
{
	printf("\n\tPRINT TOWER\n------------------------------\n");
	for (int i = TOWER_SIZE - 1; i >= 0; i--)
	{
		printf("Level [%d]\n", i + 1);
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			printf("\t");
			print_array_int(tower[i][j], TOWER_WIDTH);

		}
		printf("\n");
	}
	printf("------------------------------\n");
}



int	***create_tower()
{
	int	***tower;

	tower = malloc(sizeof(int **) * TOWER_SIZE);
	for (size_t i = 0; i < TOWER_SIZE; i++)
	{
		tower[i] = malloc(sizeof(int *) * TOWER_WIDTH);
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			tower[i][j] = malloc(sizeof(int) * TOWER_WIDTH);
			for (size_t k = 0; k < TOWER_WIDTH; k++)
			{
				tower[i][j][k] = 0;
			}
		}
	}
	return (tower);
}

void	free_tower(int ***tower)
{
	for (size_t i = 0; i < TOWER_SIZE; i++)
	{
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			free(tower[i][j]);
		}
		free(tower[i]);
	}
	free(tower);
}

void	insert_piece(int ***tower, t_position3d *start, t_position3d *end, int n)
{
	if (start->z != end->z)
	{
		for(int k = start->z; k <= end->z; k++)
			tower[k - 1][start->y][start->x] = n;
	}
	else if (start->y != end->y)
	{
		for(int j = start->y; j <= end->y; j++)
			tower[start->z - 1][j][start->x] = n;
	}
	else if (start->x != end->x)
	{
		for(int i = start->x; i <= end->x; i++)
			tower[start->z - 1][start->y][i] = n;
	}
	else
		tower[start->z - 1][start->y][start->x] = n;
}

int		calculate_drop(int ***tower, t_position3d new_start, t_position3d new_end)
{
	int fall = 0;

	while (new_start.z - 1 > 0)
	{
		new_start.z--;
		new_end.z--;
		if (new_start.z != new_end.z)
		{
			for(int k = new_start.z; k <= new_end.z; k++)
			{
				if (tower[k - 1][new_start.y][new_start.x] != 0)
					return (fall);
			}
		}
		else if (new_start.y != new_end.y)
		{
			for(int j = new_start.y; j <= new_end.y; j++)
			{
				if (tower[new_start.z - 1][j][new_start.x] != 0)
					return (fall);
			}
		}
		else if (new_start.x != new_end.x)
		{
			for(int i = new_start.x; i <= new_end.x; i++)
			{
				if (tower[new_start.z - 1][new_start.y][i] != 0)
					return (fall);
			}
		}
		else
		{
			if (tower[new_start.z - 1][new_start.y][new_start.x] != 0)
				return (fall);
		}
		fall++;
	}
	return (fall);
}

en_bool	drop_piece(int ***tower, t_piece **pieces, int id)
{
	int fall = 0;

	t_position3d *start = pieces[id]->start;
	t_position3d *end = pieces[id]->end;

	insert_piece(tower, start, end, 0);
	fall = calculate_drop(tower, *start, *end);
	start->z -= fall;
	end->z -= fall;
	insert_piece(tower, start, end, id);
	if (fall > 0)
		return (true);
	return (false);
}

en_bool	try_drop_piece(int ***tower, t_piece **pieces, int id)
{
	int fall = 0;

	t_position3d *start = pieces[id]->start;
	t_position3d *end = pieces[id]->end;

	insert_piece(tower, start, end, 0);
	fall = calculate_drop(tower, *start, *end);
	insert_piece(tower, start, end, id);
	if (fall > 0)
		return (true);
	return (false);
}

int	colapse_tower_falls(int ***tower, t_piece **pieces)
{
	int		id;
	int		checked[PIECES];
	int		falls = 0;

	(void) pieces;
	ft_arrset_int(checked, 0, PIECES);
	for (size_t i = 0; i < TOWER_SIZE; i++)
	{
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			for (size_t k = 0; k < TOWER_WIDTH; k++)
			{
				id = tower[i][j][k];
				if (id != 0 && checked[id] == 0)
				{
					checked[id] = 1;
					if (drop_piece(tower, pieces, id) == true)
						falls++;
				}
			}
		}
	}
	return (falls);
}


en_bool	try_colapse_tower(int ***tower, t_piece **pieces)
{
	int		id;
	int		checked[PIECES];
	en_bool	colapsed = false;

	(void) pieces;
	ft_arrset_int(checked, 0, PIECES);
	for (size_t i = 0; i < TOWER_SIZE; i++)
	{
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			for (size_t k = 0; k < TOWER_WIDTH; k++)
			{
				id = tower[i][j][k];
				if (id != 0 && checked[id] == 0)
				{
					checked[id] = 1;
					if (try_drop_piece(tower, pieces, id) == true)
						colapsed = true;
				}
			}
		}
	}
	return (colapsed);
}

en_bool	colapse_tower(int ***tower, t_piece **pieces)
{
	int		id;
	int		checked[PIECES];
	en_bool	colapsed = false;

	(void) pieces;
	ft_arrset_int(checked, 0, PIECES);
	for (size_t i = 0; i < TOWER_SIZE; i++)
	{
		for (size_t j = 0; j < TOWER_WIDTH; j++)
		{
			for (size_t k = 0; k < TOWER_WIDTH; k++)
			{
				id = tower[i][j][k];
				if (id != 0 && checked[id] == 0)
				{
					checked[id] = 1;
					if (drop_piece(tower, pieces, id) == true)
						colapsed = true;
				}
			}
		}
	}
	return (colapsed);
}
