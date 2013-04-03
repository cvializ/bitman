/* hexnumber.h */

#ifndef __HEXNUMBER_H__
#define __HEXNUMBER_H__

union HexNumber
{
    unsigned short int4 : 4;
    int int32;
};

union HexNumber hex_num_or(union HexNumber left, union HexNumber right);
union HexNumber hex_num_and(union HexNumber left, union HexNumber right);
union HexNumber hex_num_xor(union HexNumber left, union HexNumber right);
union HexNumber hex_num_not(union HexNumber left);
union HexNumber hex_num_sal(union HexNumber left);
union HexNumber hex_num_sar(union HexNumber left);

#endif
