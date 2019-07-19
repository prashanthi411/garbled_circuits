#include<stdio.h>
#include<stdlib.h>
#include "padding.h"

int main(void)
{
	char *text;
	text = (char *) malloc(100 * sizeof(char));
	printf("Enter string: ");
	scanf("%s",text);
	text = pad(text);
	printf("Padded string: %s\n", text);
	text = de_pad(text);
	printf("de_padded string: %s\n", text);

}