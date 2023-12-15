#include "AOC.h"

void	manage_lens(char *lens, t_hash_table *ht)
{
	char	key[SIZE];
	int		i = 0;

	while (lens[i] != '-' && lens[i] != '=')
	{
		key[i] = lens[i];
		i++;
	}
	key[i] = '\0';
	if (lens[i] == '-')
		ht_delete(ht, key);
	else if (lens[i] == '=')
	{
		i++;
		ht_insert(ht, key, &lens[i]);
	}
}

long long	calculate_powers(t_hash_table *ht)
{
	size_t		i = 0;
	size_t		j = 2;
	t_list		*bucket;
	long long	power = 0;

	while (i < HT_CAPACITY)
	{
		if (ht->items[i] == NULL)
		{
			i++;
			continue ;
		}
		power += (1 + i) * atoi(ht->items[i]->value);
		bucket = ht->overflow_buckets[i];
		j = 2;
		while (bucket != NULL)
		{
			power += (1 + i) * j * atoi(((t_ht_item *) bucket->content)->value);
			j++;
			bucket = bucket->next;
		}
		i++;
	}
	return (power);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	t_hash_table	*ht;
	char			str[SIZE];
	size_t			i = 0;
	int				c;
	int				res = 0;

	if (argc != 2)
	{
		printf("Invalid entry");
		return (1);
	}
	ht = create_table(HT_CAPACITY);
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		c = fgetc(f);
		if (feof(f)) break ;
		if (c == ',')
		{
			i = 0;
			//printf("Managing order: %s\n", str);
			manage_lens(str, ht);
			//printf("Finished managing order: %s\n", str);
			ft_bzero(str, SIZE);
			continue ;
		}
		str[i] = c;
		i++;
	}
	manage_lens(str, ht);
	print_table(ht);
	(void) res;
	res = calculate_powers(ht);
	printf("Result: %d\n", res);
	fclose(f);
	exit (0);
}
