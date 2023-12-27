#include "AOC.h"

int	calc_collision(t_line *line1, t_line *line2, double min_n, double max_n)
{
	float x;
	float y;

	printf("\nLines:\n");
	print_line(line1);
	printf("\n");
	print_line(line2);
	if (fabs(line1->m - line2->m) < 0.00001)
	{
		// printf("\nLines:\n");
		// print_line(line1);
		// printf("\n");
		// print_line(line2);
		printf("\nAre parallel\n");
		return (0);

	}
	x = (line2->n - line1->n) / (line1->m - line2->m);
	y = (line1->m * x) + line1->n;
	if ((line1->vx > 0 && x < line1->x) || (line1->vx < 0 && x > line1->x) || (line1->vy > 0 && y < line1->y) || (line1->vy < 0 && y > line1->y))
	{
		printf("\nCrossed in the past\n");
		return (0);
	}
	else if ((line2->vx > 0 && x < line2->x) || (line2->vx < 0 && x > line2->x) || (line2->vy > 0 && y < line2->y) || (line2->vy < 0 && y > line2->y))
	{
		printf("\nCrossed in the past\n");
		return (0);
	}
	if (x < min_n || x > max_n || y < min_n || y > max_n)
	{
		printf("\nCross outside of test area\n");
		return (0);
	}
	(void) min_n;
	(void) max_n;
	printf("\nCross at: x = %f y = %f\n", x, y);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	t_line			**lines;
	char			*aux;
	long long		res = 0;
	int				i = 0;

	(void) res;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	lines = malloc(sizeof(t_line *) * 310);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		aux = ft_strtrim(str, "\n");
		lines[i] = calc_line(ft_split(aux, '@'));
		i++;
	}
	lines[i] = NULL;
	for (i = 0; lines[i] != NULL; i++)
	{
		for (int j = i + 1; lines[j] != NULL; j++)
		{
			res += calc_collision(lines[i], lines[j], 7, 27);
		}
	}
	printf("\n[SOLUTION] -> %lld\n", res);
	fclose(f);
	exit (0);
}
