#include "AOC.h"

int	***tower_dup(int ***tower_old)
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
				tower[i][j][k] = tower_old[i][j][k];
			}
		}
	}
	return (tower);
}

t_piece	*piece_dup(t_piece *piece)
{
	t_piece	*new_piece;

	if (piece == NULL)
		return (NULL);
	new_piece = malloc (sizeof(t_piece));
	new_piece->start = new_point3d_malloc(piece->start->x, piece->start->y, piece->start->z);
	new_piece->end = new_point3d_malloc(piece->end->x, piece->end->y, piece->end->z);
	return (new_piece);
}

int	try_chain_reaction(int ***tower_og, t_piece **pieces_og)
{
	t_piece **pieces;
	int	***tower;
	int	falls;

	tower = tower_dup(tower_og);
	pieces = malloc(sizeof(t_piece *) * PIECES);
	for (int i = 0; i < PIECES; i++)
	{
		pieces[i] = piece_dup(pieces_og[i]);
	}
	falls = colapse_tower_falls(tower, pieces);
	free_tower(tower);
	free_pieces(pieces);
	return (falls);
}

int	count_critical_pieces_falls(int ***tower, t_piece **pieces)
{
	int res = 0;
	int falls = 0;

	for (int i = 0; i < PIECES; i++)
	{
		if (pieces[i] == NULL)
			continue ;
		insert_piece(tower, pieces[i]->start, pieces[i]->end, 0);
		falls = try_chain_reaction(tower, pieces);
		insert_piece(tower, pieces[i]->start, pieces[i]->end, i);
		res += falls;
		printf("Removing piece [%d] gives %d falls\n", i, falls);
	}
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			**strs;
	int				***tower;
	t_piece			**pieces;
	int				i = 1;
	long long		res = 0;

	(void) res;
	(void) strs;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	pieces = malloc(sizeof(t_piece *) * PIECES);
	ft_bzero(pieces, sizeof(t_piece *) * PIECES);
	tower = create_tower();
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		aux = ft_strtrim(str, "\n");
		strs = ft_split(aux, '~');
		t_position3d *start =  get_point_from_str(strs[0]);
		t_position3d *end =  get_point_from_str(strs[1]);
		pieces[i] = create_piece(start, end);
		insert_piece(tower, start, end, i);
		i++;
		free(aux);
		free_strs(strs);
	}
	colapse_tower(tower, pieces);
	res = count_critical_pieces_falls(tower, pieces);
	printf("res: %lld\n", res);
	fclose(f);
	free_tower(tower);
	free_pieces(pieces);
	exit (0);
}
