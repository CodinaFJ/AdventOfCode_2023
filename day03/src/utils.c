#include "day3.h"

void	free_strs(char	**strs)
{
	int	i = 0;

	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}