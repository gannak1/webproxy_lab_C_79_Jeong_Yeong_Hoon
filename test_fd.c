#include "list.c"
#include "list.h"
#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNV_64_PRIME 0x00000100000001B3UL
#define FNV_64_BASIS 0xcbf29ce484222325UL

uint64_t hash_bytes(const void *buf_);

int main() {
    // for (int s = 0, d = 0; s < 10; s++, d++) {
    void *addr;
    addr = (void *)15;
    // printf("addr : %p\n", addr);
    // size_t data = (size_t)addr;
    // unsigned long addr_array[16];
    // int index = 0;
    // for (int idx = 15; idx >= 0; idx--) {
    //     addr_array[idx] = (long)data & 0xf;
    //     data = data >> 4;
    // }
    // printf("addr : ");
    // for (int idx = 0; idx < 16; idx++) {
    //     printf("%d ", addr_array[idx]);
    // }
    // printf("\n");
    for (int idx = 0; idx < 10; idx++) {
        printf("\n\n%d : ", idx);
        printf("%p\n", addr);
        printf("out : %p\n\n", hash_bytes(addr + idx * 10));
    }
}
// void *va;
/* Returns a hash of the SIZE bytes in BUF. */
uint64_t hash_bytes(const void *buf_) {
    int size = 1;
    /* Fowler-Noll-Vo 32-bit hash, for bytes. */
    printf("buf addr : %p\n", (size_t)buf_);
    size_t data = (size_t)buf_;
    printf("buf addr : %p\n", data);
    uint64_t hash;
    // ASSERT(buf != NULL);

    hash = FNV_64_BASIS;
    while (size-- > 0) {
        hash = (hash * FNV_64_PRIME) ^ (data);
    }

    return hash;
}