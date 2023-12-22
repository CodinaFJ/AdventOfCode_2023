#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "hash_table.h"
#include "queue.h"
#include <math.h>
#define SIZE 500
#define	TOWER_WIDTH 15
#define	TOWER_SIZE 400
#define	PIECES 1500

typedef struct s_tower_level
{
	int	**level;
}	t_tower_level;

typedef struct s_position3d
{
	int	x;
	int	y;
	int	z;
}	t_position3d;

typedef struct s_piece
{
	t_position3d	*start;
	t_position3d	*end;
}	t_piece;

typedef struct s_position
{
	int	i;
	int	j;
}	t_position;

//DAY22
int			***create_tower();
void		free_tower(int ***tower);
void		insert_piece(int ***tower, t_position3d *start, t_position3d *end, int n);
void		print_tower(int ***tower);
en_bool		colapse_tower(int ***tower, t_piece **pieces);
en_bool		try_colapse_tower(int ***tower, t_piece **pieces);
int			colapse_tower_falls(int ***tower, t_piece **pieces);

t_position3d	*get_point_from_str(char *str);
t_position3d	new_point3d(int x, int y, int z);
t_position3d	*new_point3d_malloc(int x, int y, int z);
t_piece			*create_piece(t_position3d *start, t_position3d *end);
void			free_piece(t_piece *piece);
void			free_pieces(t_piece **pieces);
//DAY22

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
t_position	ft_strschr(char **strs, char c);
void		ft_strscpy(char **dst, char **src);
void		ft_strsncpy(char **dst, char **src, int size);
char		**ft_strsdup(char **strs);