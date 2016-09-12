/*
Mai Ren
2016-09-12

This program demonstrates how an integer was stored in memory.
*/

#include "print_memory.c"

int main()
{
    /* Define local variables */
    int i = 0;

    /* Print memory of integer i */
    printMemoryMultiFormat2(&i, sizeof(i), "i");

    /* Make a change to i */
    i = 1234;
    
    /* Print memory of integer i again */
    printMemoryMultiFormat2(&i, sizeof(i), "i");
    
    /* Cleanup */
    return 0;
}
