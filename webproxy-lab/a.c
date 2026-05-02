#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define list_entry(ELEM, TYPE, MEMBER) \
    ((TYPE *) ((char *) (ELEM) - offsetof(TYPE, MEMBER)))

struct list_elem {
    struct list_elem *prev;
    struct list_elem *next;
};

struct list {
    struct list_elem head;
    struct list_elem tail;
};

struct item {
    int value;
    struct list_elem elem;
};

typedef bool list_less_func(const struct list_elem *a,
                            const struct list_elem *b,
                            void *aux);

static struct list_elem *
list_next(struct list_elem *e) {
    return e->next;
}

static struct list_elem *
list_prev(struct list_elem *e) {
    return e->prev;
}


struct list list;

struct item items[];
static void print_list(struct list *list);
/* [first, last) 구간을 before 앞에 옮김 */
static void
list_splice(struct list_elem *before,
            struct list_elem *first,
            struct list_elem *last) {
    if (first == last)
        return;

    last = list_prev(last);   // last는 exclusive라서 실제 마지막 원소로 바꿈

    /* 기존 위치에서 [first, last] 제거 */
    first->prev->next = last->next;
    last->next->prev = first->prev;

    /* before 앞에 [first, last] 삽입 */
    first->prev = before->prev;
    last->next = before;
    before->prev->next = first;
    before->prev = last;
}

static bool
item_less(const struct list_elem *a,
          const struct list_elem *b,
          void *aux) {
    (void) aux;

    struct item *ia = list_entry(a, struct item, elem);
    struct item *ib = list_entry(b, struct item, elem);

    return ia->value < ib->value;
}

static void
inplace_merge(struct list_elem *a0,
              struct list_elem *a1b0,
              struct list_elem *b1,
              list_less_func *less,
              void *aux, struct list *list) {
    while (a0 != a1b0 && a1b0 != b1) {
        if (!less(a1b0, a0, aux)) {
            a0 = list_next(a0);
        } else {
            a1b0 = list_next(a1b0);

            print_list(list);
            list_splice(a0, list_prev(a1b0), a1b0);
            print_list(list);
        }
    }
}

static void
print_list(struct list *list) {
    for (struct list_elem *e = list->head.next;
         e != &list->tail;
         e = e->next) {
        struct item *it = list_entry(e, struct item, elem);
        printf("%d ", it->value);
    }
    printf("\n");
}

int
main(void) {
    struct list list;

    struct item items[] = {
        {1}, {2}, {3}, {4}, {7}, {8}, {0}, {5}
    };

    int n = sizeof items / sizeof items[0];

    /* 리스트 직접 연결 */
    list.head.prev = NULL;
    list.head.next = &items[0].elem;

    for (int i = 0; i < n; i++) {
        items[i].elem.prev = (i == 0) ? &list.head : &items[i - 1].elem;
        items[i].elem.next = (i == n - 1) ? &list.tail : &items[i + 1].elem;
    }

    list.tail.prev = &items[n - 1].elem;
    list.tail.next = NULL;

    /*
       초기 리스트:

       [1, 2, 3, 4, 7, 8] [0, 5]
        ↑                  ↑      ↑
        a0                 a1b0   b1
    */

    struct list_elem *a0 = &items[0].elem;      // 1
    struct list_elem *a1b0 = &items[6].elem;    // 0
    struct list_elem *b1 = &list.tail;          // 끝 더미

    printf("before: ");
    print_list(&list);

    inplace_merge(a0, a1b0, b1, item_less, NULL,&list);

    printf("after : ");
    print_list(&list);

    return 0;
}