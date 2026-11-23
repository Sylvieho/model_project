/*
 * decode.c -- Task 1.2: Reed-Solomon decoding by Lagrange interpolation.
 *
 * W(x) = sum_{i<n} c_i * L_i(x),   L_i(x) = prod_{j != i} (x - a_j) / (a_i - a_j)
 *
 * The coefficients of W are the letters w_0, ..., w_{n-1} of the message.
 *
 *   w : output, length n
 *   c : codeword, length N (only the first n entries are used)
 *   a : interpolation points, length N (pairwise distinct, n < N)
 *   p : the prime
 * Returns 0 on success, -1 on invalid input or allocation failure,
 * -2 if two of the first n points are equal.
 */
#include <stdlib.h>
#include <string.h>
#include "finite_field_arithmetic.h"

int decode(ff_elem *w, const ff_elem *c, size_t n,
           const ff_elem *a, size_t N, uint32_t p)
{
	/* we verify the entry parameters. */
    if(!w || !c || !a || n == 0 || n >= N){
        return -1;
	}
    ff_elem *num = malloc(n * sizeof(ff_elem));     /* coefficients of prod_{j != i} (x - a_j) */
    ff_elem *res = malloc(n * sizeof(ff_elem));      /* W(x), starts at 0 */
    if(!num || !res) {
        free(num); 
        free(res);
        return -1;
    }
    for(size_t k = 0; k<n; k++){
    	res[k] = 0;
    }

    int status = 0;
    for (size_t i = 0; i < n && status == 0; i++) {
        /* Numerator polynomial, starts at 1; denominator, starts at 1. */
        num[0] = 1;
        size_t deg = 0;
        ff_elem denom = 1;

        for (size_t j = 0; j < n; j++) {
            if (j == i)
                continue;

            ff_elem neg_aj = ff_neg(a[j], p);   /* -a_j */

            /* denom *= (a_i - a_j) */
            ff_elem d = ff_add(a[i], neg_aj, p);
            if(d == 0){                       /* a_i = a_j: points not distinct */
                status = -2;
                break;
            }
            denom = ff_mul(denom, d, p);

            /* num *= (x - a_j) */
            num[deg+1] = num[deg];
            for (size_t k=deg; k>=1; k--)
                num[k] = ff_add(num[k - 1],ff_mul(neg_aj,num[k],p),p);
            num[0] = ff_mul(neg_aj, num[0], p);
            deg++;
        }
        if(status!= 0){
            break;
		}
	
        /* res += c_i / denom * num */
        ff_elem s = ff_div(c[i], denom, p);
        for (size_t k = 0; k < n; k++)
            res[k] = ff_add(res[k], ff_mul(s, num[k], p), p);
    }

    if(status == 0){
        memcpy(w, res, n * sizeof *w);
	}
    free(num); 
    free(res);
    return status;
}
