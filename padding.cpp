#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pad(char* plaintext){
	int pad_value = (8 - plaintext.length()%8); // pad with pad_value, pad_value times. 
	char pad_value_character = char(pad_value);
	string temp1 = "0" + pad_value_character;
	string temp2;
	for(int i=0;i<pad_value;i++)
	{
		temp2 = temp2 + temp1;
	}
	plaintext = plaintext + temp2;
	printf("Plaintext padded: %s\n", plaintext);
}

void de_pad(char* plaintext){
	int pad_value = 2*(8 - plaintext.length()%8);//the total number of spaces that padding takes away. 
	int nobytes = (plaintext.length() - pad_value)/2; //number of bytes of the actual cipher/plaintext
	plaintext = plaintext.substr(0, nobytes); //un-padding
	return plaintext;
}