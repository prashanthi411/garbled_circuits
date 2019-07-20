#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "../aes.h"
#include "../aes.c"
#include "../padding.h"
#include "sha3.c"

#define KEY_LENGTH 128

int main(){
	int output,n;
	struct AES_ctx* ctx;
	ctx = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));

	FILE *ciph, *initvec, *hash, *al_input, *message, *testhash;
	char *key = malloc(128*sizeof(char));
	char *e1, *e2, *e3, *e4;
	char *h_op0 = malloc(45*sizeof(char));
	char *h_op1 = malloc(45*sizeof(char));


	//reading from files
	ciph = fopen("ciph.txt", "r");
	initvec = fopen("initvec.txt", "r");
	hash = fopen("hash.txt", "r");
	al_input = fopen("al_input.txt", "r");
	message = fopen("bob_message.txt", "r");
	testhash = fopen("testhash.txt", "w");

	mpz_t a, b, k, temp, key_len; //alice's input key: a ; bob's input key: b.
	mpz_init(a);
	mpz_init(b);
	mpz_init(k);
	mpz_init(temp);
	mpz_init(key_len);

	mpz_set_ui(temp, 1);
	mpz_mul_2exp(key_len, temp, KEY_LENGTH-1);

	gmp_fscanf(al_input, "%Zd\n", a);
	gmp_fscanf(message, "%Zd", b);

	mpz_xor(k, a, b); //creating key by xor'ing a and b
	mpz_ior(k, k, key_len); //ensuring it's 128 bits
	mpz_get_str(key, 10, k); //converting key to string

	printf("key: %s\n", key);

	//Scanning encrypted gates from file ciph
	fscanf(ciph, "%d", &n);
	e1=(char *)malloc((n+1)*sizeof(char));
	for (int i = 0; i < n; ++i)
	{
		e1[i] = fgetc(ciph);
	}

	fscanf(ciph, "%d", &n);
	e2=(char *)malloc((n+1)*sizeof(char));
	for (int i = 0; i < n; ++i)
	{
		e2[i] = fgetc(ciph);
	}

	fscanf(ciph, "%d", &n);
	e3=(char *)malloc((n+1)*sizeof(char));
	for (int i = 0; i < n; ++i)
	{
		e3[i] = fgetc(ciph);
	}

	fscanf(ciph, "%d", &n);
	e4=(char *)malloc((n+1)*sizeof(char));
	for (int i = 0; i < n; ++i)
	{
		e4[i] = fgetc(ciph);
	}

	char *iniv = (char*)malloc(20*sizeof(char));
	fscanf(initvec, "%s", iniv);
	printf("iniv: %s\n", iniv);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e1, 48);
	printf("unpadding e1\n");
	e1 = de_pad(e1);
	printf("decrypted e1: %s\n", e1);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e2, 48);
	printf("unpadding e2\n");
	e2 = de_pad(e2);
	printf("decrypted e2: %s\n", e2);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e3, 48);
	printf("unpadding e3\n");
	e3 = de_pad(e3);
	printf("decrypted e3: %s\n", e3);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e4, 48);
	printf("unpadding e4\n");
	e4 = de_pad(e4);
	printf("decrypted e4: %s\n", e4);

	for (int i = 0; i < 39; ++i)
	{
		h_op0[i] = fgetc(hash);
	}
	fscanf(hash, "\n");
	for (int i = 0; i < 39; ++i)
	{
		h_op1[i] = fgetc(hash);
	}
	fprintf(testhash, "%s\n", h_op0);
	fprintf(testhash, "%s", h_op1);

	sha3(e1, 39, e1, 39);
	sha3(e2, 39, e2, 39);
	sha3(e3, 39, e3, 39);
	sha3(e4, 39, e4, 39);
	printf("e4: %s\n", e4);
	fprintf(testhash, "%s\n", e4);

	printf("Computing output...\n");

	if(strcmp(e1, h_op0)==0){
		output = 0;
		printf("e1; Output is: %d\n", output);
	}
	else if(strcmp(e1, h_op1)==0){
		output = 1;
		printf("e1; Output is: %d\n", output);
	}
	else if(strcmp(e2, h_op0)==0){
		output = 0;
		printf("e2; Output is: %d\n", output);
	}
	else if(strcmp(e2, h_op1)==0){
		output = 1;
		printf("e2; Output is: %d\n", output);
	}
	else if(strcmp(e3, h_op0)==0){
		output = 0;
		printf("e3; Output is: %d\n", output);
	}
	else if(strcmp(e3, h_op1)==0){
		output = 1;
		printf("e3; Output is: %d\n", output);
	}
	else if(strcmp(e4, h_op0)==0){
		output = 0;
		printf("e4; Output is: %d\n", output);
	}
	else if(strcmp(e4, h_op1)==0){
		output = 1;
		printf("e4; Output is: %d\n", output);
	}
	else{
		printf("Alice is probably fooling you!\n");
	}

}