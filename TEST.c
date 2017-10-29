#include <stdio.h>

int
main(void)
{
	int i;

	while (scanf("%d\n", &i) != EOF) {
		if (i == 42)
			return 0;
		printf("%d\n", i);
	}

	return 0;
}
