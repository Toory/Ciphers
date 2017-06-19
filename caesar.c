#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10000 /*Fixed length for I/O*/
#define ALPHA 26 /*Alphabet length*/

void Caesar(char *str,int shift,int choose){
	int i,j,flag,temp_shift;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	for(i=0;i<strlen(str);i++){
		if(str[i] == ' ')
				printf(" ");
		else{
			for(j=0;j<ALPHA && flag != 1;j++){
				/*if choose = 0 -> encrypting*/
				if(choose == 0){
					/*if the correct match between the string to encrypt 
					  and the alphabet string is found*/ 
					if(str[i] == alphabet[j]){
						/*apply the shift given by the user, find the new letter 
						  and re-assign str[i] to the shifted letter*/
						str[i] = alphabet[(j+shift)%ALPHA];
						/*Setting flag=1 to prevent the for loop from further entering, 
						  the outer for loop will then go on the next letter of the string to encrypt */
						flag = 1;
					}
				}
				/*if choose = 1 -> decrypting*/
				else{ 
					if(str[i] == alphabet[j]){
						temp_shift = (j-shift) % ALPHA;
						if(temp_shift < 0)    
							temp_shift += ALPHA;
							/*  In C '%' it's the remainder operator 
							    (not the modulus which is required in this case)
							     so sanitizing negative cases is needed.*/
						str[i] = alphabet[temp_shift];
						flag = 1;
					}
				}
			}
			flag=0;
		}
	}
}

void crypt(int choose,char *filename){
	FILE *fp,*fout;
	int shift,i;
	char *str;
	str = malloc(N * sizeof(char));

	if((fp = fopen(filename,"r")) == NULL){
		printf("File not found\n");
		exit(EXIT_FAILURE);
	}

	/*Encrypt*/
	if(choose == 0){
		if((fout = fopen("encrypted.dat","w")) == NULL){
			printf("File not found\n");
			exit(EXIT_FAILURE);
		}
	}
	/*Decrypt*/
	else{
		if((fout = fopen("decrypted.dat","w")) == NULL){
			printf("File not found\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Input shift to apply: ");
	scanf("%d", &shift);
	
	while(fscanf(fp,"%s",str) != EOF){
		for(i = 0; i<strlen(str); i++)
			/*converts the whole string to lowercase*/
			str[i] = tolower(str[i]);
		/* choose = 0 -> encrypting
		   choose = 1 -> decrypting */
		Caesar(str,shift,choose);
		printf("%s ", str);
		fprintf(fout,"%s ",str);
	}
	printf("\n");
	fprintf(fout,"\n");

	fclose(fp);
	fclose(fout);
	return;
}

int main(int argc, char **argv){
	int choose;
	char *filename;
	filename = malloc(N * sizeof(int));

	do{
		printf("------------------------------------\n");
		printf("-----------Caesar Cipher------------\n");
		printf("------------------------------------\n");
		printf("1. Encrypt text from file.\n");
		printf("2. Decrypt text from file.\n");
		printf("3. Exit.\n");
		printf(">> ");
		scanf("%d",&choose);
		switch(choose){

			case 1:
				printf("Input filename: \n");
				scanf("%s",filename);
				crypt(0,filename);
				break;

			case 2:
				printf("Input filename: \n");
				scanf("%s",filename);
				crypt(1,filename);
				break;

			case 3:
				choose = 0;
				break;

			default:
				printf("Choose a valid option.\n");
				break;
		}
	}while(choose != 0);
	
	return 0;
}
