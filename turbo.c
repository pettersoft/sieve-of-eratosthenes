#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*
 * testa med
 * gcc -O3 turbo.c -o turbo -lm
 * och...
 * gcc -O3 -march=native turbo.c -o turbo -lm
 * och...
 * gcc -O3 -march=native -mtune=native -funroll-loops turbo.c -o turbo
 * */


const unsigned long int TOTAL_RUNS = 1000000000;
const int CHAR_SIZE = CHAR_BIT;
unsigned long int BYTES_REQUIRED = 0;

void calculate_bytes_required();

int main() {
	calculate_bytes_required();
	unsigned char *arr = malloc(BYTES_REQUIRED);
	if (arr == NULL)
		return 1;

	// set every bit to 1
	memset(arr, 0XFF, BYTES_REQUIRED);

	for (int i = 0; (i*2 + 3) * (i * 2 + 3) <= TOTAL_RUNS ; i++) {
		// get which byte we should get
		const int pos = i;
		const int n = 2*i+3;
		int arridx = pos / CHAR_SIZE;
		int bitpos = pos % CHAR_SIZE;
		
		unsigned char c1 = (arr[arridx] >> bitpos) & 1;
		if (c1 == 1) {
			// mark multiples of this as false
			const int start = n*n;
			for (int j = start; j < TOTAL_RUNS; j+= 2*n) {
				const int calc = (j-3) / 2;
				int arridx2 = (calc) / CHAR_SIZE;
				int bitpos2 = (calc) % CHAR_SIZE;


				arr[arridx2] &= ~(1u << bitpos2);
			}
		}

		
	}

	/*
	for (int i = 0; i < TOTAL_RUNS/2; i++) {	
		int arridx = (i) / CHAR_SIZE;
		int bitpos = (i) % CHAR_SIZE;
		unsigned char c1 = (arr[arridx] >> bitpos) & 1;
		int n = i*2 + 3;
		printf("För %d är primtal = %d\n", n, c1);
	}*/

	free(arr);

	return 0;
}


void calculate_bytes_required() {
	const double runs = (double)TOTAL_RUNS;
	const double charsize = (double)CHAR_SIZE;

	BYTES_REQUIRED = ceil(runs / charsize) / 2;

	// delat med 2 eftersom vi skippar jämna tal
	
}
