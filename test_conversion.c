#include<stdio.h>
#include<stdlib.h>
#include <gmp.h>

//Converts a given bitstring to a character array of equivalent binary value
char* bin_to_char(mpz_t inputstring, int length, char* string)
{
	mpz_t char_value,temp,bitstring;
	mpz_init(char_value);
	mpz_init(temp);
	mpz_init(bitstring);
	mpz_set(bitstring,inputstring);
	int n=0;
	//Allocating space for character array
	//string = (char *) malloc((length/8)*sizeof(char));

	mpz_set_ui(temp, 1);
	mpz_mul_2exp(temp, temp, 8);
	mpz_sub_ui(temp,temp,1);

	for(int i=length;i>0;i-=8){
		//Extract bottom 8 bits from bitstring
		mpz_and(char_value, bitstring, temp);

		//Store obtained bits in the character array
		string[n]=mpz_get_ui(char_value);
		n++;

		//Remove bottom 8 bits from bitstring
		mpz_fdiv_q_2exp(bitstring,bitstring,8);
	}

	return string;

}

int main()
{
	mpz_t a;
	char* str;
	str = (char *) malloc(20*sizeof(char));
	mpz_init(a);
	int seed;

	printf("Enter seed: ");
	scanf("%d",&seed);

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);

	mpz_rrandomb(a, state, 64);
	mpz_get_str(str, 10, a);
	printf("%s\n", str);
	//mpz_set_ui(a,66);
	bin_to_char(a,64,str);
	//printf("%s\n", str);
	for(int i=0;i<8;i++){
		printf("%c (%d)",str[i],(int)str[i]);
	}

	printf("\n");

}