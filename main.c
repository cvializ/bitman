#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(void)
{
    int result;    
    for(;;)
    {
        result = parser_parse();

        // We need to parse to decide if we're finished.
        // But we can't do pre- or post- test since
        // we don't want to print if it's finished
        if (parser_finished())
            break;

        printf(" = %x\n", result);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}
