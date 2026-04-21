#include <stdio.h>
#include "csapp.h"

int open_clientfd(char *hostname, char *port)
{
  int clientfd;
  struct addrinfo hints, *p, *listp;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_ADDRCONFIG;
  hints.ai_flags = AI_NUMERICSERV;
  Getaddrinfo(*hostname, *port, &hints, &listp);
  
  for(p=listp;p;p=p->ai_next) {
    if (clientfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) == -1) {
      continue;
    }
    if (connect(clientfd,p->ai_addr,p->ai_addrlen) != -1) {
      break;
    }

    Freeaddrinfo(p);
  }

  Freeaddrinfo(listp);
  if (!p) {
    return -1;
  } else {
    return clientfd;
  }
};