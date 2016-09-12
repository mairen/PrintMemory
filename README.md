# PrintMemory

This is a C program that given a memory address and a length, prints out each byte in that memory in multiple formats to help understand what was stored in it.

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

1. int:
![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_int.png?raw=true)

2. string:
![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_string.png?raw=true)

3. structure:
![Screenshot](https://github.com/mairen/PrintMemory/blob/master/Screenshots/demo_structure.png?raw=true)
