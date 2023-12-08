# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef struct s_hand
{
	int		*cards;
	int		bid;
	int		kind_strenght; //five of a kind - 1 ... high card - 7
}	t_hand;

void	free_strs(char	**strs);
int		ft_pow(int nb, int power);
int		strs_len(char **strs);
void 	print_array(long long *arr, long long len);
void 	ft_arrset(long long *arr, int d, long long len);

void	add_node(char *str, t_list **hands);
void	print_hand_list(t_list *list);