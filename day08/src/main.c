#include "AOC.h"

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[500];
	char			*aux;
	long long		res = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
	}
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
