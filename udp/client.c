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
	// Init Port N IP
	const int PORT = atoi(argv[1]);
	const char IP[16] = "127.0.0.1";
	
	//Create Socket
	int clientSocket;
	struct sockaddr_in serverAddress;
	socklen_t addr_size;

	//Create Buffer
	char Buffer[1024];
	memset(Buffer, '\0', sizeof(Buffer));

	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&serverAddress, '\0', sizeof(serverAddress));

	addr_size = sizeof(serverAddress);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(IP);
	serverAddress.sin_port = htons(PORT);


	connect(clientSocket, (struct sockaddr *)&serverAddress, addr_size);
	
	while(1){

		memset(Buffer, '\0', sizeof(Buffer));

		printf("Your Message: ");
		fgets(Buffer, sizeof(Buffer), stdin);
		sendto(clientSocket, Buffer, sizeof(Buffer), 0,(struct sockaddr *) &serverAddress, sizeof(serverAddress));
		printf(ANSI_COLOR_GREEN "You ~> %s" ANSI_COLOR_RESET, Buffer);


		recvfrom(clientSocket, Buffer, sizeof(Buffer), 0, (struct sockaddr *) &serverAddress, &addr_size);
		printf( ANSI_COLOR_CYAN "Server ~> %s" ANSI_COLOR_RESET, Buffer);

	}


	close(clientSocket);
	exit(EXIT_SUCCESS);
	
	return 0;
}