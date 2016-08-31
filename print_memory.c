/*
=================
Print out values in memory.

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

=================
Mai Ren
2015-10-25

Added:

    * Auto detect size of memory allocation unit.
    * Optionally group lines by memory allocation unit.
    * Optionally print full memory allocation units.

=================
Mai Ren
2015-10-05

First version:

Print out values in memory.

Features:
    * Print out values in memory in multiple formats:
        HEX, DEC, BIN, Char, and name of the char if the char is special.
    * Auto adapt to different pointer sizes, and maintain the correct output format.
    * Optionally print out memory address as offset.
    * Build-in ASCII table and support correctly print out any char.
    * Print memory values in groups, with adjustable group size.
    * Re-print title bar every 16 bytes(lines).
    
Call printASCIITable() to test printMemoryMultiFormat().
*/

#include <stdio.h>
#include <string.h>

/* Default settings */
#define B_PRINT_FULL_ALLOCATION_UNITS   0 /* Set to non-zero to align the start and end address to allocation unit boundaries. */ 
#define B_PRINT_ADDRESS_AS_OFFSET       1 /* Set to non-zero to print mem address as offset. */ 
#define B_SEPARATE_ALLOCATION_UNITS     1 /* Set to non-zero to insert an empty line after each memory allocation unit. */ 

struct {
    unsigned boundary1: 1;
    unsigned : 0;
    unsigned boundary2: 1;
} AllocationUnitSizeDetector;

int getAllocationUnitSize()
{
    return sizeof(AllocationUnitSizeDetector) / 2;
}

/* We assume a char is always 8 bits. */
void printBinary(char c)
{
    int count = 0;
    
    if (c == 0)
    {
        /* We just print one 0 if the value is 0, this makes it easier to read. */
        printf("       0");
    }
    else
    {
        count = 0;
        while (count++ < 8) {
            if (c & 128)
                printf("1");
            else
                printf("0");

            c <<= 1;
        }
    }
}

void getCharName(const char c, char* buf)
{
    const char *name[] = {
        "Null character",
        "Start of Header",
        "Start of Text",
        "End of Text",
        "End of Transmission",
        "Enquiry",
        "Acknowledgment",
        "Bell",
        "Backspace",
        "Horizontal Tab",
        "Line feed",
        "Vertical Tab",
        "Form feed",
        "Carriage return",
        "Shift Out",
        "Shift In",
        "Data Link Escape",
        "Device Control 1",
        "Device Control 2",
        "Device Control 3",
        "Device Control 4",
        "Negative Acknowledgement",
        "Synchronous idle",
        "End of Transmission Block",
        "Cancel",
        "End of Medium",
        "Substitute",
        "Escape",
        "File Separator",
        "Group Separator",
        "Record Separator",
        "Unit Separator",
        "Space",
        "Delete"
    };
    int index = (int)c;
    
    if (index >= 0 && index <= 32)
        strcpy(buf, name[index]);
    else if (index == 127)
        strcpy(buf, name[33]);
    else 
        buf[0] = '\0';
}

void getCharEscapeCode(const char c, char* buf)
{
    const char *escapeCode[] = {
        "\\0",
        "",
        "",
        "",
        "",
        "",
        "",
        "\\a",
        "\\b",
        "\\t",
        "\\n",
        "\\v",
        "\\f",
        "\\r",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "\\e",
        "",
        "",
        "",
        "",
        " ",
        "",
    };
    int index = (int)c;
    
    if (index < 0)
    {
        buf[0] = '\0';
    }
    else if (index >= 0 && index <= 32)
    {
        strcpy(buf, escapeCode[index]);
    }
    else if (index == 127)
    {
        strcpy(buf, escapeCode[33]);
    }
    else
    {
        buf[0] = c;
        buf[1] = '\0';
    }
}

/* Print out char c n times. */
void printChars(const char c, const int n)
{
    int i = 0;
    
    if (n <= 0)
        return;
    
    for (i = 0; i < n; i++)
        printf("%c", c);
}

/* Print out char ' ' n times. */
void printSpaces(const int n)
{
    printChars(' ', n);
}

/* Supported minimal length of mem addr is 8 characters, including the leading "0x". */
void printTitleBar(const int addressWidth)
{
    const char *titleStr1      = "Address ";
    const char *titleStr2      = "   HEX  DEC  BIN      Char \n";
    const char *titleLineStr1  = "--------";
    const char *titleLineStr2  = "   ---- ---- -------- -- ------------\n";

    int diff = 0;
    
    diff = addressWidth - 8;
        
    printf("%s", titleLineStr1);
    printChars('-', diff);
    printf("%s", titleLineStr2);
    printf("%s", titleStr1);
    printSpaces(diff);
    printf("%s", titleStr2);
    printf("%s", titleLineStr1);
    printChars('-', diff);
    printf("%s", titleLineStr2);
}

/* Show full length of memory address, and make sure "0x" was added to the front. */
void formatMemoryAddress(char *buf)
{
    int temp = 0;
    
    /*
    If the print out of %p does not contain "0x" in front,
    we clear out 2 spaces in front, and add "0x" there.
    */
    if (!(buf[0] == '0' && buf[1] == 'x'))
    {
        memmove(buf + 2, buf, strlen(buf) + 1);
        buf[0] = '0';
        buf[1] = 'x';
    }
    
    /* If necessary, insert '0's to the front to show full address. */
    temp =  2 + sizeof(void *) * 2 - strlen(buf);
    if (temp > 0)
    {
        memmove(buf + 2 + temp, buf + 2, strlen(buf) - 1);
        memset(buf + 2, '0', temp);
    }
}

/* Todo: printASMemoryAddress */

/* Print out the byte in each memory address in multiple formats. */
void printMemoryMultiFormat(
    const void  *startAddr,
    const int   length, 
    const int   bPrintFullAllocationUnits,
    const int   bPrintAddressAsOffset,
    const int   bSeparateAllocationUnits,
    const char  *name
    )
{
    /* Local variables */
    char *alignedStartAddr = (char *)startAddr;
    char *alignedEndAddr = (char *)startAddr + length - 1;
    int offset = 0;
    int temp = 0;
    char buf[3] = {0};
    char buf_large[1024] = {0};
    char *curPtr = NULL;

    /* Validate input parameters. */
    if (startAddr == NULL || length <= 0)
        return;

    /* Check if we need to start early. */
    if ((size_t)startAddr % getAllocationUnitSize() != 0)
        alignedStartAddr -= (size_t)startAddr % getAllocationUnitSize();
    
    /* Check if we need to end late. */
    if (((size_t)startAddr + length) % getAllocationUnitSize() != 0)
        alignedEndAddr += getAllocationUnitSize() - ((size_t)startAddr + length) % getAllocationUnitSize();
    
    /* Print a header section. */
    {
        printf("=======================================\n");
        
        printf("Print memory of: ");
        if (name != NULL)
            printf("%s\n", name);
        else
            printf("0x%p\n", startAddr);
        
        printf("Length = %d\n", length);

        if (alignedStartAddr != startAddr)
            printf("\nWarning: Start address was not aligned.\n\n");
    }

    for (curPtr = alignedStartAddr; curPtr <= alignedEndAddr; curPtr++)
    {
        offset = curPtr - (char *)startAddr;
        
        if (bPrintFullAllocationUnits == 0 && (offset < 0 || offset >= length))
            continue;
        
        /* Format memory address */
        sprintf(buf_large, "%p", curPtr);
        formatMemoryAddress(buf_large);
        
        /* Show memory address as offset. */
        if (bPrintAddressAsOffset != 0 && offset % 16 != 0)
        {
            memset(buf_large, ' ', strlen(buf_large) - 2);
            if (bSeparateAllocationUnits == 0 && offset % getAllocationUnitSize() == 0)
                sprintf(buf_large, "%+d", offset);
            else
                sprintf(buf_large, "%+5d", offset);
            memset(buf_large + strlen(buf_large), ' ', 1);
        }
            
        /* Print out title bar every 16 bytes. */
        /* 
        Todo: 
        
        Now we are assuming 16 is multiple of all possible 
        memory allocation unit sizes, this may not be true. 
        
        We need to change 16 to something that's dependent 
        on the size of the size of memory allocation unit, 
        so that we don't break the same memory allocation 
        unit into two parts.
        */
        if (offset % 16 == 0)
            printTitleBar(strlen(buf_large));
        /* Separate bytes into groups. */
        else if (bSeparateAllocationUnits != 0 && (curPtr - alignedStartAddr) % getAllocationUnitSize() == 0)
            printf("\n");
        
        /* Print memory addres */
        printf("%s", buf_large);
        
        /* Print separation between mem address and content. */
        if (offset >= 0 && offset < length)
            printf(" : ");
        else
            /* 
            In case we are printing full allocation units and 
            have expanded the range because of it, the extra 
            lines will be marked like this. 
            */
            printf("---");
        
        /* Print byte in HEX format */
        temp = 0;
        memcpy(&temp, curPtr, 1);
        printf("0x%02x", temp);   
    
        /* Print byte in DEC format */
        printf(" %4d ", *curPtr);
        printBinary(*curPtr);
        
        /* Print byte as a char */
        getCharEscapeCode(*curPtr, buf);
        printSpaces(3 - strlen(buf));
        printf("%s", buf);
        
        /* Print name of the char, if the char is special. */
        getCharName(*curPtr, buf_large);
        printf(" %s", buf_large);
        printf("\n");
    }
    
    printf("\n");
}

void printMemoryMultiFormat2(const void *startAddr, const int length, const char *name)
{
    printMemoryMultiFormat(
        startAddr,                      /* Start print from this address. */
        length,                         /* Print out this many bytes. */
        B_PRINT_FULL_ALLOCATION_UNITS,  /* bPrintFullAllocationUnits */
        B_PRINT_ADDRESS_AS_OFFSET,      /* bPrintAddressAsOffset */
        B_SEPARATE_ALLOCATION_UNITS,    /* bSeparateAllocationUnits */
        name
        );
}

void printMemoryMultiFormat3(const void *startAddr, const int length)
{
    printMemoryMultiFormat(
        startAddr,                      /* Start print from this address. */
        length,                         /* Print out this many bytes. */
        B_PRINT_FULL_ALLOCATION_UNITS,  /* bPrintFullAllocationUnits */
        B_PRINT_ADDRESS_AS_OFFSET,      /* bPrintAddressAsOffset */
        B_SEPARATE_ALLOCATION_UNITS,    /* bSeparateAllocationUnits */
        NULL
        );
}

void printASCIITable()
{
    char buf[128] = {0};
    int i = 0;
    
    for (i = 1; i < 128; i++)
        buf[i] = buf[i - 1] + 1;
    
    printMemoryMultiFormat2(buf, 128, "ASCII table");
}
