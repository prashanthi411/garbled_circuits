#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "aes.h"
#include "aes.c"
#include "padding.h"
int main(){
	FILE *ciph, *test;

	char *e1, *e2, *e3, *e4;
	e1 = (char*)malloc(5000*sizeof(char));
	e2 = (char*)malloc(5000*sizeof(char));
	e3 = (char*)malloc(5000*sizeof(char));
	e4 = (char*)malloc(5000*sizeof(char));

	ciph = fopen("ciph.txt", "r");
	fscanf(ciph, "%s", e1);
	fscanf(ciph, "%s", e2);
	fscanf(ciph, "%s", e3);
	fscanf(ciph, "%s", e4);

	test = fopen("test.txt", "w");
	fprintf(test, "%s\n", e1);
	fprintf(test, "%s\n", e2);
	fprintf(test, "%s\n", e3);
	fprintf(test, "%s\n", e4);

}