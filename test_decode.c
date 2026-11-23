/* test_decode.c -- random messages: decode(encode(w)) must give w back. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "finite_field_arithmetic.h"

int encode(ff_elem *c, const ff_elem *w, size_t n, const ff_elem *a, size_t N, uint32_t p);
int decode(ff_elem *w, const ff_elem *c, size_t n, const ff_elem *a, size_t N, uint32_t p);

int main(void)
{
    uint32_t p = 101;
    size_t n = 3, N = 5;
    ff_elem a[5] = {0, 1, 2, 3, 4};      /* distinct points */
    ff_elem w[3], c[5], back[3];
    int ok = 1;

    srand(time(NULL));
    for (int t = 0; t < 10; t++) {
        for (size_t i = 0; i < n; i++)
            w[i] = rand() % p;           /* random message */

        encode(c, w, n, a, N, p);
        decode(back, c, n, a, N, p);

        printf("w = %u %u %u   decode = %u %u %u\n",
               w[0], w[1], w[2], back[0], back[1], back[2]);
        for (size_t i = 0; i < n; i++)
            if (w[i] != back[i])
                ok = 0;
    }

    printf(ok ? "OK\n" : "ERREUR\n");
    return !ok;
}
