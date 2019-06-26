#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "aes.h"
#include "aes.c"
int main()
{	struct AES_ctx *ctx;
	mpz_t a, b, k;
	mpz_init(a);
	mpz_init(b);
	char *key = (char*) malloc(128*sizeof(char));
	char *iniv = (char*) malloc(128*sizeof(char));
	char *ctext = (char*) malloc(128*sizeof(char));
	FILE *al = fopen("alabel.txt", "r");
	FILE *ci = fopen("ciph.txt", "r");
	FILE *in = fopen("initvec.txt", "r");
	gmp_fscanf(al, "%Zd", a);
	gmp_fscanf(al, "%Zd", b); 
	fscanf(ci, "%s", ctext);
	fscanf(in, "%s", iniv);
	mpz_xor(k, a, b);
	gmp_printf("%Zd\n", k);
	mpz_get_str(key, 10, k);
	//printf("%s\n", key);
	// AES_init_ctx(ctx, key);
	// AES_ctx_set_iv(ctx, iniv);
	//AES_CBC_decrypt_buffer(ctx, ctext, 128);
	return 0;
}