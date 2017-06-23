#include "caesar.h"

static char *alphabet = "abcdefghijklmnopqrstuvwxyz";

void Decrypt(char *text,int shift){

	int i,x;
	
	for(i=0;i<strlen(text);i++){
		if(isspace(text[i]) != 0 || ispunct(text[i]) != 0 || text[i] == '\n'){
			/*when a space, punctuation character or new line is encountered skip*/
		}
		else{
			text[i] = tolower(text[i]);
			x = (text[i] - 'a' - shift) % ALPHA;
			if (x < 0)
				x += ALPHA;
			text[i] = alphabet[x];
		}
	}
}

void Encrypt(char *text,int shift){

	int i,x;

	for(i=0;i<strlen(text);i++){
		if(isspace(text[i]) != 0 || ispunct(text[i]) != 0 || text[i] == '\n'){
			/*when a space, punctuation character or new line is encountered skip*/
		}
		else{
			text[i] = tolower(text[i]);
			x = (text[i] - 'a' + shift) % ALPHA;
			if (x < 0)
				x += ALPHA;
			text[i] = alphabet[x];
		}
	}
}

void BruteForce(char *str) {
	int i;
	char *text = strdup(str);

	printf("Original - %s\n", text);
	for (i=0;i<ALPHA;i++) {
        Decrypt(text,i+1); /*Shifts it by one every time*/
        printf("----\nshift = %d\n%s\n", i+1,text);
        text = strdup(str);
    }
    free(text);
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
	printf("Usage: caesar <shift> [-e | -d]  [-i] <input_file> [-o] <output_file>\n");
	printf("Usage without known shift: caesar [-b]  [-i] <input_file> [-o] <output_file>\n");
	return;
}

int main(int argc, char **argv){
	char *text;

	if (argc != 7 && argc != 6 ){
			Usage();
			exit(0);
		}
	else if(strcmp(argv[3],"-i") == 0 && strcmp(argv[5],"-o") == 0){

		text = OpenFromFile(argv[4]);
		printf("%s\n", text);
		/*encrypt*/
		if (strcmp(argv[2],"-e") == 0){
			Encrypt(text,atoi(argv[1]));

		}
		/*decrypt*/
		else if (strcmp(argv[2],"-d") == 0){
			Decrypt(text,atoi(argv[1]));
		}
		else{
			Usage();
			exit(0);
		}

		WriteToFile(text,argv[6]);
	}
	
	else if(strcmp(argv[2],"-i") == 0 && strcmp(argv[4],"-o") == 0){

		text = OpenFromFile(argv[3]);

		/*bruteforce*/
		if(strcmp(argv[1],"-b") == 0){
			BruteForce(text);
		}
		else{
			Usage();
			exit(0);
		}

		WriteToFile(text,argv[5]);
	}
	else{
		Usage();
		exit(0);
	}

	return 0;
}
