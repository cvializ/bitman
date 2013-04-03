/* hexnumber.c */

#include "hexnumber.h"

/*
 This document contains methods for storing
 numbers in 32 bits, but limiting any operations
 carried out on these numbers to four bits. 
*/
static union HexNumber math_four_bits(int value)
{
    union HexNumber hex = { .int32 = 0 };
    hex.int32 = value;
    hex.int32 = hex.int4;    
    return hex;
}

union HexNumber hex_num_or(union HexNumber left, union HexNumber right)
{
    return math_four_bits(left.int32 | right.int32);
}
union HexNumber hex_num_and(union HexNumber left, union HexNumber right)
{
    return math_four_bits(left.int32 & right.int32);
}
union HexNumber hex_num_xor(union HexNumber left, union HexNumber right)
{
    return math_four_bits(left.int32 ^ right.int32);
}
union HexNumber hex_num_not(union HexNumber left)
{
    return math_four_bits(~left.int32);
}
union HexNumber hex_num_sal(union HexNumber left)
{
    return math_four_bits(left.int32 << 1);
}
union HexNumber hex_num_sar(union HexNumber left)
{
    return math_four_bits(left.int32 >> 1);
}
