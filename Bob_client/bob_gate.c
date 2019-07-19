#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "aes.h"
#include "aes.c"
#include "padding.h"
#include "sha3.c"
#define KEY_LENGTH 128

int main(){
	int output;
	struct AES_ctx* ctx;
	ctx = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));

	FILE *ciph, *initvec, *hash, *al_input, *message;
	char *key = malloc(128*sizeof(char));
	char *e1 = malloc(180*sizeof(char));
	char *e2 = malloc(180*sizeof(char));
	char *e3 = malloc(180*sizeof(char));
	char *e4 = malloc(180*sizeof(char));
	char *h_op0 = malloc(45*sizeof(char));
	char *h_op1 = malloc(45*sizeof(char));


	//reading from files
	ciph = fopen("ciph.txt", "r");
	initvec = fopen("initvec.txt", "r");
	hash = fopen("hash.txt", "r");
	al_input = fopen("al_input.txt", "r");
	message = fopen("bob_message.txt", "r");


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

	fscanf(ciph, "%s", e1);
	fscanf(ciph, "\n");
	fscanf(ciph, "%s", e2);
	fscanf(ciph, "\n");
	fscanf(ciph, "%s", e3);
	fscanf(ciph, "\n");
	fscanf(ciph, "%s", e4);

	char *iniv = (char*)malloc(20*sizeof(char));
	fscanf(initvec, "%s", iniv);
	printf("iniv: %s\n", iniv);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e1, 48);
	de_pad(e1);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e2, 48);
	de_pad(e2);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e3, 48);
	de_pad(e3);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e4, 48);
	de_pad(e4);
	
	fscanf(hash, "%s", h_op0);
	fscanf(hash, "\n");
	fscanf(hash, "%s", h_op1);

	sha3(e1, 39, e1, 39);
	sha3(e2, 39, e2, 39);
	sha3(e3, 39, e3, 39);
	sha3(e4, 39, e4, 39);

	printf("Computing output...\n");

	if(strcat(e1, h_op0)==0){
		output = 0;
		printf("e1; Output is: %d\n", output);
	}
	else if(strcat(e1, h_op1)==0){
		output = 1;
		printf("e1; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op0)==0){
		output = 0;
		printf("e2; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op1)==0){
		output = 1;
		printf("e2; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op0)==0){
		output = 0;
		printf("e3; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op1)==0){
		output = 1;
		printf("e3; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op0)==0){
		output = 0;
		printf("e4; Output is: %d\n", output);
	}
	else if(strcat(e2, h_op1)==0){
		output = 1;
		printf("e4; Output is: %d\n", output);
	}
	else{
		printf("Alice is probably fooling you!\n");
	}

}