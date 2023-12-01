#include "day1.h"

char	*translate_digits(char *str)
{
	if (strncmp(str, "one", 3) == 0)
		return ("1");
	else if (strncmp(str, "two", 3) == 0)
		return ("2");
	else if (strncmp(str, "three", 5) == 0)
		return ("3");
	else if (strncmp(str, "four", 4) == 0)
		return ("4");
	else if (strncmp(str, "five", 4) == 0)
		return ("5");
	else if (strncmp(str, "six", 3) == 0)
		return ("6");
	else if (strncmp(str, "seven", 5) == 0)
		return ("7");
	else if (strncmp(str, "eight", 5) == 0)
		return ("8");
	else if (strncmp(str, "nine", 4) == 0)
		return ("9");
	else
		return ("\0");
}

void	subtitute_numbers(char *str)
{
	char	new_str[80] = "";
	int		i = 0;

	while (str[i])
	{
		if (ft_isdigit(str[i]))
			strncat(new_str, &str[i], 1);
		strncat(new_str, translate_digits(&str[i]), 1);
		i++;
	}
	strcpy(str, new_str);
}

int	strdgt(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (str[i] - '0');
		i++;
	}
	return (0);
}

int	strrdgt(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (ft_isdigit(str[len - 1]))
			return (str[len - 1] - '0');
		len--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*f;
	char	str[80];
	char	*aux;
	long long		res = 0;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 80, f);
		if (aux == NULL) break;
		subtitute_numbers(str);
		res += (strdgt(str) * 10);
		res += strrdgt(str);
	}
	fclose(f);
	ft_printf("Result: %d\n", res);
	return (0);
}