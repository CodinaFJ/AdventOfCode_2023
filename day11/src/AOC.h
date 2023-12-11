#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include <math.h>
#define GALAXIES_N 448
#define READ_BUFFER 150
#define EXPANSION (1000000 - 1)

typedef struct s_galaxy
{
	int	row;
	int	column;
}	t_galaxy;


void	free_strs(char	**strs);
int		ft_pow(int nb, int power);
int		strs_len(char **strs);
void 	print_array(long long *arr, long long len);
void 	ft_arrset(int *arr, int d, long long len);

void	print_galaxies(t_galaxy *galaxies, int size);