#include "csapp.h"

int open_listenfd(char *port) {
  int listenfd, optspt=1;
  struct addrinfo hints, *p, *listp;
  
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_PASSIVE | AI_ADDRCONFIG;

  for (p=listp;p;p->ai_next) {
    if (listenfd = socket(p->ai_family,p->ai_socktype, p->ai_protocol) < -1) {
      continue;
    }
    Setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, (const void *)&optspt, sizeof(int));
    if (bind(listenfd,p->ai_addr,p->ai_addrlen) == 0) {
      break;
    }
    Close(listenfd);
  }
  Freeaddrinfo(listp);
  if (!p) {
    return -1;
  }

  if (listen(listenfd, LISTENQ) < 0) {
    Close(listenfd);
    return -1;
  }
  return listenfd;
}