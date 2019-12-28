//Central header file for definitions, can be split into 2 because bab_client.c only needs the padding functions
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gmp.h>     
#include "aes.h"
#include "aes.c"
#include "sha3.c"
#include<math.h>

#define KEY_LENGTH AES_KEYLEN*8 //128-bit key
#define IV_LENGTH AES_BLOCKLEN //string length 16
#define LABEL_LENGTH (int)ceil(log10(pow(2,KEY_LENGTH) - 1)) //Label length(key length in decimal)
#define CIPH_LENGTH LABEL_LENGTH + (AES_BLOCKLEN - LABEL_LENGTH%AES_BLOCKLEN)
#define HASH_LENGTH LABEL_LENGTH

char *pad(char* plaintext)
{
	int pad_value, length;
	char* padded;
	length = strlen(plaintext);
	pad_value = 16 - length%16;
	padded = (char *)malloc((length+pad_value+1)*sizeof(char));
	strcpy(padded, plaintext);
	for(int i=0 ; i < pad_value; i++)
	{
		padded[length+i] = (char)(pad_value+64);
	}
	padded[length+pad_value] = '\0';
	free(plaintext);
	return padded;
}

char *de_pad(char* plaintext)
{
	int pad_value, length;
	length = strlen(plaintext);
	pad_value = ((int)((char)plaintext[length-1]))-64;
	if((length-pad_value>0))// && (pad_value>0))
	{
		char *unpadded =  (char*)malloc((length-pad_value)*sizeof(char));
		for (int i=0; i<length-pad_value; i++)
		{
			unpadded[i] = plaintext[i]; 
		}
		free(plaintext);
		return unpadded;
	}
	else
	{
		return plaintext;
	}

}

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

	for(int i=length;i>0;i-=8)
	{
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
