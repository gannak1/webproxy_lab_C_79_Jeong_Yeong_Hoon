#include "testa.c"
#include "testb.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.c"
#include "list.h"

/* An open file. */
struct file {
	char *data;
};

struct thread {
	/* Owned by thread.c. */
	struct list fd_list;
	char name[16];             /* Name (for debugging purposes). */
	int priority;              /* Priority. */
	int64_t wakeup_tick; /* alarm clock*/
	/* Shared between thread.c and synch.c. */
	struct list_elem elem; /* List element. */
	int next_fd;
};
struct thread 
thread_current () {
	struct thread t;
	char *ta = "test";

	t.priority = 1;
	list_init (&(t.fd_list));

	t.next_fd = 2;

	/* t = new thread, current thread 와 비교 */
	return t;
}


struct fd_entry {
	struct file *data;
	int fd_n;
	struct list_elem elem;
};

struct fd_entry *
fd_entry_init (struct fd_entry *fd, struct file *data, struct thread *t) {
	fd->data = data;
	fd->fd_n = t->next_fd;
	(t->next_fd)++;
	return fd;
}

struct file *
get_file_from_fd_entry (struct list_elem *elem) {
	if (elem == NULL) {
		return NULL;
	}
	struct fd_entry *fd_elem = list_entry (elem, struct fd_entry, elem);
	return fd_elem->data;
}

int
fd_add_file (struct file *file,struct thread *t) {
	// 열린 struct file을 현재 프로세스의 fd table에 등록하고 새 fd 번호를 반환한다.
	// open() 성공 시 호출되며, 실패하면 -1을 반환하도록 설계한다.
	// struct thread *t = thread_current ();
	int return_fd_number=99; // 새 fd번호
	struct fd_entry fd;
	fd_entry_init (&fd, file, t);
	list_push_back (&t->fd_list, &(fd.elem)); // 등록
	printf("%p\n", t->fd_list);
	return fd.fd_n;
}
int
fd_add_file2() {
	int a;
	a = 11;
	return a;
}


int main() {
	struct file f;
	struct thread t;
	// struct thread z;
	// *t = z;
	t = thread_current();

	int s;
	printf("%p\n", t.fd_list);
	s = fd_add_file(&f,&t);
	printf("test_start\n");
	printf("%d\n",s);
	printf("%p\n", t.fd_list);
}

