#include "AOC.h"

long long	solve_strs(char **strs)
{
	size_t		i = 1;
	size_t		j = 0;
	int			acc = 0;
	int			aux = 0;

	while (strs[i] != NULL)
	{
		aux = row_cmp_smudge(strs, i - 1, i);
		if (aux <= abs('#' - '.'))
		{	
			j = 0;
			acc = 0;
			while (aux <= abs('#' - '.'))
			{
				aux = row_cmp_smudge(strs, i - 1 - j, i + j);
				acc += aux;
				if (i - 1 - j == 0 || strs[i + j + 1] == NULL)
				{
					if (acc == abs('#' - '.'))
					{
						reset_matrix((char **) strs);
						return (i * 100);
					}
					else
						break ;
				}
				j++;
			}
		}
		i++;
	}
	i = 1;
	while (strs[0][i])
	{
		aux = col_cmp_smudge(strs, i - 1, i);
		if (aux <= abs('#' - '.'))
		{
			j = 0;
			acc = 0;
			while (aux <= abs('#' - '.'))
			{
				aux = col_cmp_smudge(strs, i - 1 - j, i + j);
				acc += aux;
				if (i - 1 - j == 0 || strs[0][i + j + 1] == '\0')
				{
					if (acc == abs('#' - '.'))
					{
						reset_matrix((char **) strs);
						return (i);
					}
					else
						break ;
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			strs[SIZE][SIZE];
	char			*aux;
	long long		res = 0;

	if (argc != 2)
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
		if (str[0] == '\n')
		{
			res += solve_strs((char **) strs);
		}
		else
		{
			add_line(str, (char **) strs);
		}
	}
	res += solve_strs((char **) strs);
	(void) res;
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
