#include "AOC.h"

en_bool	is_vector_zeros(t_vector *vector)
{
	for (size_t i = 0; i < vector->len; i++)
	{
		if (vector->array[i] != 0)
			return (false);
	}
	return (true);
}

void str_to_vector(char *str, t_vector *vector)
{
	char	**strs;
	size_t	i = 0;

	strs = ft_split(str, ' ');
	for (i = 0; strs[i] != NULL; i++)
		vector->array[i] = atoi(strs[i]);
	vector->len = i;
	free_strs(strs);
}

int	predict_value(t_vector *vector)
{
	t_vector	new_vector;
	int			new_arr[SIZE];
	int			aux = 0;
	size_t		i = 0;

	new_vector.len = 0;
	new_vector.array = new_arr;
	ft_bzero(new_arr, SIZE);
	while (i < vector->len - 1)
	{
		new_arr[i] = vector->array[i + 1] - vector->array[i];
		i++;
	}
	new_vector.len = i;
	if (!is_vector_zeros(&new_vector))
	{
		aux = predict_value(&new_vector);
	}
	return (vector->array[0] - aux);
}

int	solve_line(char *str)
{
	t_vector	vector;
	int			array[SIZE];
	int			r;

	vector.array = array;
	vector.len = 0;
	str_to_vector(str, &vector);
	r = predict_value(&vector);
	//printf("Line: %s -> %d\n", str, r);
	return (r);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			strs[SIZE][SIZE];
	char			*aux;
	int				res = 0;

	(void) strs;
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
		res += solve_line(str);
	}
	(void) res;
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
