#include "bitmap.h"
// #include "hash.h"
// #include "list.c"
// #include "list.h"
// #include "testa.c"
// #include "testb.c"
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

struct bitmap *swap_table;
int main() {
    int total_swap_count = 100;
    swap_table = bitmap_create(total_swap_count * 8);
    if (swap_table == NULL) {
        return -1;
    }

    // swap_
    int swap_location = 15;

    for (int i = 0; i < 8; i++) {
        bitmap_set(swap_table, swap_location * 8 + i, 1);
    }

    printf("data%d : %d\n", -1, bitmap_test(swap_table, swap_location * 8 - 1));
    for (int i = 0; i < 8; i++) {
        int data = bitmap_test(swap_table, swap_location * 8 + i);
        printf("data%d : %d\n", i, data);
    }
    printf("data%d : %d\n", 9, bitmap_test(swap_table, (swap_location + 1) * 8 + 1));
    bitmap_destroy(swap_table);
} 