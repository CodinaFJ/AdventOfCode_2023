// DISCLAIMER: This code is not entirely mine. I learned how to build this algorithm from: 
// https://github.com/PaigePalisade/AdventOfCode2023/blob/main/Solutions/day12part2.c

#include "AOC.h"

long long	chached_results[BUFFER_SIZE][BUFFER_SIZE];
long long	calculate_combinations(char *str, long long *string_match, long long str_idx, long long match_idx, long long str_len, long long match_len)
{
	long long	combs = 0;
	int			valid = 0;
	long long	set = 0;

	if (match_idx == match_len) //We are finished
	{
		return (1);
	}

	if (str_idx < str_len && chached_results[str_idx][match_idx] != -1)
		return (chached_results[str_idx][match_idx]);

	set = string_match[match_idx];
	for (long long i = str_idx; i <= str_len - set; i++)
	{
		valid = 1;
		// There are enough # and ? to fulfill condition
		for (long long j = 0; j < set; j++)
		{
			if (str[i + j] == '.')
				valid = 0;
		}

		// Cannot be valid with a # previous (number would be higher)
		if (i > 0 && str[i - 1] == '#')
			valid = 0;

		// Cannot be valid with a # after (number would be higher)
		if (i + set < str_len && str[i + set] == '#')
			valid = 0;

		// Last index. Cannot have # after the set
		if (match_idx == match_len - 1)
		{
			for (long long j = i + set + 1; j < str_len; j++)
			{
				if (str[j] == '#')
					valid = 0;
			}
		}

		// In this possition this set is valid, lets check the nexts
		if (valid == 1)
		{
			combs += calculate_combinations(str, string_match, i + set + 1, match_idx + 1, str_len, match_len);
		}

		// If we find a # and it is not in the combinations that we ahve already found then this combination is not valid all along
		if (str[i] == '#')
			break;
	}
	//printf("Calculate combinations: %s. Result: %d\n", str, combs);
	if (str_idx < str_len)
	{
		chached_results[str_idx][match_idx] = combs;
	}
	return (combs);
}

long long pre_calculate_combinations(char *str, char *string_match)
{
	long long		res;
	char			str_new[BUFFER_SIZE] = "";
	char			string_match_new[BUFFER_SIZE] = "";
	char 			*aux_str;
	long long		sets_arr[BUFFER_SIZE];
	long long		str_len;
	long long		sets_len = 0;

	ft_arrset(sets_arr, 0, BUFFER_SIZE);
	ft_strlcat(str_new, str, BUFFER_SIZE);
	ft_strlcat(str_new, "?", BUFFER_SIZE);
	ft_strlcat(str_new, str, BUFFER_SIZE);
	ft_strlcat(str_new, "?", BUFFER_SIZE);
	ft_strlcat(str_new, str, BUFFER_SIZE);
	ft_strlcat(str_new, "?", BUFFER_SIZE);
	ft_strlcat(str_new, str, BUFFER_SIZE);
	ft_strlcat(str_new, "?", BUFFER_SIZE);
	ft_strlcat(str_new, str, BUFFER_SIZE);
	ft_strlcat(string_match_new, string_match, BUFFER_SIZE);
	ft_strlcat(string_match_new, ",", BUFFER_SIZE);
	ft_strlcat(string_match_new, string_match, BUFFER_SIZE);
	ft_strlcat(string_match_new, ",", BUFFER_SIZE);
	ft_strlcat(string_match_new, string_match, BUFFER_SIZE);
	ft_strlcat(string_match_new, ",", BUFFER_SIZE);
	ft_strlcat(string_match_new, string_match, BUFFER_SIZE);
	ft_strlcat(string_match_new, ",", BUFFER_SIZE);
	ft_strlcat(string_match_new, string_match, BUFFER_SIZE);
	aux_str = string_match_new;

	//printf("Case: %s %s -> ", str_new, string_match_new);

	str_len = ft_strlen(str_new);

	while (*aux_str)
	{
		sets_arr[sets_len] = atoi(aux_str);
		sets_len++;
		while (*aux_str != ',' && *aux_str)
			aux_str++;
		if (*aux_str && *(aux_str + 1))
			aux_str += 1;
	}

	//print_array(sets_arr, sets_len);
	//printf("\n");

	for (long long i = 0; i < BUFFER_SIZE; i++) 
	{
		for (long long j = 0; j < BUFFER_SIZE; j++) 
		{
			chached_results[i][j] = -1;
		}
	}

	res = calculate_combinations(str_new, sets_arr, 0, 0, str_len, sets_len);
	//printf("Case: %s %s -> %lld\n", str_new, string_match_new, res);
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[BUFFER_SIZE];
	char			**strs;
	char			*aux;
	long long		res = 0;
	long long		sum = 0;
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
		res = pre_calculate_combinations(strs[0], ft_strtrim(strs[1], "\n"));
		printf("Case: %s -> %lld \n", str, res);
		sum += res;
		free_strs(strs);
	}
	printf("Result: %lld\n", sum);
	fclose(f);
	exit (0);
}
