#include <stdio.h>
#include <string.h>
#include "str.h"

int main()
{
	char str[] = "Apple and orange";
	char key[] = "1234567890";
	char sym = 'p';
	printf("%d ", my_strcspn(str, key));
	printf("%p ", my_strchr(str, sym));
	char *ring = strchr(str, 'p');
	printf("%p ", ring);
	return 0;
}