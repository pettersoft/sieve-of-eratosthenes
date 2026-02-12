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
const unsigned long int BYTES_REQUIRED = ((TOTAL_RUNS / CHAR_BIT) / 2) + 1;


int main() {
	unsigned char *arr = malloc(BYTES_REQUIRED);
	if (arr == NULL)
		return 1;

	memset(arr, 0XFF, BYTES_REQUIRED);

	for (unsigned int i = 0; (i*2 + 3) * (i * 2 + 3) <= TOTAL_RUNS ; i++) {
		const unsigned int pos = i;
		const unsigned int n = 2*i+3;
		unsigned int arridx = pos / CHAR_BIT;
		unsigned int bitpos = pos % CHAR_BIT;
		
		unsigned char c1 = (arr[arridx] >> bitpos) & 1;
		if (c1 == 1) {
			const unsigned int start = n*n;
			unsigned int precalc = (start-3) / 2;
			for (unsigned int j = start; j < TOTAL_RUNS;) {
				const unsigned int calc = precalc; 
				unsigned int arridx2 = (calc) / CHAR_BIT;
				unsigned int bitpos2 = (calc) % CHAR_BIT;


				arr[arridx2] &= ~(1u << bitpos2);

				j += 2*n;
				precalc += n;
			}
		}

		
	}
	// Kommentera in deh är koden för att skriva ut primtalen
	/*
	for (unsigned int i = 0; i < TOTAL_RUNS/2; i++) {	
		unsigned int arridx = (i) / CHAR_BIT;
		unsigned int bitpos = (i) % CHAR_BIT;
		unsigned char c1 = (arr[arridx] >> bitpos) & 1;
		unsigned int n = i*2 + 3;
		printf("För %d är primtal = %d\n", n, c1);
	}*/

	free(arr);

	return 0;
}


