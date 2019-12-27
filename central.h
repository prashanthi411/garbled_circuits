#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "aes.h"
#include "aes.c"
#include "sha3.c"

#define KEY_LENGTH AES_KEYLEN*8 //128-bit key
#define IV_LENGTH AES_BLOCKLEN //string length 16
#define LABEL_LENGTH (int)ceil(log10(pow(2,KEY_LENGTH) - 1)) //Label length(key length in decimal)
#define CIPH_LENGTH LABEL_LENGTH + (AES_BLOCKLEN - LABEL_LENGTH%AES_BLOCKLEN)
#define HASH_LENGTH LABEL_LENGTH

char * pad(char* plaintext){
	int pad_value, length;
	char* padded;
	length = strlen(plaintext);
	pad_value = 16 - length%16;
	padded = (char *)malloc((length+pad_value+1)*sizeof(char));
	strcpy(padded, plaintext);
	for(int i=0 ; i < pad_value; i++){
		padded[length+i] = (char)(pad_value+64);
	}
	padded[length+pad_value] = '\0';
	free(plaintext);
	return padded;
}

char *de_pad(char* plaintext){
	int pad_value, length;
	char *unpadded;
	length = strlen(plaintext);
	pad_value = ((int)((char)plaintext[length-1]))-64;
	unpadded =  (char *)malloc((length-pad_value)*sizeof(char));
	if(length-pad_value>0){
		for (int i=0; i<length-pad_value; i++){
			unpadded[i] = plaintext[i]; 
	}
	free(plaintext);
	return unpadded;
	}

}