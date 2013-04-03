#include <stdio.h>
#include <stdbool.h>

char nextSymbol = '\0';

char scanner_symbol(void)
{
    fscanf(stdin, "%c", &nextSymbol);

    if (nextSymbol == '\n' || nextSymbol == '\r' || nextSymbol == '\0')
    {
        return '\0';
    }
    else
    {
        // There's probably a better way to print the output,
        // but there's probably not one as simple.
        // KISS.
        printf("%c", nextSymbol);
        return nextSymbol;
    }
}
