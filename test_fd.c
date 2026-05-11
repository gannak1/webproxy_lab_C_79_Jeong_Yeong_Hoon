#include "list.c"
#include "list.h"
#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITMASK(SHIFT, CNT) (((1ul << (CNT)) - 1) << (SHIFT))

/* Page offset (bits 0:12). */
#define PGSHIFT 0                       /* Index of first offset bit. */
#define PGBITS 12                       /* Number of offset bits. */
#define PGSIZE (1 << PGBITS)            /* Bytes in a page. */
#define PGMASK BITMASK(PGSHIFT, PGBITS) /* Page offset bits (0:12). */

int main() {
    // for (int s = 0, d = 0; s < 10; s++, d++) {
    printf("%d\n", (PGMASK));
    // }
}

