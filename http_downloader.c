#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
  
  int sock;
  struct addrinfo hints, *res;
  int status;
  char ipstr[INET_ADDRSTRLEN];
  void *addr;
  char *msg = "GET /?st=1 HTTP/1.1\r\nHost: www.wikipedia.org\r\n\r\n";
  int len = strlen(msg);
  char output[6000];
  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo("www.wikipedia.org", "80", &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
  }
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  int connStatus = connect(sock, res->ai_addr, res->ai_addrlen);
  printf("%d\n", connStatus);
  send(sock, msg, len, 0);
  recv(sock, output, 255, 0);
  close(sock);
  
  printf("%s\n", output);
  /*struct sockaddr_in *sok = (struct sockaddr_in *)res->ai_addr;
  addr = &(sok->sin_addr);
  inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
  printf("%s\n", ipstr);*/
  freeaddrinfo(res);
  /*char server_response[256];
  recv(sock, &server_response, sizeof(server_response), 0);
  printf("The server response is: %s\n", server_response);
  close(sock);*/


  return 0;
}
