#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT <PORT_HERE>

//For Console Color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(){

  int serversocket;
  struct sockaddr_in serveraddress;

  int newsocket;
  struct sockaddr_in newaddr;

  socklen_t addr_size;
  char message[1024];
  serversocket = socket(AF_INET, SOCK_STREAM, 0);
  if(serversocket < 0){
    perror(ANSI_COLOR_RED "[-]Socket Error, Aborted!" ANSI_COLOR_RESET);
  }else{
    printf(ANSI_COLOR_GREEN "[+]Socket Succesfuly Created!" ANSI_COLOR_RESET "\n");
  }
  memset(&serveraddress,'\0', sizeof(serveraddress));

  serveraddress.sin_family = AF_INET;
  serveraddress.sin_port = htons(PORT);
  serveraddress.sin_addr.s_addr = inet_addr("IP_HERE");

  int serverbind = bind(serversocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress));

  if(serverbind < 0){
    perror(ANSI_COLOR_RED "[-]Bind Error, Aborted!" ANSI_COLOR_RESET);
  }else{
    printf(ANSI_COLOR_GREEN "[+]Server Bind Succesfuly!" ANSI_COLOR_RESET "\n");
  }

  int listenn = listen(serversocket, 200);

  if(listen < 0){
    perror(ANSI_COLOR_RED "[-]Listen Error, Aborted!" ANSI_COLOR_RESET);
  }else{
    printf( ANSI_COLOR_YELLOW "[+]Listening..." ANSI_COLOR_RESET "\n");
  }

  addr_size = sizeof(newaddr);

  newsocket = accept(serversocket, (struct sockaddr *) &newaddr, &addr_size);

  if(newsocket < 0){
    perror(ANSI_COLOR_RED "[-]Accept Error, Aborted!" ANSI_COLOR_RESET);
  }else{
    printf(ANSI_COLOR_GREEN "[+]Client Connected!" ANSI_COLOR_RESET "\n");
  }

  printf("Write Your Message: ");
  fgets(message, sizeof(message), stdin);

  send(newsocket, message, strlen(message), 0);

  close(serversocket);
  printf(ANSI_COLOR_GREEN "[+]Connection Succesfuly Closed!" ANSI_COLOR_RESET "\n");
  return 0;
}
