#include <stdbool.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <err.h>

int main() { 
  
  char method[50] = "GET";
  char destination[100] = "localhost";
  char port[50] = "8000";
  int intPort = 8000;
  char httpVer[50] = "HTTP/1.0";

  struct addrinfo hints;
  struct addrinfo *res;
  struct sockaddr addr;
  socklen_t addrSize;

  memset(&hints, 0, sizeof hints);
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_family = AF_INET;


  int result = getaddrinfo("127.0.0.1", port, &hints, &res);
  printf("getaddrinfo %d\n", result);

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // if (sockfd == -1) {
  //   printf("Socket Error");
  // }

  int bindp = bind(sockfd, res->ai_addr, res->ai_addrlen);
  printf("bind %d\n", bindp);

  int list = listen(sockfd, 5);
  printf("listen %d\n", list);

  int acc = accept(sockfd, &addr, &addrSize);
  printf("accept %d\n", acc);

  char* msg = "YOOO IT WRKS";
  int msgLen = strlen(msg);
  printf("%s", msg);

  int bytesSent;
  if ((bytesSent = send(acc, msg, msgLen, 0)) == -1) {
    perror("send");
  }

  // int bytesSent = send(sockfd, msg, msgLen, 0);
  printf("%d", bytesSent);
  printf("%s", strerror(errno));
}


