#include "AOC.h"

int	transform_char(char c, int current_value)
{
	current_value += c;
	current_value *= 17;
	current_value = current_value % 256;
	//printf("Transform %c Current value %d\n", c, current_value);
	return (current_value);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	//char			str[SIZE];
	//char			strs[SIZE][SIZE];
	int				c;
	int				res = 0;
	int				current_value = 0;

	//(void) strs;
	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		c = fgetc(f);
		if (feof(f)) break ;
		if (c == ',')
		{
			//printf("Sum current_value: %d\n", current_value);
			res += current_value;
			current_value = 0;
			continue ;
		}
		current_value = transform_char(c, current_value);
	}
	res += current_value;
	(void) res;
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
