#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t strlcpy (char *dst, const char *src, size_t size);

int main() {
	unsigned long addr_f = 0x47480000;
	unsigned long addr_s = 0x4747fffc;
 

	printf("%p",addr_f - addr_s);
}

int main_s() {
	int *asd;
	int value;
	*asd = value;
	printf("%d",asd);
}

int main_t() {
	char data[] = "args-single onearg";
	char *delimiter = " ";
	char *save_ptr;
	char *token = strtok_r(data,delimiter, &save_ptr);
	printf("%s\n",token);
	while (((token = strtok_r(NULL, delimiter, &save_ptr)) != NULL)) {
		printf("%s\n",token);
	}
	if (token == NULL) {
		printf("NULL");
	}
}


char *
strtok_r (char *s, const char *delimiters, char **save_ptr) {
	char *token;


	/* If S is nonnull, start from it.
	   If S is null, start from saved position. */
	if (s == NULL)
		s = *save_ptr;

	/* Skip any DELIMITERS at our current position. */
	while (strchr (delimiters, *s) != NULL) {
		/* strchr() will always return nonnull if we're searching
		   for a null byte, because every string contains a null
		   byte (at the end). */
		if (*s == '\0') {
			*save_ptr = s;
			return NULL;
		}

		s++;
	}

	/* Skip any non-DELIMITERS up to the end of the string. */
	token = s;
	while (strchr (delimiters, *s) == NULL)
		s++;
	if (*s != '\0') {
		*s = '\0';
		*save_ptr = s + 1;
	} else
		*save_ptr = s;
	return token;
}