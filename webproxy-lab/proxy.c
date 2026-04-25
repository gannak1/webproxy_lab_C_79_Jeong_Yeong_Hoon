#include "csapp.h"
#include <stdio.h>

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr =
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 "
    "Firefox/10.0.3\r\n";

void doit(int fd);
void read_requesthdrs(rio_t *rp, char *host_header, char *other_header);
void parse_uri(char *uri, char *hostname, char *port, char *path);
void reassemble(char *req, char *path, char *hostname, char *other_header);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char hostname[MAXLINE], port[MAXLINE];

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        doit(connfd);
        Close(connfd);
    }
    printf("%s", user_agent_hdr);
    return 0;
}

void doit(int fd) {
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char host_header[MAXLINE], other_header[MAXLINE];
    char hostname[MAXLINE], port[MAXLINE], path[MAXLINE];
    char request_buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    printf("Request headers:\n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    if ((strcasecmp(method, "GET") != 0)) {
        clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        return;
    }
    read_requesthdrs(&rio, host_header, other_header);

    /*Parse URI from GET request*/
    parse_uri(uri, hostname, port, path);
    int servedf = Open_clientfd(hostname, port);
    reassemble(request_buf, path, hostname, other_header);
    Rio_writen(servedf, request_buf, strlen(request_buf));
    forward_response(servedf, fd);
}

void read_requesthdrs(rio_t *rp, char *host_header, char *other_header) {
    char buf[MAXLINE];
    host_header[0] = '\0';
    other_header[0] = '\0';

    while (Rio_readlineb(rp, buf, MAXLINE) > 0 && strcmp(buf, "\r\n")) {
        if (!strncasecmp(buf, "HOST:", 5)) {
            strcpy(host_header, buf);
        } else if (!strncasecmp(buf, "User-Agent:", 11) || !strncasecmp(buf, "Connection:", 11) ||
                   !strncasecmp(buf, "Proxy-connection:", 17)) {
            continue;
        } else {
            strcat(other_header, buf);
        }
    }
}

void parse_uri(char *uri, char *hostname, char *port, char *path) {
    char *hostbegin, *hostend, *portbegin, *pathbegin;
    char buf[MAXLINE];

    strcpy(buf, uri);

    hostbegin = strstr(buf, "//");
    hostbegin = (hostbegin != NULL) ? hostbegin + 2 : buf;

    pathbegin = strchr(hostbegin, '/');
    if (pathbegin != NULL) {
        strcpy(path, pathbegin);
        *pathbegin = '\0';
    } else {
        strcpy(path, "/");
    }

    portbegin = strchr(hostbegin, ':');
    if (portbegin != NULL) {
        *portbegin = '\0';
        strcpy(hostname, hostbegin);
        strcpy(port, portbegin + 1);
    } else {
        strcpy(hostname, hostbegin);
        strcpy(port, "80");
    }
}
void reassemble(char *req, char *path, char *hostname, char *other_header) {
    sprintf(req,
            "GET %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "%s"
            "Connection: close\r\n"
            "Proxy-Connection: close\r\n"
            "%s"
            "\r\n",
            path, hostname, user_agent_hdr, other_header);
}
void forward_response(int servedf, int fd) {
    rio_t serve_rio;
    Rio_readinitb(&serve_rio, servedf);

    char response_buf[MAXBUF];
    ssize_t n;
    while (n = Rio_readnb(&serve_rio, response_buf, MAXBUF) > 0) {
        Rio_writen(fd, response_buf, sizeof(response_buf));
    }
}
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body*/
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body,
            "%s <body bgcolor="
            "ffffff"
            ">\r\n",
            body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
