#include <stdlib.h>
#include "finite_field_arithmetic.h"
/*
 * encode.c -- Task 1.1: Reed-Solomon encoding via matrix-vector product.
 *
 * Computes c(w) = F * w with F = (a_j^i), 0 <= j < N, 0 <= i < n.
 *   c : output, length N
 *   w : message, length n
 *   a : interpolation points, length N (pairwise distinct, n < N)
 *   p : the prime
 * Returns 0 on success, -1 on invalid input or allocation failure.
 */
int encode(ff_elem *c, const ff_elem *w, size_t n, const ff_elem *a, size_t N, uint32_t p){
	/* we verify the entry parameters. */
	if (!c || !w || !a || n==0 || n>= N){
		return -1;
	}
	
	/* Step 1: we build F (N * n), F[j*n + i] = a_j^i. */
	ff_elem *F = malloc(N*n * sizeof(ff_elem));
	if(!F)
		return -1;
	for(size_t j = 0; j < N; j++){
		F[j*n] = 1;
		for(size_t i  = 1; i < n; i++){
			F[j*n+i] = ff_mul(F[j*n + i - 1], a[j],p);
		}
	}
 	/* Step 2: c = F*w */
 	for(size_t j = 0; j < N; j++){
 		ff_elem s = 0;
 		for(size_t i  = 0; i < n; i++){
			s = ff_add(s,ff_mul(F[j*n+i],w[i],p),p);
		c[j] = s;
		}
	}
	free(F);
	return 0;
}
