#include "AOC.h"

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[SIZE];
	char			*aux;
	char			strs[SIZE][SIZE];
	long long		res = 0;

	(void) res;
	(void) strs;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break ;
		add_line(str, (char **)strs);
	}
	print_strs((char **)strs);
	printf("res: %lld\n", res);
	fclose(f);
	exit (0);
}
