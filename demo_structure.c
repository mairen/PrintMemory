/*
Mai Ren
2016-09-12

This program shows how structures were stored in memory.
*/

#include "print_memory.c"

struct example
{
    int x;
    char y;
    char z;
};

int main()
{
    /* Define local variables */
    struct example test = {65535, 'a', 'b'};
    struct example test2;
    
    /* Print memory of both structures */
    printMemoryMultiFormat2(&test, sizeof(test), "test");    
    printMemoryMultiFormat2(&test2, sizeof(test2), "test2");

    /* Cleanup */
    return 0;
}

