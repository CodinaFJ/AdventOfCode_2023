#include "AOC.h"

int	evaluate_card(char *card)
{
	char 		**strs;
	char		**winners;
	char		**included;
	en_bool		nbrs[99];
	int			i = 0;
	int			n = 0;

	ft_printf("Evaluate card: %s", card);
	ft_bzero(nbrs, 100 * sizeof(en_bool));
	strs = ft_split(card, '|');
	winners = ft_split(strs[0], ' ');
	included = ft_split(strs[1], ' ');
	while (included[i])
	{
		nbrs[ft_atoi(included[i])] = true;
		i++;
	}
	i = 0;
	printf("Winner numbers: ");
	while (winners[i])
	{
		if (nbrs[ft_atoi(winners[i])])
		{
			printf(" [%d] ", ft_atoi(winners[i]));
			n++;
		}
		i++;
	}
	free_strs(strs);
	free_strs(winners);
	free_strs(included);
	printf("  ->  Card value: %d\n", ft_pow(2, n - 1));
	return (ft_pow(2, n - 1));
}

int	main(int argc, char **argv)
{
	FILE	*f;
	char	str[500];
	char	*aux;
	long long		res = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		res += evaluate_card(ft_strchr(str, ':'));
	}
	fclose(f);
	ft_printf("\nResult: %d\n", res);
	exit (0);
}
