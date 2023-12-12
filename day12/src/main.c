#include "AOC.h"

int	calculate_string_value(char *str)
{
	int		value = 0;
	int		i = 0;

	while (str[i])
	{
		if (str[i] == ',')
		{
			i++;
			continue;
		}
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	//printf("calculate_string_value: %d\n", value);
	return (value);
}

en_bool	validate_string(char *str, char *string_match)
{
	size_t	i = 0;
	char	*aux_str;
	int		res = 0;
	int		aux = 0;

	aux_str = string_match;
	//printf("Validate string: %s [string_match = %s]\n", str, string_match);
	while (str[i])
	{
		if (str[i] == '#')
		{
			if (aux_str == NULL)
				return (0);
			else if (*aux_str == ',')
				aux_str++;
			aux = atoi(aux_str);
			if (aux == 0)
				return (0);
			res = 0;
			while (str[i] == '#')
			{
				res++;
				i++;
			}
			if (res != aux)
				return (0);
			aux_str = ft_strchr(aux_str, ',');
		}
		else
			i++;
	}
	if (aux_str != NULL)
		return (0);
	//printf("Successfull validation!");
	return (1);
}

int	calculate_combinations(char *str, size_t i, char *string_match)
{
	int	combs = 0;

	//printf("Calculate combinations: %s\n", str);
	if (str[i] == '\0')
		return (validate_string(str, string_match));
	if (str[i] != '?')
		combs += calculate_combinations(str, i + 1, string_match);
	else
	{
		str[i] = '.';
		combs += calculate_combinations(str, i + 1, string_match);
		str[i] = '#';
		combs += calculate_combinations(str, i + 1, string_match);
		str[i] = '?';
	}
	//printf("Calculate combinations: %s. Result: %d\n", str, combs);
	return (combs);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[BUFFER_SIZE];
	char			**strs;
	char			*aux;
	long long		res = 0;
	//int				string_value;

	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		strs = ft_split(str, ' ');
		res += calculate_combinations(strs[0], 0, ft_strtrim(strs[1], "\n"));
		free_strs(strs);
	}
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
