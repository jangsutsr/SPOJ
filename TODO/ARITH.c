#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define UPDATE_CARRY(digit, carry) if (digit >= 10) {digit -= 10; carry = '1';} else {carry = '0';}


enum operator {
	ADD='+',
	SUB='-',
	MUL='*'
};


void
allocate_nums(char *input_buffer, char *left, char *right, enum operator *operator)
{
	int i, j;

	for (i = 0, j = 0; input_buffer[i] != '\0'; ++i) {
		if (input_buffer[i] >= '0' && input_buffer[i] <= '9') {
			if (*operator) {
				right[j++] = input_buffer[i];
			} else {
				left[j++] = input_buffer[i];
			}
		} else {
			*operator = input_buffer[i];
			j = 0;
		}
	}
}


void
reverse_num(char *num, int left, int right)
{
	char swap;

	while (left < right) {
		swap = num[left];
		num[left++] = num[right];
		num[right--] = swap;
	}
}


int
get_max_int(int *array, int len)
{
	int ret = array[0], i;

	for (i = 1; i < len; ++i) {
		if (array[i] > ret)
			ret = array[i];
	}
	return ret;
}


void
print_dash_line(int max_len, int len_above, int len_below)
{
	int longest_dashes = len_above, i;

	if (len_below > longest_dashes)
		longest_dashes = len_below;
	for (i = 0; i + longest_dashes < max_len; ++i)
		putchar(' ');
	for (; i < max_len; ++i)
		putchar('-');
	putchar('\n');
}


void
print_add(char *left, char *right)
{
#define LEFT 0
#define RIGHT 1
#define RESULT 2
	char result[550];
	int lens[] = {strlen(left), strlen(right), 0}, max_len;
	int i, j;
	int digit;
	char carry = '0';

	memset(result, '\0', 550 * sizeof(char));
	for (i = lens[LEFT] - 1, j = lens[RIGHT] - 1; i >= 0 && j >= 0; --i, --j) {
		digit = left[i] - '0' + right[j] - '0' + carry - '0';
		UPDATE_CARRY(digit, carry)
		result[lens[RESULT]++] = digit + '0';
	}
	for (; i >= 0; --i) {
		digit = left[i] - '0' + carry - '0';
		UPDATE_CARRY(digit, carry)
		result[lens[RESULT]++] = digit + '0';
	}
	for (; j >= 0; --j) {
		digit = right[j] - '0' + carry - '0';
		UPDATE_CARRY(digit, carry)
		result[lens[RESULT]++] = digit + '0';
	}
	if (carry == '1')
		result[lens[RESULT]++] = carry;
	reverse_num(result, 0, lens[RESULT] - 1);
	++lens[RIGHT];
	max_len = get_max_int(lens, 3);
	for (i = 0; i + lens[LEFT] < max_len; ++i)
		putchar(' ');
	printf("%s\n", left);
	for (i = 0; i + lens[RIGHT] < max_len; ++i)
		putchar(' ');
	printf("+%s\n", right);
	print_dash_line(max_len, lens[RIGHT], lens[RESULT]);
	for (i = 0; i + lens[RESULT] < max_len; ++i)
		putchar(' ');
	printf("%s\n", result);
#undef LEFT
#undef RIGHT
#undef RESULT
}


void
print_sub(char *left, char *right)
{
	/*TODO*/
	printf("%s\n", left);
	printf("%s\n", right);
}


void
print_mul(char *left, char *right)
{
	/*TODO*/
	printf("%s\n", left);
	printf("%s\n", right);
}


int
main(void)
{
	int T;
	char left[501], right[501], input_buffer[1002];
	enum operator operator;

	scanf("%d\n", &T);
	for (; T > 0; --T) {
		operator = 0;
		memset(left, '\0', 501 * sizeof(char));
		memset(right, '\0', 501 * sizeof(char));
		memset(input_buffer, '\0', 1002 * sizeof(char));
		scanf("%s\n", input_buffer);
		allocate_nums(input_buffer, left, right, &operator);
		switch (operator) {
		case ADD:
			print_add(left, right);
			break;
		case SUB:
			print_sub(left, right);
			break;
		case MUL:
			print_mul(left, right);
			break;
		default:
			break;
		}
		putchar('\n');
	}
	return EXIT_SUCCESS;
}
