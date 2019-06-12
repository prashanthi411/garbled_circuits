#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

#include<netinet/in.h>

int main(int argc, char** argv)
{
	int bob,alice,len;
	FILE *random,*c_bob, *enc_messages;

	alice = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_alice;
	struct sockaddr_in server_bob;
	server_alice.sin_family=AF_INET;
	server_alice.sin_port=htons(atoi(argv[1]));
	server_alice.sin_addr.s_addr=INADDR_ANY;
	bzero(&server_alice.sin_zero, 8);

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
	
	//Fork to execute alice1
	pid_t pid=fork();

	//child process
	if(pid==0)
	{
		//Execute alice1
		static char *argv[]={"alice1",NULL};
		execv("alice1", argv);
		exit(-1);
	}

	//Waits for child process to finish
	waitpid(pid,0,0);

	random=fopen("randomx.txt","r");
	
	fscanf(random,"%s",buffer);
	send(bob, buffer, strlen(buffer), 0);
	bzero(buffer, strlen(buffer));

	fscanf(random,"%s",buffer);
	send(bob, buffer, strlen(buffer), 0);
	bzero(buffer, strlen(buffer));

	
	c_bob = fopen("bob_c.txt", "w"); //stores c = (x_b + k^e) mod n

	recv(bob, buffer, 350, 0);
	fprintf(c_bob,"%s",buffer);
	bzero(buffer, strlen(buffer));


	//Fork to execute alice2
	pid=fork();

	//child process
	if(pid==0)
	{
		//child process alice2
		static char *argv[]={"alice2",NULL};
		execv("alice2", argv);
		exit(-1);
	}

	//Waits for child process to finish
	waitpid(pid,0,0);

	enc_messages = fopen("enc_messages.txt", "r");

	fscanf(enc_messages,"%s",buffer);
	send(bob, buffer, strlen(buffer), 0);
	bzero(buffer, strlen(buffer));

	fscanf(enc_messages,"%s",buffer);
	send(bob, buffer, strlen(buffer), 0);
	bzero(buffer, strlen(buffer));

	close(bob);
}