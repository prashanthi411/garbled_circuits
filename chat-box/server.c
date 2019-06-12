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
	int bob,alice,len;

	alice = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_alice;
	struct sockaddr_in server_bob;
	server_alice.sin_family=AF_INET;
	server_alice.sin_port=htons(atoi(argv[1]));
	server_alice.sin_addr.s_addr=INADDR_ANY;
	bzero(&server_alice.sin_zero, 8);

	FILE *ftest=fopen("test.txt","r");
	char *test;
	test=(char *)malloc(8*sizeof(char));
	fscanf(ftest,"%s",test);
	printf("%s",test);
	fscanf(ftest,"%s",test);
	printf("%s",test);
	if((bind(alice, (struct sockaddr*)&server_alice, sizeof(struct sockaddr_in))) == -1){
		printf("Server binding unsuccessful!\n");
		exit(-1);
	}

	if((listen(alice, 2)) == -1){
		printf("Listen unsuccessful!\n");
		exit(-1);
	}
	else
		printf("Alice is listening....\n");

	len=sizeof(struct sockaddr_in);

	if((bob=accept(alice, (struct sockaddr *)&server_bob, &len)) < 0){
		printf("Unable to accept connection!\n");
		exit(-1);
	}
	else
		printf("Alice has accepted a connection...\n");

	char *buffer;
	buffer=(char*)malloc(350*sizeof(char));
	while(1){
		bzero(buffer, strlen(buffer));

		recv(bob, buffer, 350, 0);
		printf("bob: %s\n",buffer);

		bzero(buffer, strlen(buffer));
		
		printf("Alice: ");
		scanf("%s",buffer);
		send(bob, buffer, strlen(buffer), 0);
		
		if((strncmp(buffer,"exit",4)) == 0){
			printf("Exiting....\n");
			break;
		}
	}
	close(bob);
}