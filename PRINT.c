#include <stdio.h>
#include <stdlib.h>


#define CEIL(x, y) ((x % y) ? x / y + 1 : x / y)
#define MAX(x, y) ((x > y) ? x : y)


long
get_factor_limit(long num)
{
	long left = 1, right = num, mid;

	while (left <= right) {
		mid = (left + right) / 2;
		if (mid * mid > num) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return left;
}


long
find_prime_factors(long range, long **ret)
{
	char *table;
	long i, j, prime_count = 0;

	table = calloc(range + 1, sizeof(char));
	for (i = 2; i <= range; ++i) {
		if (table[i])
			continue;
		++prime_count;
		for (j = i * i; j <= range; j += i)
			table[j] = 1;
	}
	*ret = calloc(prime_count, sizeof(long));
	j = 0;
	for (i = 2; i <= range; ++i) {
		if (!table[i])
			(*ret)[j++] = i;
	}
	free(table);
	return prime_count;
}


/**
 * QUESTION: Still don't quite understand why sieve against an interval
 * is somehow more efficient than checking each interval element for
 * primary. Time complexity analysis involves number theory proof, which
 * is beyond current knowledge base.
 */
void
print_primes(long left, long right, long *prime_factors, int prime_count)
{
	int i;
	long mark;
	char *table;

	table = calloc(right - left + 1, sizeof(long));
	for (i = 0; i < prime_count && prime_factors[i] * prime_factors[i] <= right; ++i) {
		for (mark = prime_factors[i] * MAX(2, CEIL(left, prime_factors[i]));
			 mark <= right; mark += prime_factors[i])
			table[mark - left] = 1;
	}
	for (i = 0; i < right - left + 1; ++i) {
		if (!table[i])
			printf("%ld\n", left + (long)i);
	}
	free(table);
}


int
main(void)
{
	int t, i;
	long *m, *n, range = 1L;
	long *prime_factors = NULL;
	int prime_count;

	scanf("%d\n", &t);
	m = calloc(t, sizeof(long));
	n = calloc(t, sizeof(long));
	for (i = 0; i < t; ++i) {
		scanf("%ld %ld\n", m + i, n + i);
		if (range < n[i])
			range = n[i];
	}
	prime_count = find_prime_factors(get_factor_limit(range), &prime_factors);
	for (i = 0; i < t; ++i) {
		print_primes(m[i], n[i], prime_factors, prime_count);
	}
	free(prime_factors);
	free(m);
	free(n);
	return 0;
}
