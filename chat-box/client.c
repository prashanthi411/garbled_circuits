#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include<netinet/in.h>

int main(int argc, char** argv)
{
	int alice,bob;

	alice = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_alice;
	server_alice.sin_family=AF_INET;
	server_alice.sin_port=htons(atoi(argv[2]));
	server_alice.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&server_alice.sin_zero, 8);

	if(connect(alice, (struct sockaddr*)&server_alice, sizeof(struct sockaddr_in)) == -1){
		printf("Connection could not be established!");
		exit(-1);
	}

	char *test;
	test=(char *)malloc(8*sizeof(char));

/*******Test***************
 Recieving string from Alice and printing it
****************************/
	recv(alice,test, 8, 0);
	printf("%s",test);
	bzero(test, strlen(test));


	recv(alice,test, 8, 0);
	printf("%s",test);
	bzero(test, strlen(test));

/*************************
		End Of Test
**************************/

	char *buffer;
	buffer=(char*)malloc(350*sizeof(char));
	while(1){
		bzero(buffer, sizeof(buffer));

		printf("Bob: ");
		scanf("%s",buffer);
		send(alice, buffer, strlen(buffer), 0);

		bzero(buffer, sizeof(buffer));

		recv(alice, buffer, 350, 0);
		printf("alice: %s\n",buffer);
		if((strncmp(buffer,"exit",4)) == 0){
			printf("Exiting....\n");
			break;
		}
	}
	close(alice);
}
