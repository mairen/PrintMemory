# PrintMemory

This is a C program that given a memory address and a length, prints out each byte in that memory block in multiple formats to help understand what was stored in it.

I use this to teach C programming in class. This can also be used as a debugger when we don't have access to a better one.

Features:

    * Print out values in memory in multiple formats:
        HEX, DEC, BIN, Char, and name of the char if the char is special.
    * Auto adapt to different pointer sizes, and maintain the correct output format.
    * Optionally print out memory address as offset.
    * Build-in ASCII table and support correctly print out any char.
    * Auto detect size of memory allocation unit.
    * Optionally group lines by memory allocation unit.
    * Optionally print full memory allocation units.
    * Re-print title bar every 16 bytes(lines).
    
Call printASCIITable() to test printMemoryMultiFormat().

# Demos

int:

![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_int.png?raw=true)

string:

![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_string.png?raw=true)

structure:

![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_structure.png?raw=true)
