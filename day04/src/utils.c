#include "AOC.h"

void	free_strs(char	**strs)
{
	int	i = 0;

	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}

int	ft_pow(int nb, int power)
{
	if (power == 1)
		return (nb);
	else if (power == 0)
		return (1);
	else if (power < 0 || nb == 0)
		return (0);
	return (nb * ft_pow(nb, power - 1));
}
