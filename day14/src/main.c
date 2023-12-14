#include "AOC.h"

char	*ft_strchr_column(char **strs, size_t column, int c)
{
	size_t	i = 0;

	while (strs[i] != NULL)
	{
		if (strs[i][column] == c)
			return (&strs[i][column]);
		i++;
	}
	return (NULL);
}

size_t	get_strs_rows_n(char **strs)
{
	size_t i = 0;
	while(strs[i] != NULL)
		i++;
	return (i);
}

long long	weight_rocks(long long rocks_n, size_t rocks_start, size_t total_rows)
{
	long long r = 0;

	for (size_t i = 0; i < (size_t) rocks_n; i++)
	{
		//printf("Add rocks: %lld - (%lld + %lld)\n", total_rows, rocks_start, i);
		r += total_rows - (rocks_start + i);
	}
	return (r);
}

long long north_beam_load(char **strs)
{
	size_t		i = 0;
	size_t		j = 0;
	size_t		total_rows;
	long long	r = 0;

	total_rows = get_strs_rows_n(strs);

	// Iter all matrix through columns
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == 'O')
				r += total_rows - i;
			j++;
		}
		i++;
	}
	return (r);
}

void	set_rocks_north(char **strs, size_t rocks_start, long long rocks_n, size_t j, size_t i)
{
	size_t		m = 0;

	if (rocks_n == 0)
		return ;
	for (m = rocks_start; m < (size_t) rocks_start + rocks_n; m++)
		strs[m][i] = 'O';
	for (m = rocks_start + rocks_n; m < j; m++)
		strs[m][i] = '.';
}

void	set_rocks_west(char **strs, size_t rocks_start, long long rocks_n, size_t j, size_t i)
{
	size_t		m = 0;

	if (rocks_n == 0)
		return ;
	for (m = rocks_start; m < (size_t) rocks_start + rocks_n; m++)
		strs[i][m] = 'O';
	for (m = rocks_start + rocks_n; m < j; m++)
		strs[i][m] = '.';
}

void	set_rocks_south(char **strs, size_t rocks_start, long long rocks_n, size_t j, size_t i)
{
	size_t		m = 0;

	if (rocks_n == 0)
		return ;
	for (m = rocks_start; m < (size_t) j - rocks_n; m++)
		strs[m][i] = '.';
	for (m = j - rocks_n; m < j; m++)
		strs[m][i] = 'O';
}

void	set_rocks_east(char **strs, size_t rocks_start, long long rocks_n, size_t j, size_t i)
{
	size_t		m = 0;

	if (rocks_n == 0)
		return ;
	for (m = rocks_start; m < (size_t) j - rocks_n; m++)
		strs[i][m] = '.';
	for (m = j - rocks_n; m < j; m++)
		strs[i][m] = 'O';
}

void	tilt_north(char **strs)
{
	size_t		i = 0;
	size_t		j = 0;
	//size_t		total_rows;
	size_t		rocks_start = 0;
	long long	rocks_n = 0;

	//total_rows = get_strs_rows_n(strs);
	// Iter all matrix through columns
	while (strs[0][i])
	{
		j = 0;
		while (strs[j] != NULL)
		{
			if (strs[j][i] == '#')
			{
				set_rocks_north(strs, rocks_start, rocks_n, j, i);
				while(strs[j] != NULL && strs[j][i] == '#')
					j++;
				rocks_start = j;
				rocks_n = 0;
				continue ;
			}
			else if (strs[j][i] == 'O')
				rocks_n++;
			j++;
		}
		set_rocks_north(strs, rocks_start, rocks_n, j, i);
		rocks_start = 0;
		rocks_n = 0;
		i++;
	}
}

void	tilt_west(char **strs)
{
	size_t		i = 0;
	size_t		j = 0;
	//size_t		total_rows;
	size_t		rocks_start = 0;
	long long	rocks_n = 0;

	//total_rows = get_strs_rows_n(strs);
	// Iter all matrix through columns
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '#')
			{
				set_rocks_west(strs, rocks_start, rocks_n, j, i);
				while(strs[i][j] && strs[i][j] == '#')
					j++;
				rocks_start = j;
				rocks_n = 0;
				continue ;
			}
			else if (strs[i][j] == 'O')
				rocks_n++;
			j++;
		}
		set_rocks_west(strs, rocks_start, rocks_n, j, i);
		rocks_start = 0;
		rocks_n = 0;
		i++;
	}
}

void	tilt_south(char **strs)
{
	size_t		i = 0;
	size_t		j = 0;
	//size_t		total_rows;
	size_t		rocks_start = 0;
	long long	rocks_n = 0;

	//total_rows = get_strs_rows_n(strs);
	// Iter all matrix through columns
	while (strs[0][i])
	{
		j = 0;
		while (strs[j] != NULL)
		{
			if (strs[j][i] == '#')
			{
				set_rocks_south(strs, rocks_start, rocks_n, j, i);
				while(strs[j] != NULL && strs[j][i] == '#')
					j++;
				rocks_start = j;
				rocks_n = 0;
				continue ;
			}
			else if (strs[j][i] == 'O')
				rocks_n++;
			j++;
		}
		set_rocks_south(strs, rocks_start, rocks_n, j, i);
		rocks_start = 0;
		rocks_n = 0;
		i++;
	}
}

void	tilt_east(char **strs)
{
	size_t		i = 0;
	size_t		j = 0;
	//size_t		total_rows;
	size_t		rocks_start = 0;
	long long	rocks_n = 0;

	//total_rows = get_strs_rows_n(strs);
	// Iter all matrix through columns
	while (strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '#')
			{
				set_rocks_east(strs, rocks_start, rocks_n, j, i);
				while(strs[i][j] && strs[i][j] == '#')
					j++;
				rocks_start = j;
				rocks_n = 0;
				continue ;
			}
			else if (strs[i][j] == 'O')
				rocks_n++;
			j++;
		}
		set_rocks_east(strs, rocks_start, rocks_n, j, i);
		rocks_start = 0;
		rocks_n = 0;
		i++;
	}
}

void cycle(char **strs, int n)
{
	long long	lowest = LONG_MAX;
	long long	res;

	for (int i = 0; i < n; i++)
	{
		tilt_north(strs);
		tilt_west(strs);
		tilt_south(strs);
		tilt_east(strs);
		res = north_beam_load(strs);
		if (res < lowest)
			lowest = res;
	}
	//print_strs(strs);
	//printf("Min load = %lld\n", lowest);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			strs[SIZE][SIZE];
	char			*aux;
	long long		res = 0;

	if (argc != 3)
	{
		printf("Invalid entry");
		return (1);
	}

	reset_matrix((char **) strs);

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		add_line(str, (char **) strs);
	}
	cycle((char **) strs, atoi(argv[2]));
	res += north_beam_load((char **) strs);
	(void) res;
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
