#include "AOC.h"
#include "hash_table.h"

int	main(int argc, char **argv)
{
	t_hash_table *ht = create_table(HT_CAPACITY);
	ht_insert(ht, (char *)"1", (char *)"First address");
    ht_insert(ht, (char *)"2", (char *)"Second address");
    ht_insert(ht, (char *)"Hel", (char *)"Third address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    ht_insert(ht, (char *)"Bbu", (char *)"Fith address");
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau"); // Collision!
    print_search(ht, (char *)"Bbu"); // Collision!
    print_table(ht);
    ht_delete(ht, (char *)"1");
    ht_delete(ht, (char *)"Cau");
    print_table(ht);
    free_htable(ht);
	(void) argc;
	(void) argv;
	return (0);
}
