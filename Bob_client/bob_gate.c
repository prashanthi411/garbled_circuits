#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "../central.h"

int main(){
	int output;
	struct AES_ctx* ctx;
	ctx = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));

	FILE *ciph, *initvec, *hash, *al_input, *message, *testhash;
	char *key = malloc(128*sizeof(char));
	char *e1, *e2, *e3, *e4;
	char *h_op0 = malloc(45*sizeof(char));
	char *h_op1 = malloc(45*sizeof(char));

	int n1, n2, n3, n4, *l1, *l2, *l3, *l4;
	l1 = (int*)malloc(sizeof(int));
	l2 = (int*)malloc(sizeof(int));
	l3 = (int*)malloc(sizeof(int));
	l4 = (int*)malloc(sizeof(int));

	//reading from files
	ciph = fopen("ciph.txt", "r");
	initvec = fopen("initvec.txt", "r");
	hash = fopen("hash.txt", "r");
	al_input = fopen("al_input.txt", "r");
	message = fopen("bob_message.txt", "r");
	testhash = fopen("testhash.txt", "w");
	FILE *anothertest = fopen("anothertest.txt", "w");

	mpz_t a, b, k, temp, key_len; //alice's input key: a ; bob's input key: b.
	mpz_init(a);
	mpz_init(b);
	mpz_init(k);
	mpz_init(temp);
	mpz_init(key_len);

	mpz_set_ui(temp, 1);
	mpz_mul_2exp(key_len, temp, KEY_LENGTH-1);

	gmp_fscanf(al_input, "%Zd", a);
	gmp_fscanf(message, "%Zd", b);

	mpz_xor(k, a, b); //creating key by xor'ing a and b
	mpz_ior(k, k, key_len); //ensuring it's 128 bits
	mpz_get_str(key, 10, k); //converting key to string

	//printf("key: %s\n", key);

	//Scanning encrypted gates from file ciph
	e1 = (char*)malloc((CIPH_LENGTH+2)*sizeof(char));
	for (int i = 0; i < CIPH_LENGTH; ++i)
	{
		e1[i] = fgetc(ciph);
	}
	fprintf(anothertest, "%s\n", e1);

	e2 = (char*)malloc((CIPH_LENGTH+2)*sizeof(char));
	for (int i = 0; i < CIPH_LENGTH; ++i)
	{
		e2[i] = fgetc(ciph);
	}
	fprintf(anothertest, "%s\n", e2);

	e3 = (char*)malloc((CIPH_LENGTH+2)*sizeof(char));
	for (int i = 0; i < CIPH_LENGTH; ++i)
	{
		e3[i] = fgetc(ciph);
	}
	fprintf(anothertest, "%s\n", e3);

	e4 = (char*)malloc((CIPH_LENGTH+2)*sizeof(char));
	for (int i = 0; i < CIPH_LENGTH; ++i)
	{
		e4[i] = fgetc(ciph);
	}
	fprintf(anothertest, "%s\n", e4);

	char *iniv = (char*)malloc(20*sizeof(char));
	fscanf(initvec, "%s", iniv);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e1, n1);
	e1 = de_pad(e1);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e2, n2);
	e2 = de_pad(e2);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e3, n3);
	e3 = de_pad(e3);

	AES_init_ctx(ctx, key);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_decrypt_buffer(ctx, e4, n4);
	e4 = de_pad(e4);


	for (int i = 0; i < HASH_LENGTH; ++i)
	{
		h_op0[i] = fgetc(hash);
	}
	
	for (int i = 0; i < HASH_LENGTH; ++i)
	{
		h_op1[i] = fgetc(hash);
	}

	sha3(e1, 39, e1, 39);
	sha3(e2, 39, e2, 39);
	sha3(e3, 39, e3, 39);
	sha3(e4, 39, e4, 39);

	//printf("e4: %s\n", e4);
	//fprintf(testhash, "%s\n", e4);

	printf("Computing output...\n");

	if(strcmp(e1, h_op0)==0){
		output = 0;
		printf("It's e1: Output is: %d\n", output);
	}
	else if(strcmp(e1, h_op1)==0){
		output = 1;
		printf("It's e1: Output is: %d\n", output);
	}
	else if(strcmp(e2, h_op0)==0){
		output = 0;
		printf("It's e2: Output is: %d\n", output);
	}
	else if(strcmp(e2, h_op1)==0){
		output = 1;
		printf("It's e2: Output is: %d\n", output);
	}
	else if(strcmp(e3, h_op0)==0){
		output = 0;
		printf("It's e3: Output is: %d\n", output);
	}
	else if(strcmp(e3, h_op1)==0){
		output = 1;
		printf("It's e3: Output is: %d\n", output);
	}
	else if(strcmp(e4, h_op0)==0){
		output = 0;
		printf("It's e4: Output is: %d\n", output);
	}
	else if(strcmp(e4, h_op1)==0){
		output = 1;
		printf("It's e4: Output is: %d\n", output);
	}
	else{
		printf("Alice is probably fooling you!\n");
	}

}