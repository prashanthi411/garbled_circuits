#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pad(char* plaintext){
	int pad_value, length;
	char* padded;
	length = strlen(plaintext);
	printf("length: %d\n", length);

	pad_value = 16 - length%16;
	if(pad_value == 0){
		padded = (char *)malloc((length+17)*sizeof(char));
		strcpy(padded, plaintext);
		strcat(padded, "0000000000000000");
		strcpy(plaintext, padded);
		plaintext=(char *)realloc(padded,(length+17)*sizeof(char));
	}

	else{
		padded = (char *)malloc((length+pad_value+1)*sizeof(char));
		strcpy(padded, plaintext);
		for(int i=0 ; i< pad_value; i++){
			padded[length+i] = (char)pad_value;
		}
		padded[length+pad_value] = '\0';
		//printf("%s\n", padded);
		plaintext=(char *)realloc(padded,(length+17)*sizeof(char));
	}
}

void de_pad(char* plaintext){
	int pad_value, length;
	char* padded;
	length = strlen(plaintext);

	pad_value = plaintext[length-1];
	if(pad_value == 0){
		padded =  (char *)realloc(plaintext, (length-15)*sizeof(char));
	}

	else{
		padded =  (char *)realloc(plaintext, (length-pad_value+1)*sizeof(char));
	}
}