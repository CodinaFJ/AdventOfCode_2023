#include "AOC.h"

int	evaluate_card(char *card, int *cards, int idx)
{
	char 		**strs;
	char		**winners;
	char		**included;
	en_bool		nbrs[99];
	int			i = 0;
	int			j = 0;
	int			n = 0;

	//printf("\nEvaluate card: %s", card);
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
	//printf("Winner numbers: ");
	while (winners[i])
	{
		if (nbrs[ft_atoi(winners[i])])
		{
			//printf(" [%d] ", ft_atoi(winners[i]));
			n++;
		}
		i++;
	}
	i = 1;
	while (i <= n)
	{
		j = 0;
		while (j < cards[idx])
		{
			cards[idx + i]++;
			j++;
		}
		i++;
	}
	free_strs(strs);
	free_strs(winners);
	free_strs(included);
	return (n);
}

int	main(int argc, char **argv)
{
	FILE	*f;
	char	str[500];
	char	*aux;
	long long		res = 0;
	int		res2;
	int		cards[220];
	int		i = 0;
	int		j = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}
	while (i < 220)
	{
		cards[i] = 1;
		i++;
	}
	i = 0;
	cards[0] = 1;
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		if (cards[i] == 0)	break;
		res2 = evaluate_card(ft_strchr(str, ':'), cards, i);
		if (res2 == 0 && cards[i + 1] == 0)
			break ;
		i++;
	}
	fclose(f);
	while (j < i)
	{
		//printf("Card[%d]: %d\n", j, cards[j]);
		res += cards[j];
		j++;
	}
	printf("\nResult: %lld\n", res);
	exit (0);
}
