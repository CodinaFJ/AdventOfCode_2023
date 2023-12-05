#include "AOC.h"
#define SEEDS_NUMBER 50

typedef struct s_map_line
{
	long long	dst;
	long long	src;
	long long	range;
}	t_map_line;

long long	min_arr(long long *arr, int len)
{
	long long min;
	
	min = LLONG_MAX;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] < min)
			min = arr[i];
	}
	return (min);
}

void read_seeds(long long *seeds, int *n_seeds, FILE *f)
{
	char	str[500];
	char	*aux;
	char	**auxs;

	fgets(str, 500, f);
	aux = ft_strchr(str, ':');
	auxs = ft_split((aux + 1), ' ');
	*n_seeds = strs_len(auxs);
	for (int i = 0; i < *n_seeds; i++)
		seeds[i] = atoll(auxs[i]);
	free_strs(auxs);
}

void	map_seeds(long long *src_seeds, long long *dst_seeds, char *str, int n_seeds)
{
	char		**strs;
	t_map_line	map_line;

	strs = ft_split(str, ' ');
	map_line.dst = atoll(strs[0]);
	map_line.src = atoll(strs[1]);
	map_line.range = atoll(strs[2]);
	for (int i = 0; i < n_seeds; i++)
	{
		if (src_seeds[i] >= map_line.src && src_seeds[i] < (map_line.src + map_line.range))
		{
			//printf("dst_seeds = src_seeds[%lld] + (map_line.dst[%lld] - map_line.src[%lld]) = %lld\n", src_seeds[i], map_line.dst, map_line.src, src_seeds[i] + (map_line.dst - map_line.src));
			dst_seeds[i] = src_seeds[i] + (map_line.dst - map_line.src);
		}
	}

	/*printf("[MAP SEEDS]\n");
	printf("src_seeds:\n");
	print_array(src_seeds, n_seeds);
	printf("dst_seeds:\n");
	print_array(dst_seeds, n_seeds);*/
}

void	transfer_seeds(long long *src_seeds, long long *dst_seeds, int n_seeds)
{
	for (int i = 0; i < n_seeds; i++)
	{
		if (dst_seeds[i] != -1)
		{
			src_seeds[i] = dst_seeds[i];
			dst_seeds[i] = -1;
		}
	}
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[500];
	char			*aux;
	long long		src_seeds[SEEDS_NUMBER];
	long long		dst_seeds[SEEDS_NUMBER];
	long long		res = 0;
	int				n_seeds;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	ft_bzero(src_seeds, sizeof(long long) * SEEDS_NUMBER);
	ft_arrset(dst_seeds, -1, SEEDS_NUMBER);
	f = fopen(argv[1], "r");
	read_seeds(src_seeds, &n_seeds, f);
	aux = fgets(str, 500, f);
	aux = fgets(str, 500, f);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		if (str[0] >= '0' && str[0] <= '9')
			map_seeds(src_seeds, dst_seeds, str, n_seeds);
		else if (str[0] >= 'a' && str[0] <= 'z')
			transfer_seeds(src_seeds, dst_seeds, n_seeds);
	}
	transfer_seeds(src_seeds, dst_seeds, n_seeds);
	res = min_arr(src_seeds, n_seeds);
	printf("\nResult: %lld\n", res);
	fclose(f);
	exit (0);
}
