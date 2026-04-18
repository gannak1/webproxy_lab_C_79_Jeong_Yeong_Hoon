#include <stdio.h>
#include "../csapp.h"

struct addrinfo {
  int ai_falgs;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  char ai_canonname;
  size_t ai_addrlen;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
};

void main(int argc,char **argv) {
}