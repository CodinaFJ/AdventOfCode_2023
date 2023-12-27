#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#include <time.h>
#include <gsl/gsl_multiroots.h>
#define SIZE 5000

typedef struct s_line
{
	double	x;
	double	y;
	double	z;
	double	vx;
	double	vy;
	double	vz;
	double	m;
	double	n;
}	t_line;

typedef struct s_equation
{
	double	**pos;
	double	**vel;
}	t_equation;

typedef struct s_pos2d
{
	int	i;
	int	j;
}	t_pos2d;

//DAY24
t_line	*calc_line(char **strs);
void	print_lines(t_line **lines);
void	print_line(t_line *line);
void	print_line_r3(t_line *line);

//DAY24

void		free_strs(char	**strs);
int			strs_len(char **strs);
int			ft_pow(int nb, int power);
void 		ft_arrset(long long *arr, int d, long long len);
void 		ft_arrset_int(int *arr, int d, int len);
void 		print_array(long long *arr, long long len);
void 		print_array_int(int *arr, int len);
void		print_strs(char **strs);
void		add_line(char *str, char **strs);
void		reset_matrix(char **strs);
int			row_cmp(char **strs, int x, int y);
int			col_cmp(char **strs, int x, int y);
int			row_cmp_smudge(char **strs, int x, int y);
int			col_cmp_smudge(char **strs, int x, int y);
t_pos2d		ft_strschr(char **strs, char c);
void		ft_strscpy(char **dst, char **src);
void		ft_strsncpy(char **dst, char **src, int size);
char		**ft_strsdup(char **strs);
char		*ft_strcat(char *dest, char *src);

// LISTS
int			ft_lst_contains(t_list *lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_remove(t_list *lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_dup(t_list *lst_src, void *(*dup)(void *));
void		*ft_lst_remove_at(t_list **lst, int index);
void		*ft_lst_pop(t_list **lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_remove_all(t_list *lst, void *content, int (*compare)(void *, void *));
