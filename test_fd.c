#include "hash.h"
#include "list.c"
#include "list.h"
#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct hash spt =
        hash_init(struct hash * h, hash_hash_func * hash, hash_less_func * less, void *aux);
}

bool page_less(const struct hash_elem *a_, const struct hash_elem *b_, void *aux UNUSED) {
    const struct page *a = hash_entry(a_, struct page, hash_elem);
    const struct page *b = hash_entry(b_, struct page, hash_elem);

    return a->addr < b->addr;
    ;
}