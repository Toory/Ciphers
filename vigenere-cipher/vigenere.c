#include "vigenere.h"

static char *alphabet = "abcdefghijklmnopqrstuvwxyz";

void Encrypt(char *str,int shift){

	int j;

	for(j=0;j<ALPHA;j++){
		if(*str == alphabet[j]){
			//printf("str = %c alphabet[%d] = %c - %d ",str,j,alphabet[j],((j+shift)%ALPHA));
			*str = alphabet[(j+shift)%ALPHA];
			break;
		}
	}
	return;
}

void Decrypt(char *str,int shift){

	int j,temp_shift;

	if(*str == ' '){
		/*when a space in encountered skip*/
	}
	else{
		for(j=0;j<ALPHA;j++){
			if(*str == alphabet[j]){
				temp_shift = (j-shift) % ALPHA;
				if(temp_shift < 0)    
					temp_shift += ALPHA;
					/*  In C '%' it's it's the remainder operator 
					    (not the modulus which is required in this case)
					    so sanitizing negative cases is needed.*/
				*str = alphabet[temp_shift];
				break;
			}
		}
	}

	return;
}

void GetShifts(int *shift,char *keyword){
	int i,j;

	for(i=0;i<strlen(keyword);i++){
		for(j=0;j<ALPHA;j++){
			if (keyword[i] == alphabet[j]){
				shift[i] = j;
				printf("shift[%d] = %d\n",i,shift[i]);
			} 
		}
	}

	return;
}

void Vigenere(char *text,char *keyword,char *choose){
	int *shifts,i,j;
	char c;

	shifts = malloc(strlen(keyword) * sizeof(int));

	GetShifts(shifts,keyword);

	for(i=0,j=0;i<strlen(text);i++,j++){
		/*c = text[i] is passed by reference in the encrypt/decrypt fuction*/
		c = text[i];
		
		if((strcmp(choose,"-e") == 0))
			Encrypt(&c,shifts[j]);
		else
			Decrypt(&c,shifts[j]);

		text[i] = c;
		if(c == ' ' || (ispunct(c)) != 0 || c == '\n')
			j--;
		else if(j+1 == strlen(keyword))
			j=-1;
		else
			continue;
	}

	printf("%s\n",text);

	return;
}

void WriteToFile(char *text, char *fileOut){

	int fout;
	/*open output file in write mode and if it doesn't exit it will be created
	   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH stand for write and read permission */
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fout = open(fileOut,O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fout == -1){
		fprintf(stderr, "Error opening %s\n", fileOut);
		exit(0);
	}
	
	write(fout,text,strlen(text));

	close(fout);
	return;
}

char *OpenFromFile(char *fileIn){
	
	int i,fin;
	char *text;
	text = malloc(N * sizeof(char));

	fin = open(fileIn,O_RDONLY);
	if (fin == -1){
		fprintf(stderr, "Error opening %s\n", fileIn);
		exit(0);
	}
	/*read entire file and put it in text*/
	read(fin,text,N);
	
	for(i=0;i<strlen(text);i++){
		/*converts the whole string to lowercase*/
		text[i] = tolower(text[i]);
	}

	close(fin);
	return text;
}

static void Usage(){
	printf("Usage: vigenere <keyword> [-e | -d]  [-i] <input_file> [-o] <output_file>\n");
	return;
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
