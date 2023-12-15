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

int	move_in_pipes(t_position *curr, movement move, char **map, int moves_n, char **new_map)
{
	char c;

	//printf("Move %d\n", move);
	move_pos(curr, move);
	new_map[curr->i][curr->j] = START;
	c = map[curr->i][curr->j];
	if (c == START || move == NONE)
	{
		if (move == NONE)
			printf("ERROR\n");
		return (moves_n);
	}
	else if (move != SOUTH && (c == N_E || c == N_W || c == S_N))
			return (move_in_pipes(curr, NORTH, map, moves_n + 1, new_map));
	else if (move != WEST && (c == N_E || c == S_E || c == E_W))
			return (move_in_pipes(curr, EAST, map, moves_n + 1, new_map));
	else if (move != NORTH && (c == S_E || c == S_N || c == S_W))
			return (move_in_pipes(curr, SOUTH, map, moves_n + 1, new_map));
	else if (move != EAST && (c == N_W || c == S_W || c == E_W))
			return (move_in_pipes(curr, WEST, map, moves_n + 1, new_map));
	return (-1);
}

en_bool	is_in_loop(char *str, char *new_str, int j)
{
	int		count = 0;
	int		aux = 0;
	char	c;
	char	c_new;

	for (int i = 0; i < j; i++)
	{
		c = str[i];
		c_new = new_str[i];
		if (c_new != START)
			continue ;
		if (c == S_N)
			count++;
		else if (c == S_E || c == START)
			aux++;
		else if (c == N_E)
			aux--;
		else if (c == N_W)
			aux++;
		else if (c == S_W)
			aux--;
		if (abs(aux) == 2)
		{
			aux = 0;
			count++;
		}
	}
	if (count % 2 == 0)
	{
		//printf("String: %s -> Is %d in loop?: NO\n", str, j);
		new_str[j] = 'O';
		return (false);
	}
	else
	{
		//printf("String: %s -> Is %d in loop?: YES\n", str, j);
		new_str[j] = 'I';
		return (true);
	}
}

int count_tiles_inside(char **map, char **new_map)
{
	int	res = 0;
	
	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (new_map[i][j] == START)
				continue ;
			if (is_in_loop(map[i], new_map[i], j))
				res++;
		}
	}
	return (res);
}

int	solve_pipes(char **strs)
{
	t_position	curr;
	movement	move;
	char		**new_strs;
	int			len;
	char 		c;

	len = strs_len(strs);
	new_strs = malloc(sizeof(char *) * (len + 1));
	new_strs[len] = NULL;
	for (int i = 0; strs[i] != NULL; i++)
		new_strs[i] = ft_strdup(strs[i]);
	//print_strs(strs);
	curr = ft_strschr(strs, START);
	//printf("Start position: %d, %d\n", curr.i, curr.j);
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
			//printf("Check char: %c\n", c);
			if (i == -1 && (c == S_E || c == S_N || c == S_W))
			{
				//printf("Move north\n");
				move = NORTH;
				break ;
			}
			else if (j == 1 && (c == N_W || c == S_W || c == E_W))
			{
				//printf("Move east\n");
				move = EAST;
				break ;
			}
			else if (i == 1 && (c == N_W || c == N_E || c == S_N))
			{
				//printf("Move south\n");
				move = SOUTH;
				break ;
			}
			else if (j == -1 && (c == E_W || c == N_E || c == S_E))
			{
				//printf("Move west\n");
				move = WEST;
				break ;
			}
		}
		if (move != NONE) break;
	}
	move_in_pipes(&curr, move, strs, 1,(char **)  new_strs);
	for (int i = 0; new_strs[i] != NULL; i++)
	{
		for (int j = 0; new_strs[i][j]; j++)
		{
			if (new_strs[i][j] != START)
				new_strs[i][j] = '.';
		}
	}
	len = count_tiles_inside(strs, (char **) new_strs);
	print_strs((char **)  new_strs);
	free_strs(new_strs);
	printf("Tiles counted: %d\n", len);
	return (len);
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
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
