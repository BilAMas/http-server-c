#include <stdbool.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>

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
  printf("getaddrinfo %d \n", result);

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  printf("socket %d \n", sockfd);

  // if (sockfd == -1) {
  //   printf("Socket Error");
  // }
  //

  int conn = connect(sockfd, res->ai_addr, res->ai_addrlen);

  printf("connect %d\n", conn);
  printf("%s", strerror(errno));

  char msg[100];
  // int msgMax = 100;
  int recvd = recv(sockfd, msg, 100, 0);
  printf("%s", strerror(errno));
  printf("%s", msg);
  printf("%d", recvd);
  
}
