#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

// IP socket address structure
struct sockaddr_in
{
  uint16_t sin_family;       // Protocol family (always AF_INET)
  uint16_t sin_port;         // Port number in network byte order
  struct in_addr sin_addr;   // IP adress in network byte order
  unsigned char sin_zero[8]; // Pad to sizeof (struct sockaddr)
};

struct sockaddr
{
  uint16_t sa_family; // Protocol family
  char sa_data[14];   // Address data
};

// 소켓 식별자 생성
// 소켓을 끝점으로 만들고 싶으면 하드코딩된 인자로 socket함수 호출
// clientfd = Socket(AF_INET, SOCK_STREAM,0);
int socket(int domain, int type, int protocol);

// 서버와 연결 수립
// 해당 함수는 소켓 주소 addr의 서버와 인터넷 연결을 시도
// addrlen은 sizeof(sockaddr_in)
int connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);

// 서버가 클라이언트 연결 수립하기 위해서 사용
// bind는 커널에 addr에 있는 서버의 소켓 주소를 소켓 식별자 sockfd와 연결하라고 물어봄
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// 서버가 클라이언트 연결 수립하기 위해서 사용
// 클라이언트는 연결 요청을 개시하는 능동적 개체
// 서버는 클라이언트로부터 연결 요청을 기다리는 수동적 개체
int listen(int sockfd, int backlog);

// 서버가 클라이언트 연결 수립하기 위해서 사용
// 클라이언트로부터 연결 요청을 받는 함수
// listenfd에 도달하기까지 기다리고 그 후 addr내의 클라이언트 소켓 주소를 채우고 Unix I/O 함수들을 사용해서 클라이언트와 통신하기 위해서 사용될 수 있는 연결 식별자를 리턴
int accept(int listenfd, struct sockaddr *addr, int *addrlen);

int getaddrinfo(const char *host, const char *service);

void freeaddrinfo(struct addrinfo *result);

const char *gai_strerror(int errcode);

struct addrinfo
{
  int ai_flags;             // Hints argument flags
  int ai_family;            // First arg to socket function
  int ai_socktype;          // Second arg to socket function
  int ai_protocol;          // Third arg to socket function
  char *ai_canonname;       // Canonical hostname
  size_t ai_addrlen;        // Size of ai_addr struct
  struct sockaddr *ai_addr; // Ptr to socket address structure
  struct addrinfo *ai_next; // Ptr to next item in linked list
};

int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *service, size_t servlen, int flags);
