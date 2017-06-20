#include "caesar.h"

#define N 10000 /*Fixed length for I/O*/
#define ALPHA 26 /*Alphabet length*/

void decrypt(char *str,int shift){

	int i,j,flag,temp_shift;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	for(i=0;i<strlen(str);i++){
		if(str[i] == ' '){
			/*when a space in encountered skip*/
		}
		else{
			for(j=0;j<ALPHA && flag != 1;j++){
				if(str[i] == alphabet[j]){
					temp_shift = (j-shift) % ALPHA;
					if(temp_shift < 0)    
						temp_shift += ALPHA;
						/*  In C '%' it's it's the remainder operator 
						    (not the modulus which is required in this case)
						    so sanitizing negative cases is needed.*/
					str[i] = alphabet[temp_shift];
					flag = 1;
				}
			}
			flag=0;
		}
	}

	return;
}

void encrypt(char *str,int shift){

	int i,j,flag;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	for(i=0;i<strlen(str);i++){
		if(str[i] == ' '){
			/*when a space in encountered skip*/
		}
		else{
			for(j=0;j<ALPHA && flag != 1;j++){
					/*if the correct match between the string to encrypt and the alphabet string is found*/ 
					if(str[i] == alphabet[j]){
						/*apply the shift given by the user, find the new letter 
						  and re-assign str[i] to the shifted letter*/
						str[i] = alphabet[(j+shift)%ALPHA];
						/*Setting flag=1 to prevent the for loop from further entering, 
						  the outer for loop will then go on the next letter of the string to encrypt */
						flag = 1;
					}
			}
			flag=0;
		}
	}

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
	printf("%s\n", text);
	write(fout,text,strlen(text));

	close(fout);
	return;
}

void Usage(){
	printf("Usage: caesar <shift> [-e | -d]  [-i] <input_file> [-o] <output_file>\n");
	return;
}

int main(int argc, char **argv){
	char *text;

	if (argc != 7){
		Usage();
		exit(0);
	}
	else if(strcmp(argv[3],"-i") == 0 && strcmp(argv[5],"-o") == 0){
			
		text = OpenFromFile(argv[4]);

		if (strcmp(argv[2],"-e") == 0){
			encrypt(text,atoi(argv[1]));

		}
		else if (strcmp(argv[2],"-d") == 0){
			decrypt(text,atoi(argv[1]));
		}
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
