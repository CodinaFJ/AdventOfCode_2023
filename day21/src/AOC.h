#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#define SIZE 500

typedef enum e_def_map_chars
{
	START = 'S',
	PLOT = '.',
	REACHED = 'O',
	STEPPED = 'X',
	ROCK = '#'
}	e_map_chars;

typedef enum e_def_consts
{
	STEPS_N = 26501365,
	MAP_SIZE = 131,
} e_consts;

typedef struct s_position
{
	int	i;
	int	j;
}	t_position;

//DAY21

//DAY21

void		free_strs(char	**strs);
int			strs_len(char **strs);
int			ft_pow(int nb, int power);
void 		ft_arrset(long long *arr, int d, long long len);
void 		print_array(long long *arr, long long len);
void		print_strs(char **strs);
void		add_line(char *str, char **strs);
void		reset_matrix(char **strs);
int			row_cmp(char **strs, int x, int y);
int			col_cmp(char **strs, int x, int y);
int			row_cmp_smudge(char **strs, int x, int y);
int			col_cmp_smudge(char **strs, int x, int y);
t_position	ft_strschr(char **strs, char c);
void		ft_strscpy(char **dst, char **src);
void		ft_strsncpy(char **dst, char **src, int size);
char		**ft_strsdup(char **strs);