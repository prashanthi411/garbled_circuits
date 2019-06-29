#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "aes.h"
#include "aes.c"
#include "padding.h"

#define KEY_LENGTH 128

int main(){
	//Files to write the randomly generated keys
	FILE *alabel = fopen("alabel.txt", "w");
	FILE *blabel = fopen("blabel.txt", "w");
	FILE *oplabel = fopen("oplabel.txt", "w");
	FILE *initvec = fopen("initvec.txt", "w");
	FILE *ciph = fopen("ciph.txt", "w");
	FILE *hash = fopen("hash.txt", "w");

	struct AES_ctx *ctx;
	mpz_t a0, b0, a1, b1, c0, c1, key1, key2, key3, key4, iv, temp,key_len;
	char *op_0, *op_1, *k1, *k2, *k3, *k4, *iniv;
	mpz_init(a0);
	mpz_init(a1);
	mpz_init(b0);
	mpz_init(b1);
	mpz_init(c0);
	mpz_init(c1);
	mpz_init(iv);
	mpz_init(key1);
	mpz_init(key2);
	mpz_init(key3);
	mpz_init(key4);
	mpz_init(key_len);
	mpz_init(temp);
	int seed;

	//key_len=2^127
	mpz_set_ui(temp,1);
	mpz_mul_2exp(key_len,temp,KEY_LENGTH-1);

	printf("Enter seed: ");
	scanf("%d",&seed);
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,seed);

	//Generating random labels
	mpz_rrandomb(a0, state, KEY_LENGTH);
	//bitwise or with key_len so that the length is always 128 bits
	mpz_ior(a0,a0,key_len);
	mpz_rrandomb(a1, state, KEY_LENGTH);
	mpz_ior(a1,a1,key_len);
	mpz_rrandomb(b0, state, KEY_LENGTH);
	mpz_ior(b0,b0,key_len);
	mpz_rrandomb(b1, state, KEY_LENGTH);
	mpz_ior(b1,b1,key_len);
	mpz_rrandomb(c0, state, KEY_LENGTH);
	mpz_ior(c0,c0,key_len);
	mpz_rrandomb(c1, state, KEY_LENGTH);
	mpz_ior(c1,c1,key_len);
	mpz_rrandomb(iv, state, 16);

	//writing these to file
	gmp_fprintf(alabel, "%Zd\n", a0);
	gmp_fprintf(alabel, "%Zd", a1);
	gmp_fprintf(blabel, "%Zd\n", b0);
	gmp_fprintf(blabel, "%Zd", b1);
	gmp_fprintf(oplabel, "%Zd\n", c0);
	gmp_fprintf(oplabel, "%Zd", c1);
	gmp_fprintf(initvec, "%Zd\n", iv);

	//XORing random numbers to generate keys for AES
	mpz_xor(key1, a0, b0);
	mpz_ior(key1,key1,key_len);
	mpz_xor(key2, a0, b1);
	mpz_ior(key2,key2,key_len);
	mpz_xor(key3, a1, b0);
	mpz_ior(key3,key3,key_len);
	mpz_xor(key4, a1, b1);
	mpz_ior(key4,key4,key_len);

	//Encrypting c0, c1 using the above keys
	op_0 = (char*)malloc(150*sizeof(char));
	op_1 = (char*)malloc(150*sizeof(char));
	k1 = (char*)malloc(128*sizeof(char));
	k2 = (char*)malloc(128*sizeof(char));
	k3 = (char*)malloc(128*sizeof(char));
	k4 = (char*)malloc(128*sizeof(char));
	iniv = (char*)malloc(16*sizeof(char));

	mpz_get_str(op_0, 10, c0);
	mpz_get_str(op_1, 10, c1); 
	mpz_get_str(k1, 10, key1);
	mpz_get_str(k2, 10, key2); 
	mpz_get_str(k3, 10, key3);
	mpz_get_str(k4, 10, key4); 
	mpz_get_str(iniv, 10, iv); 

	int len;
	//encrypting using key1
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k1);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, 128);	
	len = strlen(op_0);
	fprintf(ciph, "%d\n", len);
	fprintf(ciph, "%s\n", op_0);

	//encrypting using key2
	mpz_get_str(op_0, 10, c0);
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k2);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, 128);
	len = strlen(op_0);
	fprintf(ciph, "%d\n", len);
	fprintf(ciph, "%s\n", op_0);

	//encrypting using key3
	mpz_get_str(op_0, 10, c0);
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k3);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, 128);
	len = strlen(op_0);
	fprintf(ciph, "%d\n", len);
	fprintf(ciph, "%s\n", op_0);

	//encrypting using key4
	op_1 = pad(op_1);
	AES_init_ctx(ctx, k4);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_1, 128);
	len = strlen(op_1);
	fprintf(ciph, "%d\n", len);
	fprintf(ciph, "%s\n", op_1);

	//send the above encryptions to Bob -- iv, four encryptions, hash of op_0 and op_1
	mpz_get_str(op_0, 10, c0);
	mpz_get_str(op_1, 10, c1); 
	//  var1 = hash(op_0);
	// var2 = hash(op_1);
	//write var1 and var2 to file hash.txt. 
	// send this file to Bob.

	printf("Sending the garbled table...\n");

	//clearing space for all variables
	mpz_clear(a0);
	mpz_clear(a1);
	mpz_clear(b0);
	mpz_clear(b1);
	mpz_clear(key1);
	mpz_clear(key2);
	mpz_clear(key3);
	mpz_clear(key4);
	mpz_clear(c0);
	mpz_clear(c1);
	mpz_clear(iv);
	free(op_1);
	free(op_0);
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(iniv);
}