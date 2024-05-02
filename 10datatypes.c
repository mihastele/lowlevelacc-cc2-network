#include <stdio.h>

int main(int argc, char *argv[])
{

    // signed types (can be negative)
    int x;           // 4 bytes (32 bits) depends on the architecture
    char y;          // 1 byte (8 bits)
    short z;         // 2 bytes (16 bits)
    int a;           // 4 bytes (32 bits) depends on the architecture
    long long int l; // 8 bytes (64 bits)

    float f;  // 4 bytes (32 bits)
    double d; // 8 bytes (64 bits)

    // unsigned types (cannot be negative)
    unsigned int ux;           // 4 bytes (32 bits) depends on the architecture
    unsigned char uy;          // 1 byte (8 bits)
    unsigned short uz;         // 2 bytes (16 bits)
    unsigned int ua;           // 4 bytes (32 bits) depends on the architecture
    unsigned long long int ul; // 8 bytes (64 bits)

    // unix types
    size_t s; // 8 bytes (64 bits)

    // unsigned
    unsigned int i = 0;
    // casting unsigned to signed
    int si = (int)i;
    // casting big number would return a negative number

    // not recommended from larger to smaller cast
    unsigned int bigX = 0xfffffefe;
    short kindaBigX = (short)bigX;

    short short2 = -1;
    int wasashort = (int)short2;

    // casting pointers
    short *ptr = (short *)argv[0];

    return 0;
}