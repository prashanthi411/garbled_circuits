#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<fcntl.h> 
#include<unistd.h>
#include <strings.h>
int main(int argc, char** argv){
	int alice, bob;
	alice = socket(AF_INET, SOCK_STREAM, 0); //establishing an endpoint

	struct sockaddr_in server_alice;
	struct sockaddr_in server_bob;
	server_alice.sin_family=AF_INET;
	server_alice.sin_port=htons(atoi(argv[1]));
	server_alice.sin_addr.s_addr=INADDR_ANY;
	bzero(&server_alice.sin_zero, 8);
	
	//reading x_0 and x_1 from file
	FILE *randomx = fopen("randomx.txt", "r"); //file to read randomly generated x_0, x_1 by Alice
	char *x_0 = (char*) malloc(500*sizeof(char));
	char *x_1 = (char*) malloc(500*sizeof(char));
	char *c = (char*) malloc(500*sizeof(char));

	fgets(x_0, 500, randomx);
	fgets(x_1, 500, randomx);
	printf("x_0 as string: %s\n", x_0);

	int len = sizeof(struct sockaddr_in);

	if((bind(alice, (struct sockaddr *)&server_alice, sizeof(struct sockaddr_in))) != 0){
		printf("Server binding unsuccessful!\n");
		exit(0);
	}
	else
	{
		printf("Server bound to descriptor alice. \n");
	}

	//Waiting for connection requests
	if((listen(alice, 5))==-1) 
	{
		perror("\nListen failed! ");
		exit(0);
	}
	else
	{
		printf("Alice is listening...\n");
	}

	//Accepting a connection
	if((bob = accept(alice, (struct sockaddr *)&server_bob, &len))==-1)
	{
		perror("\nCouldn't accept any network! ");
		exit(0);
	}
	else
	{
		printf("Connected to Bob!\n");
	}
	
	/**********************************************
	//Execute alice_ot1.c before the next line
	***********************************************/

	//Oblivious transfer: sending x_0, x_1
	send(bob, x_0, strlen(x_0), 0);
	send(bob, x_1, strlen(x_1), 0);
	
	//Receiving c=(x_b + (k^e)) mod n	
	FILE *bob_c = fopen("bob_c.txt", "w"); //file to store c from Bob
	recv(bob, c, 500, 0);
	fprintf(bob_c, "%s\n", c);
	
	/**********************************************
	//Execute alice_ot1.c before the next line
	***********************************************/

	//reading m'_0 and m'_1 from file
	FILE *enc_messages = fopen("enc_messages.txt", "r"); //file to read randomly generated x_0, x_1 by Alice
	char *md_0 = (char*) malloc(500*sizeof(char));
	char *md_1 = (char*) malloc(500*sizeof(char));
	fgets(md_0, 500, enc_messages);
	fgets(md_1, 500, enc_messages);

	//Sending m'_0 and m'_1 to Bob
	send(bob, md_0, strlen(md_0), 0);
	send(bob, md_1, strlen(md_1), 0);	

	//Execute bob_ot2.c now.
	close(bob);
}