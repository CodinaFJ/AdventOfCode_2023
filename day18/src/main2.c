#include "AOC.h"

void	get_data(char *str, char *c, long long *n)
{
	char	*str_hx;
	char	**strs;

	strs = ft_split(str, ' ');
	str_hx = ft_strtrim(strs[2], "#\n()");
	free_strs(strs);
	*c = str_hx[5];
	str_hx[5] = '\0';
	*n = (long long) ft_atoi_base(str_hx, "0123456789abcdef");
} 

long long	dig_trench(t_trench_node *prev_node, char *str)
{
	t_trench_node	*new_node;
	long long		res = 0;
	long long		n = 0;
	char			c = 0;

	printf("Prev node: %lld, %lld\n", prev_node->x, prev_node->y);
	new_node = malloc(sizeof(t_trench_node));
	get_data(str, &c, &n);
	new_node->x = prev_node->x;
	new_node->y = prev_node->y;
	if (c == NORTH)
		new_node->y += n;
	else if (c == EAST)
		new_node->x += n;
	else if (c == SOUTH)
		new_node->y -= n;
	else if (c == WEST)
		new_node->x -= n;
	//printf("Line: %c, %lld -> New node: %lld, %lld\n", c, n, new_node->x, new_node->y);
	res = (prev_node->y + new_node->y) * (prev_node->x - new_node->x);
	res -= n;
	prev_node->x = new_node->x;
	prev_node->y = new_node->y;
	free(new_node);
	printf("New node: %lld, %lld\n", prev_node->x, prev_node->y);
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	t_trench_node	*prev_node;
	long long		res = 0;


	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	prev_node = malloc(sizeof(t_trench_node));
	prev_node->x = 0;
	prev_node->y = 0;
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, SIZE, f);
		if (aux == NULL) break ;
		res += dig_trench(prev_node, str);
	}
	(void) res;
	res += prev_node->y * prev_node->x;
	res = res / 2;
	res--;
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
