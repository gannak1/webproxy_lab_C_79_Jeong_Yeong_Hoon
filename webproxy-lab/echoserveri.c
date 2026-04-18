#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  char client_hostname[MAXLINE], client_port[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "error");
    exit(0);
  }

  listenfd = Open_listenfd(argv[1]);

  while(1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port,MAXLINE,0);
    echo(connfd);
    Close(connfd);
  }

  exit(0);
}

void echo(int connfd) {
  rio_t rio;
  char buf[MAXLINE];
  size_t n;
  rio_readinitb(&rio, connfd);
  while ((n=Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("server receive %d bytes\n", (int) n);
    Rio_writen(connfd, buf, strlen(buf));
  }
}