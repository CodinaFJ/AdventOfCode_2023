#include "AOC.h"

int	count_critical_pieces(int ***tower, t_piece **pieces)
{
	int res = 0;

	for (int i = 0; i < PIECES; i++)
	{
		if (pieces[i] == NULL)
			continue ;
		insert_piece(tower, pieces[i]->start, pieces[i]->end, 0);
		if (try_colapse_tower(tower, pieces) != true)
			res++;
		insert_piece(tower, pieces[i]->start, pieces[i]->end, i);
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
	res = count_critical_pieces(tower, pieces);
	printf("res: %lld\n", res);
	fclose(f);
	free_tower(tower);
	free_pieces(pieces);
	exit (0);
}
