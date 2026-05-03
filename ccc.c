#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <string.h>

int main() {
    char *asd;
    asd = "asd\\asdas\\dasd";
    while (strchr(asd, '\\')!='\0') {
        printf("%d\n", asd);
        asd++;
    }
}