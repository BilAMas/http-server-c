#include <stdbool.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <err.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

// sendRespone(int code, headers, filebytes) {
//   if code == 200 etc etc etc
// }

int code;

struct ParsedResult {
  char* storedRequest;
  char* address;
};


char* genHeader() {
  char date[100] = "";
  time_t myTime = time(NULL);
  char* HTTPTime = asctime(gmtime(&myTime));
  // strcat(HTTPTime, "\r\n");

  return HTTPTime;
}

char* response(char* headerToSend, int code, int socket, int acceptus) {
  char statusLine[100] = "HTTP/1.0";
  if (code == 200) {
    strcat(statusLine, " 200 OK \r\n");
  } else if (code == 400) {
    strcat(statusLine, " 400 Bad Request\r\n");
  } else if (code == 404) {
    strcat(statusLine, " 404 Not Found\r\n");
  } else if (code == 500) {
    strcat(statusLine, " 500 Internal Server Error\r\n");
  } else if (code == 501) {
    strcat(statusLine, " 501 Not Implemented\r\n");
  } else {
    strcat(statusLine, " 500 Internal Server Error\r\n");
  }
  char dateLine[100] = "Date: ";
  strcat(dateLine, genHeader());
  // char* dateLine = genHeader();
  static char resp[100] = "";
  // char* HTTPVer = "HTTP/1.0";
  // char* HTTPCode = " 200";
  // strcat(resp, HTTPVer);
  // printf("What we have after version, %s\n", resp);
  // strcat(resp, HTTPCode);
  // printf("What we have after code, %s\n", resp);
  strcat(resp, statusLine);
  strcat(resp, dateLine);
  strcat(resp, headerToSend);


  strcat(resp, "\r\n");
  int msgLen = strlen(resp);
  printf("%s\n", resp);
  

  int bytesSent;
  if ((bytesSent = send(acceptus, resp, msgLen, 0)) == -1) {
    perror("send");
  }

  // int bytesSent = send(sockfd, msg, msgLen, 0);
  printf("%d", bytesSent);
  printf("%s", strerror(errno));

  close(socket);

  return resp;
}


// char* respHeader(struct ParsedResult ResultFromMain) {
// char* respHeader() {
  // static char respHeader[256] = "";
  // char serverInfo[100] = "Server: BHTTP/0.1\r\n";
  // char serverInfo[100] = "Server: BHTTP/0.1\r\n";
  // char storedRequestFromMain[100];
  // strcpy(storedRequestFromMain,ResultFromMain.storedRequest);
  // printf("this is stored req form inside funcobuncow %s", ResultFromMain.storedRequest);
  // printf("this is stored req form inside funcobunco %s", storedRequestFromMain);

  // strcat(respHeader, storedRequestFromMain);
  // strcat(respHeader, "\n");
  // strcat(respHeader, serverInfo);

  // return respHeader;
//   return "Server: BHTTP/0.1\r\n";
// }

void entHeader() {
  }

void entBody() {
 }

struct ParsedResult parseRequest(char* recvString) {
  char stringToParse[300];
  // char storedRequest[100];
  struct ParsedResult parsedResult;
  parsedResult.address = malloc(300);
  // printf("this is the og string %s", recvString);

  // strcpy(storedRequest,recvString);
  strcpy(stringToParse,recvString);
  // printf("this print comes from within the func %s\n", stringToParse);
  // printf("print comes from within the func %s\n", storedRequest);

  // char address[100];
  char *pointerToParse[300];
  *pointerToParse = stringToParse;
  
  char* firstLine = strtok(*pointerToParse, "\r\n");
  // printf("first line %s", firstLine);
  char *requestType = strtok(firstLine, " ");
  char *addy = strtok(NULL, " ");
  // char *address = strchr(firstLine,'/');
  strcpy(parsedResult.address, addy);
  // strcpy(address,addParsed);
  // printf("addy form the funco (%s)", addy);
  // if (strcmp(requestType, "GET") != 0) {
  //   code = 501;
  //   // have response handle the whole bytesent stuff 
  //   // Call SendResp to terminate right here.
  //   // printf("Invalid Request Type");
  // }

  // char *address = strchr(firstLine,'/');
  // if (address == NULL) {
  //   strcpy(address, "/index.html");
  // }
  // printf("wwawwa%s \n", address);
  

  // struct ParsedResult parsedResult = {
  //   storedRequest,
  //   address
  // };
  
  // printf("i wanna jump outta here (%s)", parsedResult.address);

  return parsedResult;
}


int main() { 
  
  // char method[50] = "GET";
  // char destination[100] = "localhost";
  char port[50] = "8000";
  // int intPort = 8000;
  // char httpVer[50] = "HTTP/1.0";

  struct addrinfo hints;
  struct addrinfo *res;
  struct sockaddr addr;
  socklen_t addrSize;

  memset(&hints, 0, sizeof hints);
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_family = AF_INET;

  int result;
  if ((result = getaddrinfo("127.0.0.1", port, &hints, &res)) == -1) {
    perror("Address Info Error");
  }
  // printf("getaddrinfo %d\n", result);


  // printf("Socket %d\n", res->ai_family);
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd == -1) {
    printf("Socket Error");
  }

  int bindp = bind(sockfd, res->ai_addr, res->ai_addrlen);
  if (bindp == -1) {
    printf("Bind Error");
    // printf("ERRRROOORRR!!! %s \n", strerror(errno));
  }
  printf("Bind Complete %d\n", bindp);

  int list = listen(sockfd, 5);
  if (list == -1) {
    printf("Listen Error");
  }
  printf("Listening... %d\n", list);

  int acc = accept(sockfd, &addr, &addrSize);
  if (acc == -1) {
    printf("Accept Error");
    printf("ERRRROOORRR!!! %s \n", strerror(errno));
  }
  printf("Accepted Connection %d\n", acc);
  
  // char recvString[300] = "GET /index.html HTTP/1.1 \r\n";
  char recvString[300];
  // char* pointerRecvString[100];
  // *pointerRecvString = recvString;
  int rec;
  // while(1) {
    rec = recv(acc, recvString, 300, 0);
    // printf("ERRRROOORRR!!! %s \n", strerror(errno));
    // printf("%s\n", recvString);
    // printf("%i\n", rec);
    // if (strchr(recvString, '\n') != NULL) {
    //     break;
    // }
    if (rec == -1) {
      printf("Reciving Request Error");
      code = 500;
      // Call SendResp to terminate right here.
  }


  // TODO FRIDAY- Have the struct func just return addresss only. Wait u cant return strings anyways uhoh
  struct ParsedResult parsedResultus = parseRequest(recvString);
  // if (code == 501) {
  //   char* testToSend = parsedResult.storedRequest;
  //   char* respHeaderFinal = respHeader(parsedResult);
  //   char* testRespFail = response(respHeaderFinal, code);
  //
  //
  //   strcat(testRespFail, "\r\n");
  //   // strcat(testRespFail, bytesToSend);
  //   int msgLen = strlen(testRespFail);
  //   printf("%s\n", testRespFail);
  //   
  //
  //   int bytesSent;
  //   if ((bytesSent = send(acc, testRespFail, msgLen, 0)) == -1) {
  //     perror("send");
  //   }
  //
  //   // int bytesSent = send(sockfd, msg, msgLen, 0);
  //   printf("%d", bytesSent);
  //   printf("%s", strerror(errno));
  //
  //   close(sockfd);
  // }
  // printf("value of code is %i", code);
  if (code == 501) {
    // struct ParsedResult parsedResult = parseRequest(recvString);
    // char* testToSend = parsedResult.storedRequest;
    // char* respHeaderFinal = respHeader(parsedResult);
    char* respHeaderFinal = "";
    response(respHeaderFinal, code, sockfd, acc);
  } else {


  // char* testToSend = parsedResultus.storedRequest;
  // printf("test resultus (%s)", parsedResultus.storedRequest);
  // char* respHeaderFinal = respHeader();
  char entHeader[100] = "Content-Type: text/html\n";
  char respHeaderFinal[100] = "Server: BHTTP/0.1\r\n";

  FILE *fileToSend;
  char fileLoc[100] = ".";
  // printf("parsed resultus (%s)", parsedResultus.address);
  strcat(fileLoc, parsedResultus.address);
  fileToSend = fopen(fileLoc, "rb");
  if (fileToSend != NULL) {
      code = 200;
      char bytesToSend[256];
      fread(bytesToSend, sizeof(*fileToSend), 1, fileToSend);
      strcat(respHeaderFinal, entHeader);
      strcat(respHeaderFinal, "\n");
      strcat(respHeaderFinal, bytesToSend);
      response(respHeaderFinal, code, sockfd, acc);
  }
  else {
    code = 404;
    char* respHeaderFinal = "";
    response(respHeaderFinal, code, sockfd, acc);
  } 

    // Here we do recv call to get the request in the format from spec
    // Then we parse this
    // Then we perform file ops (fopen) and (fread)
    // Then we send HTTP headers and file bytes as response
    // Close connection
     

    
  }
  free(parsedResultus.address);
  close(sockfd);
}


