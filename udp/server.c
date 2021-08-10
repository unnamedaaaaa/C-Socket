#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>


//For Console Color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s {PORT}\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//Init Port
	const int port = atoi(argv[1]);

	int serverSocket;
	struct sockaddr_in serverAddress, clientAddress;
	socklen_t addr_size;


	//Buffer
	char Buffer[1024];

	serverSocket = socket(AF_INET,SOCK_DGRAM, 0);
 
	memset(&serverAddress, '\0', sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));


	addr_size = sizeof(clientAddress);

	while(1){
		memset(Buffer, '\0', sizeof(Buffer));

		recvfrom(serverSocket, Buffer, sizeof(Buffer), 0, (struct sockaddr *) &clientAddress, &addr_size);
		printf(ANSI_COLOR_GREEN "Client ~> %s" ANSI_COLOR_RESET, Buffer);


		memset(Buffer, '\0', sizeof(Buffer));

		printf("Your Message: ");
		fgets(Buffer, sizeof(Buffer), stdin);
		sendto(serverSocket, Buffer, sizeof(Buffer), 0, (struct sockaddr *) &clientAddress, addr_size);
		printf(ANSI_COLOR_CYAN "You ~> %s" ANSI_COLOR_RESET, Buffer);
	
	}

	
	close(serverSocket);
	exit(EXIT_SUCCESS);
 	return 0;
}
