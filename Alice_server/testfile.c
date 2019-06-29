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

	
int main(){
	FILE *ciph, *extra;
	int *l1, *l2, *l3, *l4;
	l1 = (int*)malloc(sizeof(int));
	l2 = (int*)malloc(sizeof(int));
	l3 = (int*)malloc(sizeof(int));
	l4 = (int*)malloc(sizeof(int));
	
	//variables for reading encryptions from the file "ciph.txt"
	char *e1, *e2, *e3, *e4;
	e1 = (char*)malloc(150*sizeof(char));
	e2 = (char*)malloc(150*sizeof(char));
	e3 = (char*)malloc(150*sizeof(char));
	e4 = (char*)malloc(150*sizeof(char));
	ciph = fopen("ciph.txt", "r");
	fscanf(ciph, "%d\n", l1);
	fgets(e1, (int)(*l1+1), ciph);
	printf("%d\n", *l1);
	fscanf(ciph, "%d\n", l2);
	printf("%d\n", *l2);
	fgets(e2, (int)(*l2+1), ciph);
	fscanf(ciph, "%d\n", l3);
	printf("%d\n", *l3);
	fgets(e3, (int)(*l3+1), ciph);
	fscanf(ciph, "%d\n", l4);
	printf("%d\n", *l4);
	fgets(e4, (int)(*l4+1), ciph);

	extra = fopen("extra.txt", "w");
	fprintf(extra, "%s\n", e1);
	fprintf(extra, "%s\n", e2);
	fprintf(extra, "%s\n", e3);
	fprintf(extra, "%s\n", e4);
}