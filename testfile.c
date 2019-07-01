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
#include "aes.c"
#include<gmp.h>
#include "padding.h"
int main(){
	struct AES_ctx* ctx;

	FILE *ciph, *extra, *keys, *initvec;
	//variables for reading encryptions from the file "ciph.txt"
	mpz_t ky1, ky2, ky3, ky4;
	char *e1, *e2, *e3, *e4, *k1, *k2, *k3, *k4, *iniv;
	int n1, n2, n3, n4, *l1, *l2, *l3, *l4;
	l1 = (int*)malloc(sizeof(int));
	l2 = (int*)malloc(sizeof(int));
	l3 = (int*)malloc(sizeof(int));
	l4 = (int*)malloc(sizeof(int));

	k1 = (char*)malloc(150*sizeof(char));
	k2 = (char*)malloc(150*sizeof(char));
	k3 = (char*)malloc(150*sizeof(char));
	k4 = (char*)malloc(150*sizeof(char));
	iniv = (char*)malloc(20*sizeof(char));

	keys = fopen("keys.txt", "r");
	fscanf(keys, "%s", k1);
	fscanf(keys, "\n");
	fscanf(keys, "%s", k2);
	fscanf(keys, "\n");
	fscanf(keys, "%s", k3);
	fscanf(keys, "\n");
	fscanf(keys, "%s", k4);
	fscanf(keys, "\n");

	printf("k1: %s\n", k1);
	printf("k1: %s\n", k2);
	printf("k1: %s\n", k3);
	printf("k1: %s\n", k4);
	initvec = fopen("initvec.txt", "r");	
	fscanf(initvec, "%s", iniv);
	printf("iniv: %s\n", iniv);
	ciph = fopen("ciph.txt", "r");
	
	fscanf(ciph, "%d\n", l1);	
	n1 = (int)(*l1);
	e1 = (char*)malloc((n1+5)*sizeof(char));
	for (int i = 0; i < n1; ++i)
	{
		e1[i] = fgetc(ciph);
	}
	printf("e1: %s\n", e1);
	
	ctx->RoundKey = malloc(AES_keyExpSize*sizeof(uint8_t));
	ctx->Iv = malloc(AES_BLOCKLEN*sizeof(uint8_t));
	AES_CBC_decrypt_buffer(ctx, e1, 48);
	printf("op_0 after decryption: %s\n", e1);
	printf("e1: %s\n", e1);	
	AES_init_ctx(ctx, k1);
	AES_ctx_set_iv(ctx, iniv);
	fscanf(ciph, "%d\n", l2);	
	n2 = (int)(*l2);
	e2 = (char*)malloc((n2+5)*sizeof(char));
	for (int i = 0; i < n2; ++i)
	{
		e2[i] = fgetc(ciph);
	}		


	fscanf(ciph, "%d\n", l3);	
	n3 = (int)(*l3);
	e3 = (char*)malloc((n3+5)*sizeof(char));
	for (int i = 0; i < n3; ++i)
	{
		e3[i] = fgetc(ciph);
	}	


	fscanf(ciph, "%d\n", l4);	
	n4 = (int)(*l4);
	e4 = (char*)malloc((n4+5)*sizeof(char));
	for (int i = 0; i < n4; ++i)
	{
		e4[i] = fgetc(ciph);
	}

	fclose(ciph);

	// fprintf(extra, "%s\n", h_op0);
	// fprintf(extra, "%s\n", h_op1);
}