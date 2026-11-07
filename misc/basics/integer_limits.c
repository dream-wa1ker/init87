#include <stdio.h>
#include <limits.h>
#include <stdint.h>

typedef unsigned _BitInt(128) uint128_t;
typedef unsigned _BitInt(1024) uint1024_t;
void print_u128(uint128_t n)
{
    char buf[40];
    size_t i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + n % 10);
        n /= 10;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
    puts("");
}


void print_u1024(uint1024_t n)
{
    char buf[1024];
    size_t i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + n % 10);
        n /= 10;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
    puts("");
}




int main(void) {
    printf("INT_MAX         = %d\n", INT_MAX);
    printf("UINT_MAX        = %u\n", UINT_MAX);
    printf("LONG_MAX        = %ld\n", LONG_MAX);
    printf("ULONG_MAX       = %lu\n", ULONG_MAX);
    printf("LLONG_MAX       = %lld\n", LLONG_MAX);
    printf("ULLONG_MAX      = %llu\n", ULLONG_MAX);
    uint128_t max = (uint128_t)-1;
    uint1024_t ultra = (uint1024_t)-1;
    printf("Unsigned 128 Bit Integer : ");
    print_u128(max);
    printf("Unsigned 1024 Bit Integer : ");
    print_u1024(ultra);

    return 0;
}
