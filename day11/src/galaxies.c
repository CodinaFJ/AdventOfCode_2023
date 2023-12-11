#include "AOC.h"

void	print_galaxies(t_galaxy *galaxies, int size)
{
	int	i = 0;

	printf("\n\nPRINT GALAXIES:\n----------------------\n");
	while (i < size)
	{
		printf("Galaxy %d: row %d col %d\n", i, galaxies[i].row, galaxies[i].column);
		i++;
	}
	printf("----------------------\n\n");
}