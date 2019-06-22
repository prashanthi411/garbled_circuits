#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pad(char* plaintext){
	int pad_value,length;
	char* padded;
	length=strlen(plaintext);

	pad_value = length%16;
	if(pad_value==0){
		padded =  (char *)malloc((length+17)*sizeof(char));
		strcpy(padded,plaintext);
		strcat(padded,"0000000000000000");
		free(plaintext);
		plaintext=padded;
	}

	else{
		padded =  (char *)malloc((length+pad_value+1)*sizeof(char));
		strcpy(padded,plaintext);
		for(int i=0;i<pad_value;i++){
			padded[length+i]=(char)pad_value;
		}
		padded[length+pad_value]='\0';
		free(plaintext);
		plaintext=padded;
	}
}

void de_pad(char* plaintext){
	int pad_value,length;
	length=strlen(plaintext);
	char *padded;
	pad_value = plaintext[length-1];
	if(pad_value==0){
		plaintext = (char*) realloc(plaintext, (length-15)*sizeof(char));
	}

	else{
		plaintext = (char*) realloc(plaintext, (length-pad_value+1)*sizeof(char));
		strcpy(padded,plaintext);
		for(int i=0;i<pad_value;i++){
			padded[length+i]=(char)pad_value;
		}
		padded[length+pad_value]='\0';
		free(plaintext);
		plaintext=padded;
	}
}