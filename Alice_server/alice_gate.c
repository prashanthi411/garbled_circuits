#include<stdio.h>
#include<gmp.h>     
#include<stdlib.h> 
#include<stdint.h>
#include<string.h>
#include "../central.h"
#include<math.h>

#define KEY_LENGTH AES_KEYLEN*8 //128-bit key
#define IV_LENGTH AES_BLOCKLEN //string length 16
#define LABEL_LENGTH (int)ceil(log10(pow(2,KEY_LENGTH) - 1)) //Label length(key length in decimal)
#define CIPH_LENGTH LABEL_LENGTH + (AES_BLOCKLEN - LABEL_LENGTH%AES_BLOCKLEN)

//Converts a given bitstring to a character array of equivalent binary value
char* bin_to_char(mpz_t inputstring, int length)
{
	mpz_t char_value,temp,bitstring;
	mpz_init(char_value);
	mpz_init(temp);
	mpz_init(bitstring);
	mpz_set(bitstring,inputstring);
	int n=0;
	//Allocating space for character array
	char* string = (char *) malloc((length/8)*sizeof(char));

	mpz_set_ui(temp, 1);
	mpz_mul_2exp(temp, temp, 8);
	mpz_sub_ui(temp,temp,1);

	for(int i=length;i>0;i-=8){
		//Extract bottom 8 bits from bitstring
		mpz_and(char_value, bitstring, temp);
		
		//Store obtained bits in the character array
		string[n]=(char)mpz_get_si(char_value);
		n++;

		//Remove bottom 8 bits from bitstring
		mpz_fdiv_q_2exp(bitstring,bitstring,8);
	}

	return string;

}


int main()
{
	//Files to write the randomly generated keys
	FILE *alabel = fopen("alabel.txt", "w+");
	FILE *blabel = fopen("blabel.txt", "w+");
	FILE *oplabel = fopen("oplabel.txt", "w+");
	FILE *initvec = fopen("initvec.txt", "w+");
	FILE *ciph = fopen("ciph.txt", "w+");
	FILE *hash = fopen("hash.txt", "w+");
	FILE *keys = fopen("keys.txt", "w+"); //temp

	struct AES_ctx *ctx;
	ctx = (struct AES_ctx*)malloc(sizeof(struct AES_ctx));
	mpz_t a0, b0, a1, b1, c0, c1, key1, key2, key3, key4, iv, temp1, temp2, key_len, iv_len;
	char *op_0, *op_1, *k1, *k2, *k3, *k4, *iniv;
	//int n1, n2, n3, n4;

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
	mpz_init(iv_len);
	mpz_init(temp1);
	mpz_init(temp2);
	int seed;

	//setting key_len = 2^(KEY_LENGTH-1)
	mpz_set_ui(temp1, 1);
	mpz_mul_2exp(key_len, temp1, KEY_LENGTH-1);

	//setting iv_len = 2^(IV_LENGTH-1)
	mpz_set_ui(temp2, 1);
	mpz_mul_2exp(iv_len, temp2, IV_LENGTH-1);

	printf("Enter seed: ");
	scanf("%d", &seed);
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);

	//Generating random labels
	mpz_rrandomb(a0, state, KEY_LENGTH);
	mpz_ior(a0, a0, key_len); //bitwise or with key_len so that the length is always 128 bits
	mpz_rrandomb(a1, state, KEY_LENGTH);
	mpz_ior(a1, a1, key_len);
	mpz_rrandomb(b0, state, KEY_LENGTH);
	mpz_ior(b0, b0, key_len);
	mpz_rrandomb(b1, state, KEY_LENGTH);
	mpz_ior(b1, b1, key_len);
	mpz_rrandomb(c0, state, KEY_LENGTH);
	mpz_ior(c0, c0, key_len);
	mpz_rrandomb(c1, state, KEY_LENGTH);
	mpz_ior(c1, c1, key_len);
	mpz_rrandomb(iv, state, IV_LENGTH);
	mpz_ior(iv, iv, iv_len);

	//writing these to file
	gmp_fprintf(alabel, "%Zd\n", a0);
	gmp_fprintf(alabel, "%Zd", a1);
	gmp_fprintf(blabel, "%Zd\n", b0);
	gmp_fprintf(blabel, "%Zd", b1);
	gmp_fprintf(oplabel, "%Zd\n", c0);
	gmp_fprintf(oplabel, "%Zd", c1);
	gmp_fprintf(initvec, "%Zd", iv);

	//XORing random numbers to generate keys for AES
	mpz_xor(key1, a0, b0);
	mpz_ior(key1, key1, key_len); //bitwise or with key_len so that the length is always 128 bits
	//gmp_printf("key: %Zd\n", key1);
	mpz_xor(key2, a0, b1);
	mpz_ior(key2, key2, key_len);
	mpz_xor(key3, a1, b0);
	mpz_ior(key3, key3, key_len);
	mpz_xor(key4, a1, b1);
	mpz_ior(key4, key4, key_len);

	//Encrypting c0, c1 using the above keys
	op_0 = (char*)malloc(500*sizeof(char));
	op_1 = (char*)malloc(500*sizeof(char));
	k1 = (char*)malloc(128*sizeof(char));
	k2 = (char*)malloc(128*sizeof(char));
	k3 = (char*)malloc(128*sizeof(char));
	k4 = (char*)malloc(128*sizeof(char));
	iniv = (char*)malloc(20*sizeof(char));

	mpz_get_str(op_0, 10, c0);
	mpz_get_str(op_1, 10, c1); 
	k1 = bin_to_char(key1,KEY_LENGTH);
	k2 = bin_to_char(key2,KEY_LENGTH);
	k3 = bin_to_char(key3,KEY_LENGTH);
	k4 = bin_to_char(key4,KEY_LENGTH);
	iniv = bin_to_char(iv, IV_LENGTH); 

	/**********Writing keys to file***********/

	fprintf(keys, "%s\n", k1);
	fprintf(keys, "%s\n", k2);
	fprintf(keys, "%s\n", k3);
	fprintf(keys, "%s\n", k4);

	/*****************************************/
	//encrypting using key1
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k1);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, CIPH_LENGTH);	
	fprintf(ciph, "%s", op_0); //writing only the ciphertext (and not ciphertext length) to ciph.txt

	//encrypting using key2
	mpz_get_str(op_0, 10, c0);
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k2);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, CIPH_LENGTH);
	fprintf(ciph, "%s", op_0);

	//encrypting using key3
	mpz_get_str(op_0, 10, c0);
	op_0 = pad(op_0);
	AES_init_ctx(ctx, k3);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_0, CIPH_LENGTH);
	fprintf(ciph, "%s", op_0);

	op_1 = pad(op_1);
	AES_init_ctx(ctx, k4);
	AES_ctx_set_iv(ctx, iniv);
	AES_CBC_encrypt_buffer(ctx, op_1, CIPH_LENGTH);
	fprintf(ciph, "%s", op_1);

	//send the above encryptions to Bob -- iv, four encryptions, hash of op_0 and op_1
	mpz_get_str(op_0, 10, c0);
	mpz_get_str(op_1, 10, c1); 
	sha3(op_0, LABEL_LENGTH, op_0, HASH_LENGTH);
	sha3(op_1, LABEL_LENGTH, op_1, HASH_LENGTH);
	fprintf(hash, "%s", op_0); //writing only the hash and not hash length now
	fprintf(hash, "%s", op_1);

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
	//free(iniv);
	fclose(alabel);
	fclose(blabel);
	fclose(initvec);
	fclose(ciph);
	fclose(oplabel);
	fclose(hash);
	fclose(keys);	
}