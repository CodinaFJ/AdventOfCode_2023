#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#include <time.h>
#define SIZE 5000

typedef struct s_edge
{
	char	*vertex_a;
	char	*vertex_b;
	char	*vertex_a_og;
	char	*vertex_b_og;
	char	*chain_vertex_a;
	char	*chain_vertex_b;
}	t_edge;

typedef struct s_pos2d
{
	int	i;
	int	j;
}	t_pos2d;

//DAY25
t_edge		*new_edge(char *vertex_a, char *vertex_b);
void		*dup_edge(void *src);
int			edges_cmp(void *edge_a, void *edge_b);
void		free_edge(void *edge);
void		print_edge(t_edge *edge);
void		print_edges(t_list *edges);
void		print_edges_og(t_list *edges);
void		print_edge_chain(t_edge *edge);
void		print_edges_chains(t_list *edges);
int 		edge_contains_one_vertex(void *edge_a, void *vertex);
//DAY25

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
t_list		*ft_lst_remove(t_list *lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_dup(t_list *lst_src, void *(*dup)(void *));
void		*ft_lst_remove_at(t_list **lst, int index);
void		*ft_lst_pop(t_list **lst, void *content, int (*compare)(void *, void *));
t_list		*ft_lst_remove_all(t_list *lst, void *content, int (*compare)(void *, void *));
