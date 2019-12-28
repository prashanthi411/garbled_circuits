#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "central.h"
int main()
{
	FILE *newfile = fopen("newfile.txt", "r");
	fflush(newfile);
	struct AES_ctx *ctx;
	ctx = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));	

	char *op = malloc(40*sizeof(char));;
	char *new = malloc(40*sizeof(char));
	char *key = malloc(40*sizeof(char));
	char iv[6];
	strcpy(op, "340282366920009858498774741110063366144IIIIIIIII");
	mpz_t k;
	mpz_init(k);
	gmp_fscanf(newfile, "%Zd", k);

	key = bin_to_char(k,KEY_LENGTH);

	strcpy(iv, "65039");

	printf("before decryption\n");
	printf("op = %s\n", op);

	printf("after encryption\n");
	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iv);
	AES_CBC_encrypt_buffer(ctx, op, CIPH_LENGTH);	
	printf("op = %s\n", op);


	printf("after decryption\n");
	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iv);
	AES_CBC_decrypt_buffer(ctx, op, CIPH_LENGTH);
	new = de_pad(op);
	printf("op = %s\n", new);
	return 0;
}