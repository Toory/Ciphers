#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vigenere.h"

#define N 10000
#define ALPHA 26 /*Alphabet length*/

static char *alphabet = "abcdefghijklmnopqrstuvwxyz";

void Encrypt(char *text,int shift){
	int x;

	*text = tolower(*text);
	x = (*text - 'a' + shift) % 26;
	if (x < 0)
		x += ALPHA;
	*text = alphabet[x];
}

void Decrypt(char *text,int shift){
	int x;

	*text = tolower(*text);
	x = (*text - 'a' - shift) % 26;
	if (x < 0)
		x += ALPHA;
	*text = alphabet[x];
}

void GetShifts(int *shift,char *keyword){
	int i;

	for(i=0;i<strlen(keyword);i++){
		shift[i] = (keyword[i] - 'a') % 26;
	}
}

void Vigenere(char *text,char *keyword,char *choose){
	int *shifts,i,j;

	shifts = malloc(strlen(keyword) * sizeof(int));

	/*get the different shifts in an array of integers*/
	GetShifts(shifts,keyword);

	/*loop repeats for the length of the text*/
	for(i=0,j=0;i<strlen(text);i++,j++){

		if(isalpha(text[i]) == 0){
			/*if text[i] is not in the alphabet skip
			  and decrease j since the shift it's not used*/
			j--;
		}
		else{
			if((strcmp(choose,"-e") == 0))
				Encrypt(&text[i],shifts[j]);
			else
				Decrypt(&text[i],shifts[j]);
		}

		/*the j index is resetted once every strlen(keyword)*/
		if(j+1 == strlen(keyword)){
			j=-1;
		}
	}
	free(shifts);
}

char *OpenFromFile(char *fileIn){
	FILE *fin = fopen(fileIn, "r");
	char *text;

	text = malloc(N * sizeof(char));

	if(fin == NULL){
		fprintf(stderr, "Error, could not open file.\n");
		exit(-1);
	}

	/*read entire file and put it in text*/
	fread(text,N,1,fin);

	fclose(fin);
	return text;
}

void WriteToFile(char *text, char *fileOut){
	FILE *fout = fopen(fileOut, "w");

	if(fout == NULL){
		fprintf(stderr, "Error, could not open file.\n");
		exit(-1);
	}

	printf("%s\n", text);
	fwrite(text,strlen(text),1,fout);

	fclose(fout);
}

static void Usage(){
	printf("Usage: vigenere <keyword> [-e | -d]  [-i] <input_file> [-o] <output_file>\n");
}

int main(int argc, char **argv){
	char *text;

	if (argc != 7 ){
		Usage();
		exit(0);
	}
	else if(strcmp(argv[3],"-i") == 0 && strcmp(argv[5],"-o") == 0){

		text = OpenFromFile(argv[4]);

		if(strcmp(argv[2],"-e") == 0 || strcmp(argv[2],"-d") == 0)
			Vigenere(text,argv[1],argv[2]);
		else{
			Usage();
			exit(0);
		}

		WriteToFile(text,argv[6]);
	}
	else{
		Usage();
		exit(0);
	}

	return 0;
}
