#include "csapp.h"

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  char clienthost[MAXLINE], clientport[MAXLINE];

  if(argc != 2) {
    exit(0);
  }
  listenfd = Open_listenfd(argv[1]);

  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *) &clientaddr, clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, clienthost, MAXLINE, clientport, MAXLINE, 0);
    echo(connfd);
    Close(connfd);
  }
  exit(0);
}

void echo(int connfd) {
  size_t n;
  rio_t rio;
  char buf[MAXLINE];
  
  Rio_readinitb(&rio, connfd);
  while (n=Rio_readlineb(&rio, buf, MAXLINE) != 0) {
    printf("server receive %d bytes\n", (int)n);
    Rio_writen(connfd, buf,n);
  }
}