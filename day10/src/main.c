#include "AOC.h"

void	move_pos(t_position *curr, movement move)
{
	if (move == NORTH)
		curr->i--;
	else if (move == EAST)
		curr->j++;
	else if (move == SOUTH)
		curr->i++;
	else if (move == WEST)
		curr->j--;
}

int	move_in_pipes(t_position *curr, movement move, char **map, int moves_n)
{
	char c;

	//printf("Move %d\n", move);
	move_pos(curr, move);
	c = map[curr->i][curr->j];
	if (c == START || move == NONE)
	{
		if (move == NONE)
			printf("ERROR\n");
		return (moves_n);
	}
	else if (move != SOUTH && (c == N_E || c == N_W || c == S_N))
			return (move_in_pipes(curr, NORTH, map, moves_n + 1));
	else if (move != WEST && (c == N_E || c == S_E || c == E_W))
			return (move_in_pipes(curr, EAST, map, moves_n + 1));
	else if (move != NORTH && (c == S_E || c == S_N || c == S_W))
			return (move_in_pipes(curr, SOUTH, map, moves_n + 1));
	else if (move != EAST && (c == N_W || c == S_W || c == E_W))
			return (move_in_pipes(curr, WEST, map, moves_n + 1));
	return (-1);
}

int	solve_pipes(char **strs)
{
	t_position	curr;
	movement	move;
	char 		c;

	curr = ft_strschr(strs, START);
	printf("Start position: %d, %d\n", curr.i, curr.j);
	move = NONE;
	for (int i = -1; i < 2; i ++)
	{
		for (int j = -1; j < 2; j ++)
		{
			if (abs(i + j) != 1)
				continue ;
			if (curr.i + i < 0 || curr.j + j < 0 || strs[curr.i + i] == NULL || strs[curr.i + i][curr.j + j] == '\0')
				continue ;
			c = strs[curr.i + i][curr.j + j];
			printf("Check char: %c\n", c);
			if (i == -1 && (c == S_E || c == S_N || c == S_W))
			{
				printf("Move north\n");
				move = NORTH;
				break ;
			}
			else if (j == 1 && (c == N_W || c == S_W || c == E_W))
			{
				printf("Move east\n");
				move = EAST;
				break ;
			}
			else if (i == 1 && (c == N_W || c == N_E || c == S_N))
			{
				printf("Move south\n");
				move = SOUTH;
				break ;
			}
			else if (j == -1 && (c == E_W || c == N_E || c == S_E))
			{
				printf("Move west\n");
				move = WEST;
				break ;
			}
		}
		if (move != NONE) break;
	}
	return (move_in_pipes(&curr, move, strs, 1));
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			strs[SIZE][SIZE];
	int				res = 0;

	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		add_line(str, (char **) strs);
	}
	(void) res;
	res = solve_pipes((char **) strs);
	printf("Result: %d\n", res / 2);
	fclose(f);
	exit (0);
}
