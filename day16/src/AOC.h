#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include <math.h>
#define SIZE 10

typedef struct s_vector
{
	int		*array;
	size_t	len;
}	t_vector;

void	free_strs(char	**strs);
int		strs_len(char **strs);
int		ft_pow(int nb, int power);
void 	ft_arrset(long long *arr, int d, long long len);
void 	print_array(long long *arr, long long len);
void	print_strs(char **strs);
void	add_line(char *str, char **strs);
void	reset_matrix(char **strs);
int		row_cmp(char **strs, int x, int y);
int		col_cmp(char **strs, int x, int y);
int		row_cmp_smudge(char **strs, int x, int y);
int		col_cmp_smudge(char **strs, int x, int y);