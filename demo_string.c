/*
Mai Ren
2016-09-12

This program demonstrates the difference of sizeof and strlen a string.
*/

#include "print_memory.c"

int main()
{
    /* Define local variables */
    char str[] = "Hello world!";

    /* Print memory of str using sizeof */
    printMemoryMultiFormat2(str, sizeof(str), "str using sizeof");

    /* Print memory of str using strlen */
    printMemoryMultiFormat2(str, strlen(str), "str using strlen");
    
    /* Cleanup */
    return 0;
}
