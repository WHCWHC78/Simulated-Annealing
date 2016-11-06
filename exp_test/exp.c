#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    uint16_t cnt;

    srand(time(NULL));

    for (cnt = 300; cnt > 0; --cnt) {
        int r = (-1) * (rand() % 28);
        printf("%03d) r: %03d, exp: %f\n", cnt, r, exp(((float)r) / cnt));
    }

    return 0;
}
