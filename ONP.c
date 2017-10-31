#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_EXPR_LEN 401


void
get_rpn(char *expression, char *rpn, char *stack)
{
	int i, j = 0, k = 0;

	for (i = 0; expression[i] != '\0'; ++i) {
		switch (expression[i]) {
		case '(':
			++k;
			break;
		case ')':
			rpn[j++] = stack[k--];
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			stack[k] = expression[i];
			break;
		default:
			rpn[j++] = expression[i];
			break;
		}
	}
}


int
main(void)
{
	int t;
	char *expression = calloc(MAX_EXPR_LEN, sizeof(char)),
		 *rpn = calloc(MAX_EXPR_LEN, sizeof(char)),
		 *stack = calloc(MAX_EXPR_LEN, sizeof(char));

	scanf("%d\n", &t);
	for (; t > 0; --t) {
		scanf("%s\n", expression);
		get_rpn(expression, rpn, stack);
		printf("%s\n", rpn);
		memset(expression, '\0', MAX_EXPR_LEN * sizeof(char));
		memset(rpn, '\0', MAX_EXPR_LEN * sizeof(char));
		memset(stack, '\0', MAX_EXPR_LEN * sizeof(char));
	}
	free(expression);
	free(rpn);
	free(stack);
	return 0;
}
