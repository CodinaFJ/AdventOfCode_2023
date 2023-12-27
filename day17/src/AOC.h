#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#define SIZE 500

typedef enum e_movement
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NONE
}	t_movement;

typedef struct s_node
{
	int				i;
	int				j;
	int				cost;
	t_movement		current_movement;
	int				straight_movements;
}	t_node;

typedef struct s_pos2d
{
	int	i;
	int	j;
}	t_pos2d;

//DAY17

//DIJKSTRA
void		dijkstra_find_path(int **map, int size, t_pos2d start, t_pos2d end, int min_movements, int max_movements);
t_node		*new_node(int i, int j, int cost, t_movement movement, int straight_movements);
t_node		***create_nodes_matrix(int size, int **map);
void		free_nodes_matrix(t_node ***node_matrix);
void		print_node_matrix_costs(t_node ***node_matrix);
void		print_nodes_list(t_list *list);
void 		print_array_path(int *arr, int len);
t_node		*node_dup(t_node *node);
int			node_cmp(void *node_a, void *node_b);
//DAY17

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

// LISTS
int			ft_lst_contains(t_list *lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_remove(t_list *lst, void *content);
