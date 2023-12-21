#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#define SIZE 500
#define N_MODULES 58

typedef enum e_def_pulse
{
	NONE = 0,
	LOW = 1,
	HIGH = 2
}	e_pulse;

typedef enum e_def_module_type
{
	BROADCAST = 'b',
	FLIP_FLOP = '%',
	CONJUCTION = '&',
}	e_module_type;

typedef struct s_module
{
	char			*name;
	char			**outputs;
	e_pulse			*pulse;
	size_t			pulse_front;
	size_t			pulse_rear;
	e_module_type	module_type;
	en_bool			ff_state;
	t_hash_table	*cjt_inputs_states;
}	t_module;

typedef struct s_position
{
	int	i;
	int	j;
}	t_position;

//DAY20

void	print_module(t_module module);
void	print_modules(t_module *modules);
void	add_module(t_module *modules, size_t i, char *str);
void	fill_conjuction_inputs(t_module *modules, t_hash_table *modules_types_table, size_t size);
t_module	*find_module(t_module *modules, char *name);

//DAY20

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
//t_position	ft_strschr(char **strs, char c);
void		ft_strscpy(char **dst, char **src);
void		ft_strsncpy(char **dst, char **src, int size);