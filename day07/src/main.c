#include "AOC.h"


int	cmp_hand_strenght(t_hand *node1, t_hand *node2)
{
	if (node1->kind_strenght > node2->kind_strenght)
		return (1);
	else if (node1->kind_strenght == node2->kind_strenght)
	{
		for(int i = 0; i < 5; i++)
		{
			if (node1->cards[i] == node2->cards[i])
				continue ;
			else if (node1->cards[i] > node2->cards[i])
				return (1);
			else if (node1->cards[i] < node2->cards[i])
				return (0);
		}
	}
	else
		return (0);
	return (0);
}

t_list	*sort_list(t_list* lst, int (*cmp)(t_hand*, t_hand*))
{
	void	*overflow;
	t_list	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->content, lst->next->content)) == 0)
		{
			overflow = lst->content;
			lst->content = lst->next->content;
			lst->next->content = overflow;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

int	calculate_res(t_list *hands)
{
	t_hand	*hand;
	int		res = 0;
	int		i = 1;

	while (hands)
	{
		hand = hands->content;
		res += hand->bid * i;
		hands = hands->next;
		i++;
	}
	return (res);
}

int	main(int argc, char **argv)
{
	FILE			*f;
	char			str[500];
	char			*aux;
	long long		res = 0;
	t_list			*hands;

	if (argc != 2)
	{
		ft_printf("Invalid entry");
		return (1);
	}

	hands = NULL;
	f = fopen(argv[1], "r");
	while (feof(f) == 0)
	{
		aux = fgets(str, 500, f);
		if (aux == NULL) break;
		add_node(str, &hands);
	}
	hands = sort_list(hands, &cmp_hand_strenght);
	print_hand_list(hands);
	res = calculate_res(hands);
	printf("Result: %lld\n", res);
	fclose(f);
	exit (0);
}
