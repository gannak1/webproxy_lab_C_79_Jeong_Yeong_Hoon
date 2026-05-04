#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <string.h>

int main() {
    // char *asd;
    // asd = "hello world";
    // while (strchr(' ',asd)!=NULL) {
    //     printf("%s\n", asd);
    //     asd++;
    // }
    // printf("%s\n", asd);
    long x = 0x47480000-0x4747ffc0;
    printf("%p",x);
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
		*s = 'P';
		*save_ptr = s + 1;
	} else
		*save_ptr = s;
	return token;
}