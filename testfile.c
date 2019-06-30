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
	int n1, n2, n3, n4;
	l1 = (int*)malloc(sizeof(int));
	l2 = (int*)malloc(sizeof(int));
	l3 = (int*)malloc(sizeof(int));
	l4 = (int*)malloc(sizeof(int));
	
	n1 = (int)(*l1);
	n2 = (int)(*l2);
	n3 = (int)(*l3);
	n4 = (int)(*l4);
	//variables for reading encryptions from the file "ciph.txt"
	char *e1, *e2, *e3, *e4;
	ciph = fopen("ciph.txt", "r");
	fscanf(ciph, "%d\n", l1);	
	e1 = (char*)malloc((n1+5)*sizeof(char));
	for (int i = 0; i < n1; ++i)
	{
		e1[i] = fgetc(ciph);
		printf("e1[i]: %c\n", e1[i]);
//		fscanf(ciph, "%c", e1[i]);
	}	
	printf("e1: %s\n", e1);
	printf("%d\n", n1);
	fscanf(ciph, "%d\n", l2);
	e2 = (char*)malloc((n2+5)*sizeof(char));
	printf("%d\n", n2);
	for (int i = 0; i < n2; ++i)
	{
		e2[i] = fgetc(ciph);
	}	
	printf("e2: %s\n", e2);
	fscanf(ciph, "%d\n", l3);
	e3 = (char*)malloc((n3+5)*sizeof(char));
	printf("%d\n", n3);
	for (int i = 0; i < n3; ++i)
	{
		e3[i] = fgetc(ciph);
	}	
		printf("e3: %s\n", e3);
	fscanf(ciph, "%d\n", l4);
	e4 = (char*)malloc((n4+5)*sizeof(char));
	printf("%d\n", n4);
	for (int i = 0; i < n4; ++i)
	{
		e4[i] = fgetc(ciph);
	}	
	printf("e4: %s\n", e4);
	extra = fopen("extra.txt", "w");
	fprintf(extra, "%s\n", e1);
	fprintf(extra, "%s\n", e2);
	fprintf(extra, "%s\n", e3);
	fprintf(extra, "%s\n", e4);
}