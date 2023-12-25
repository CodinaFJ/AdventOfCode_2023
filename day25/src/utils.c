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
	strs = NULL;
	return ;
}

int	strs_len(char **strs)
{
	int	len;

	len = 0;
	while (strs[len] != NULL)
		len++;
	return (len);
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

void print_array(long long *arr, long long len)
{
	for (long long i = 0; i < len; i++)
	{
		printf("%lld ", arr[i]);
	}
	printf("\n");
}

void print_array_int(int *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void ft_arrset(long long *arr, int d, long long len)
{
	for (long long i = 0; i < len; i++)
	{
		arr[i] = d;
	}
}


void ft_arrset_int(int *arr, int d, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = d;
	}
}

void	print_strs(char **strs)
{
	int	i;

	printf("\nPRINT STRS\n------------------------------\n");
	i = 0;
	while (strs[i])
	{
		printf("%s\n", (char *) strs[i]);
		i++;
	}
	printf("------------------------------\n");

}
