#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "scanner.h"
#include "hexnumber.h"

#define PARSER_FINISH_SYMBOL (27)

extern char nextSymbol;

static bool accept(char accepted)
{
    if (nextSymbol == accepted)
    {
        scanner_symbol();
        return true;
    }
    return false;
}

static bool match(char expected)
{
    if (!accept(expected))
    {
        printf("Error! Unexpected Symbol '%c', expected '%c'",
                nextSymbol,
                expected);
        exit(EXIT_FAILURE);
    }
    return true;
}

static bool is_hex(char symbol)
{
    return (symbol >= '0' && symbol <= '9') ||
            (symbol >= 'a' && symbol <= 'f') ||
            (symbol >= 'A' && symbol <= 'F');
}

static union HexNumber hex_value(char symbol)
{
    union HexNumber val = { .int32 = 0 };
    if (symbol >= '0' && symbol <= '9')
    {
        val.int32 = (int)symbol - '0';
    }
    else if (symbol >= 'a' && symbol <= 'f')
    {
        val.int32 = (int)symbol - 'a' + 10;
    }
    else if (symbol >= 'A' && symbol <= 'F')
    {
        val.int32 = (int)symbol - 'A' + 10;
    }
    else
    {
        printf("Error: Invalid Hex Value '%c'", symbol);
        exit(EXIT_FAILURE);
    }
    return val;
}

static union HexNumber A();
static union HexNumber B();
static union HexNumber C();
static union HexNumber E();
static union HexNumber AA(union HexNumber st);
static union HexNumber BB(union HexNumber st);
static union HexNumber EE(union HexNumber st);

static union HexNumber E(void)
{
    return EE(A());
}
static union HexNumber EE(union HexNumber st)
{
    if(accept('|'))
    {
        return EE(hex_num_or(st,A()));
    }
    else
    {
        return st;
    }
}
static union HexNumber A(void)
{
    return AA(B());
}
static union HexNumber AA(union HexNumber st)
{
    if(accept('^'))
    {
        return AA(hex_num_xor(st,B()));
    }
    else
    {
        return st;
    }
}
static union HexNumber B(void)
{
    return BB(C());
}
static union HexNumber BB(union HexNumber st)
{
    if (accept('&'))
    {
        return BB(hex_num_and(st,C()));
    }
    else
    {
        return st;
    } 
}
static union HexNumber C(void)
{
    if (accept('<'))
    {
        return hex_num_sal(C());
    }
    else if (accept('>'))
    {
        return hex_num_sar(C());
    }
    else if (accept('~'))
    {
        return hex_num_not(C());
    }
    else if (accept('('))
    {
        union HexNumber result = E();
        match(')');
        return result;
    }
    else if (is_hex(nextSymbol))
    {
        union HexNumber result = hex_value(nextSymbol);
        scanner_symbol(); // advance the symbol
        return result;
    }
    else
    {
        // Invalid terminal character. Silently fail.
        nextSymbol = PARSER_FINISH_SYMBOL;
        union HexNumber n = { .int32 = -1 };
        return n;
    }
}

int parser_parse(void)
{
    scanner_symbol();
    return E().int4;
}

bool parser_finished()
{
    return nextSymbol == PARSER_FINISH_SYMBOL;
}
