#include <stdio.h>
#include "finite_field_arithmetic.h"
int encode(ff_elem *c, const ff_elem *w, size_t n, const ff_elem *a, size_t N, uint32_t p);
int main(void)
{
    ff_elem w[3] = {1, 2, 3}, a[5] = {0, 1, 2, 3, 4}, c[5];
    if (encode(c, w, 3, a, 5, 7)) return 1;
    for (int j = 0; j < 5; j++) printf("%u ", c[j]);   /* expected: 1 6 3 6 1 */
    printf("\n");
    return 0;
}
