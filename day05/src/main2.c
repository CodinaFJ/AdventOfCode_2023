#include "AOC.h"
#define SEEDS_NUMBER 500

typedef struct s_map_line
{
	long long	dst;
	long long	src_start;
	long long	src_end;
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

void read_seeds(long long *seeds, int *n_seeds_src, FILE *f)
{
	char		str[500];
	char		*aux;
	char		**auxs;

	fgets(str, 500, f);
	aux = ft_strchr(str, ':');
	auxs = ft_split((aux + 1), ' ');
	*n_seeds_src = strs_len(auxs);
	for (int i = 0; i < *n_seeds_src; i += 2)
	{
		seeds[i] = atoll(auxs[i]);
		seeds[i + 1] = atoll(auxs[i + 1]) + seeds[i];
	}
	free_strs(auxs);
}

void	map_seeds(long long *src_seeds, long long *dst_seeds, char *str, int n_seeds_src, int *n_seeds_dst)
{
	char		**strs;
	t_map_line	map_line;
	long long	new_range_start;
	long long	new_range_end;

	printf("\n[MAP SEEDS]\n");
	strs = ft_split(str, ' ');
	map_line.dst = atoll(strs[0]);
	map_line.src_start = atoll(strs[1]);
	map_line.range = atoll(strs[2]);
	map_line.src_end = map_line.src_start + map_line.range - 1;
	for (int i = 0; i < n_seeds_src; i += 2)
	{
		// All range is included
		if (src_seeds[i] >= map_line.src_start && src_seeds[i + 1] <= map_line.src_end)
		{
			dst_seeds[i] = src_seeds[i] + (map_line.dst - map_line.src_start);
			dst_seeds[i + 1] = src_seeds[i + 1] + (map_line.dst - map_line.src_start);
		}
		// Seed range overlaps higher
		else if (src_seeds[i] >= map_line.src_start && src_seeds[i] <= map_line.src_end)
		{
			// Transformed range is the new created
			new_range_start = src_seeds[i] + (map_line.dst - map_line.src_start);
			new_range_end = map_line.dst + map_line.range - 1;
			dst_seeds[*n_seeds_dst] = new_range_start;
			dst_seeds[(*n_seeds_dst) + 1] = new_range_end;
			(*n_seeds_dst) += 2;

			// Modify current range for future transformation
			src_seeds[i] = map_line.src_end + 1;
		}
		// Seed range overlaps smaller
		else if (src_seeds[i + 1] >= map_line.src_start && src_seeds[i + 1] <= map_line.src_end)
		{
			new_range_start = map_line.dst;
			new_range_end = src_seeds[i + 1] + (map_line.dst - map_line.src_start);
			dst_seeds[*n_seeds_dst] = new_range_start;
			dst_seeds[(*n_seeds_dst) + 1] = new_range_end;
			(*n_seeds_dst) += 2;

			// Modify current range for future transformation
			src_seeds[i + 1] = map_line.src_start - 1;
		}
	}
	print_array(src_seeds, (int) n_seeds_src);
	print_array(dst_seeds, (int) *n_seeds_dst);
	printf("\n");
}

void	transfer_seeds(long long *src_seeds, long long *dst_seeds, int *n_seeds_src, int n_seeds_dst)
{
	*n_seeds_src = n_seeds_dst;
	for (int i = 0; i < n_seeds_dst; i++)
	{
		if (dst_seeds[i] != -1)
		{
			src_seeds[i] = dst_seeds[i];
			dst_seeds[i] = -1;
		}
	}
	printf("\n[TRANSFER SEEDS]\n");
	print_array(src_seeds, (int) *n_seeds_src);
	print_array(dst_seeds, (int) n_seeds_dst);
	printf("\n");
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[500];
	char			*aux;
	long long		src_seeds[(SEEDS_NUMBER)];
	long long		dst_seeds[(SEEDS_NUMBER)];
	long long		res = 0;
	int				n_seeds_src;
	int				n_seeds_dst;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	ft_bzero(src_seeds, sizeof(long long) * (SEEDS_NUMBER));
	ft_arrset(dst_seeds, -1, (SEEDS_NUMBER));
	f = fopen(argv[1], "r");
	read_seeds(src_seeds, &n_seeds_src, f);
	n_seeds_dst = n_seeds_src;
	aux = fgets(str, 500, f);
	aux = fgets(str, 500, f);
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		if (str[0] >= '0' && str[0] <= '9')
			map_seeds(src_seeds, dst_seeds, str, n_seeds_src, &n_seeds_dst);
		else if (str[0] >= 'a' && str[0] <= 'z')
			transfer_seeds(src_seeds, dst_seeds, &n_seeds_src, n_seeds_dst);
	}
	transfer_seeds(src_seeds, dst_seeds, &n_seeds_src, n_seeds_dst);
	res = min_arr(src_seeds, n_seeds_src);
	printf("\nResult: %lld\n", res);
	fclose(f);
	exit (0);
}
