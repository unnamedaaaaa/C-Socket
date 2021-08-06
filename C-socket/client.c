#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT <PORT_HERE>

int main(){

  int clientSocket;
  struct sockaddr_in serveraddress;
  char message[1024];

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serveraddress, '\0', sizeof(serveraddress));
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_port = htons(PORT);
  serveraddress.sin_addr.s_addr = inet_addr("IP_HERE");

  connect(clientSocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress));


  recv(clientSocket, message, sizeof(message), 0);
  printf("Server ~> %s \n", message);

  close(clientSocket);
  exit(EXIT_SUCCESS);

  return 0;
}
