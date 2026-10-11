#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t something[8];

    something[0] = 0x00 & 1;

    printf("%u", something[0]);

    return 0;
}