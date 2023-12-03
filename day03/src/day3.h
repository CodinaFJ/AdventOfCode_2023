# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef enum
{
	max_red = 12,
	max_green = 13,
	max_blue = 14
}	max_cubes;

void	free_strs(char	**strs);

typedef struct s_cube_set
{
	int min_red;
	int min_green;
	int min_blue;
}	t_cube_set;