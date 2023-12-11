#include "AOC.h"

long long	calculate_distances(const t_galaxy *galaxies, const int size)
{
	int			i;
	int 		j;
	long long	res = 0;

	for (i = 0; i < size; i++)
	{
		for (j = (i + 1); j < size; j++)
		{
			res += abs(galaxies[i].row - galaxies[j].row);
			res += abs(galaxies[i].column - galaxies[j].column);
		}
	}
	return (res);
}

void	expand_universe(int *empty_rows, int *empty_cols,t_galaxy *galaxies, const int size)
{
	int	i = 1;

	while (i < READ_BUFFER)
	{
		empty_rows[i] += empty_rows[i - 1];
		empty_cols[i] += empty_cols[i - 1];
		i++;
	}

	for (i = 0; i < size; i++)
	{
		galaxies[i].row += (empty_rows[galaxies[i].row] * EXPANSION);
		galaxies[i].column += (empty_cols[galaxies[i].column] * EXPANSION);
		
	}
}

void	add_galaxies_from_line(t_galaxy *galaxies, int *galaxy_index, char *str, int row, int *empty_rows, int *empty_cols)
{
	int	col = 0;

	while (str[col])
	{
		if (str[col] == '#')
		{
			galaxies[*galaxy_index].row = row;
			galaxies[*galaxy_index].column = col;
			empty_rows[row] = 0;
			empty_cols[col] = 0;
			(*galaxy_index)++;
		}
		col++;
	}
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[READ_BUFFER];
	char			*aux;
	t_galaxy		galaxies[GALAXIES_N];
	int				galaxy_index = 0;
	int				row = 0;
	int				empty_rows[READ_BUFFER];
	int				empty_cols[READ_BUFFER];
	long long		res = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}
	ft_bzero(galaxies, sizeof(t_galaxy) * GALAXIES_N);
	ft_arrset(empty_rows, 1, READ_BUFFER);
	ft_arrset(empty_cols, 1, READ_BUFFER);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, READ_BUFFER, f);
		if (aux == NULL) break;
		add_galaxies_from_line(galaxies, &galaxy_index, str, row, empty_rows, empty_cols);
		row++;
	}
	print_galaxies(galaxies, galaxy_index);
	expand_universe(empty_rows, empty_cols, galaxies, galaxy_index);
	print_galaxies(galaxies, galaxy_index);
	res = calculate_distances(galaxies, galaxy_index);
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
