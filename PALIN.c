#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>


void
increment(char *num, char *carry)
{
	if (*num == '9') {
		*num = '0';
		*carry = '1';
	} else {
		++(*num);
		*carry = '0';
	}
}


void
reverse(char *string, int left, int right)
{
	char swap;

	while (left < right) {
		swap = string[left];
		string[left++] = string[right];
		string[right--] = swap;
	}
}


int
num_cmp(const char *num1, const char *num2, int num_len)
{
	int i;

	for (i = 0; i < num_len; ++i) {
		if (num1[i] > num2[i]) {
			return 1;
		} else if (num1[i] < num2[i]) {
			return -1;
		}
	}
	return 0;
}


void
process_cornercase(char *left_num, char mid_num, int left_len)
{
	char carry = '0';
	int i;

	if (mid_num != EOF)
		increment(&mid_num, &carry);
	for (i = left_len - 1; i >= 0; --i) {
		if (mid_num != EOF && carry == '0')
			break;
		increment(left_num + i, &carry);
		if (carry == '0')
			break;
	}
	if (carry == '1')
		putchar(carry);
	printf("%s", left_num);
	if (mid_num != EOF)
		putchar(mid_num);
	if (carry == '0')
		reverse(left_num, 0, left_len - 1);
	if (carry == '1')
		left_num[left_len - 1] = '1';
	printf("%s", left_num);
}


void
print_smallest_palindrome(const char *num)
{
	int num_len = strlen(num);
	int mid_ind = num_len / 2, i;
	char *left_num, *right_num, mid_num = EOF;

	if (num_len == 1) {
		if (num[0] == '9') {
			printf("11\n");
		} else {
			printf("%c\n", num[0] + 1);
		}
		return;
	}
	if (num_len % 2)
		mid_num = num[mid_ind];
	left_num = calloc(mid_ind + 1, sizeof(char));
	right_num = calloc(mid_ind + 1, sizeof(char));
	for (i = 0; i < mid_ind; ++i) {
		left_num[i] = num[i];
		right_num[mid_ind - i - 1] = num[i];
	}
	if (num_cmp(right_num, num + mid_ind + ((mid_num == EOF) ? 0 : 1), mid_ind) > 0) {
		printf("%s", left_num);
		if (mid_num != EOF)
			putchar(mid_num);
		printf("%s", right_num);
	} else {
		process_cornercase(left_num, mid_num, mid_ind);
	}
	putchar('\n');
	free(left_num);
	free(right_num);
}


int
main(void)
{
	int t;
	char K[1000001];

	scanf("%d\n", &t);
	for (; t > 0; --t) {
		memset(K, '\0', 1000001 * sizeof(char));
		scanf("%s\n", K);
		print_smallest_palindrome(K);
	}
	return EXIT_SUCCESS;
}
