#include "AOC.h"

void	*print_hand(void *printable_hand)
{
	t_hand *hand = (t_hand *) printable_hand;

	printf("\n");
	printf("[HAND]: ");
	for (int i = 0; i < 5; i++)
		printf("%d ", hand->cards[i]);
	printf("\n");
	printf("[BID]: %d\n", hand->bid);
	printf("[STRENGHT]: %d\n", hand->kind_strenght);
	printf("\n");
	return (printable_hand);
}

void	print_hand_list(t_list *list)
{
	t_list	*node;

	node = list;
	while (node != NULL)
	{
		print_hand(node->content);
		node = node->next;
	}
}

void	translate_cards(t_hand *hand, char *str)
{
	//printf("TRANSLATE CARDS: %s\n", str);
	hand->cards = ft_calloc(5, sizeof(int));
	for (int i = 0; i < 5; i++)
	{
		if (str[i] == 'A')
			hand->cards[i] = 0;
		else if (str[i] == 'K')
			hand->cards[i] = 1;
		else if (str[i] == 'Q')
			hand->cards[i] = 2;
		else if (str[i] == 'T')
			hand->cards[i] = 3;
		else if (str[i] == '9')
			hand->cards[i] = 4;
		else if (str[i] == '8')
			hand->cards[i] = 5;
		else if (str[i] == '7')
			hand->cards[i] = 6;
		else if (str[i] == '6')
			hand->cards[i] = 7;
		else if (str[i] == '5')
			hand->cards[i] = 8;
		else if (str[i] == '4')
			hand->cards[i] = 9;
		else if (str[i] == '3')
			hand->cards[i] = 10;
		else if (str[i] == '2')
			hand->cards[i] = 11;
		else if (str[i] == 'J')
			hand->cards[i] = 12;
	}
}


int	add_jokers(int joker_n, int strength)
{
	if (joker_n == 0)
		return (strength);

	if (strength == 2)
		return (1);
	else if (strength == 3)
		return (1);
	else if (strength == 4)
	{
		if (joker_n == 2)
			return (1);
		else
			return (2);
	}
	else if (strength == 5)
	{
		if (joker_n == 1)
			return (3);
		else if (joker_n == 2)
			return (2);
	}
	else if (strength == 6)
		return (4);
	else if (strength == 7)
		return (6);
	return (99);
}

/**
 * FIVE OF A KIND	- 1
 * FOUR OF A KIND	- 2
 * FULL HOUSE		- 3
 * THREE OF A KIND	- 4
 * TWO PAIR			- 5
 * ONE PAIR			- 6
 * HIGH CARD		- 7
*/
int		calculate_kind_strenght(t_hand *hand)
{
	char	cards[13]; //A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J
	int		max1 = 0;
	int		max2 = 0;

	//printf("CALCULATE STRENGHT: ");
	ft_bzero(cards, 13 * sizeof(char));
	for (int i = 0; i < 5; i++)
		cards[hand->cards[i]]++;
	for (int i = 0; i < 13; i++)
	{
		if ((cards[i] > max1 && max2 >= max1) || cards[i] > 3)
			max1 = cards[i];
		else if (cards[i] > max2)
			max2 = cards[i];
	}
	if (max1 == 5)
		return (1);
	else if (max1 == 4)
		return (add_jokers(cards[12], 2));
	else if (max1 == 3 || max2 == 3)
	{
		if (max2 == 2 || max1 == 2)
			return (add_jokers(cards[12], 3));
		else
			return (add_jokers(cards[12], 4));
	}
	else if (max1 == 2)
	{
		if (max2 == 2)
			return (add_jokers(cards[12], 5));
		else
			return (add_jokers(cards[12], 6));
	}
	else if (max2 == 2)
	{
		if (max1 == 2)
			return (add_jokers(cards[12], 5));
		else
			return (add_jokers(cards[12], 6));
	}
	else if (max1 == 1)
		return (add_jokers(cards[12], 7));
	else
		printf("[ERROR] Something has gone wrong");
	return (99);
}

void	add_node(char *str, t_list **hands)
{
	char	**strs;
	t_hand	*new_hand;

	//printf("ADD NODE: %s", str);
	new_hand = malloc(sizeof(t_hand));
	strs = ft_split(str, ' ');
	translate_cards(new_hand, strs[0]);
	new_hand->bid = atoi(strs[1]);
	new_hand->kind_strenght = calculate_kind_strenght(new_hand);
	if (*hands == NULL)
		*hands = ft_lstnew(new_hand);
	else
		ft_lstadd_back(hands, ft_lstnew(new_hand));
	free_strs(strs);
}