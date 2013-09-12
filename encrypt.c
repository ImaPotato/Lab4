#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeSpaces (char *str);
void removeCharacters(char* alpha, char* pass, char* build, char* alp);
void decrypt(char* encryptedText, char* pass);

/*
takes some text and a password, it then removes any spaces or duplicate characters from the password and then creates a key by
removing the characters already in the key from alpha and then placeing alpha on the end of the new password string
then each character in the text is compared to this new key and has it character chosen and printed.
*/
void encrypt(char *text, char* pass) {
	char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* build = malloc(27 * sizeof(char));
	char* alp = malloc(26 * sizeof(char));

	removeCharacters(alpha, pass, build, alp);

	int i;
	char c;
	char encryptedText[strlen(text) + 1];
	i = 0;

	while (i < strlen(text)) {
    	c = toupper(text[i]);
    	if ( (c >= 'A') && (c <= 'Z')) {
    		int pos = c - 65;
    		encryptedText[i] = build[pos];
    	} else {
      		encryptedText[i] = c;
    	}
    	i++;
	}

	encryptedText[i] = ' ';
	printf("%s\n", encryptedText);
		decrypt(encryptedText, pass);
}
/*
takes an encrypted string and a password and matches each character from the encrypted string against a key
and then finds the correct character in the alphabet to print
*/
void decrypt(char* encryptedText, char* pass){

	char* text = malloc(50 * sizeof(int));
	char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char* build = malloc(27 * sizeof(char));
	char* alp = malloc(26 * sizeof(char));

	removeCharacters(alpha, pass, build, alp);

	int i;
	int j;
	int z = 0;
	char c;

	for(i = 0; i < strlen(encryptedText); i++){
		c = encryptedText[i];
				if ( (c >= 'A') && (c <= 'Z')) {
		for(j = 0; j < strlen(build); j++){
			if(build[j] == encryptedText[i]){
				text[z] = alpha[j];
				z++;
				break;
			}
		}
	} else {
		text[z] = c;
		z++;
		}
	}
	text[z] = ' ';
	printf("%s\n",text);
}
/*
removes the characters from the alphabet that are already contained in the password, 
the remaining characters of the alphabet are then concatenated onto the end of the password 
*/
void removeCharacters(char* alpha, char* pass, char* build, char* alp){
	int j;
	int y;
	int z = 1;

	build[0] = pass[0];

	int boolean = 1;
	for(y = 1; y < strlen(pass); y++){
		for(j = 0; j < strlen(build); j++){
			if(build[j] == pass[y]){
				boolean = 2;
				break;
			}
			if(pass[y] == ' '){
				boolean = 2;
				break;
			}
		}
		if(boolean == 1){
			build[z] = pass[y];
			z++;
		}
		boolean = 1;
	}

	build[z] = ' ';
	removeSpaces(build);
	z = 0;
	boolean = 1;

	for(j = 0; j < strlen(alpha); j++){
		for(y = 0; y < strlen(build); y++){
			if((build[y] = toupper(build[y])) == alpha[j]){
				boolean = 2;
				break;
			}
		}
		if(boolean == 1){
			alp[z] = alpha[j];
			z++;
		}
		boolean = 1;
	}
	alp[z] = ' ';
	strcat(build, alp);

}
/*
for a string removes any ' ', needed this for when the password contained more then one word e.g "hello sir"
*/
void removeSpaces (char *str) {
    char *src = str;
    char *dst = src;
    while (*src != '\0') {
        if (*src != ' ')
            *dst++ = *src;
        src++;
    }
    *dst = '\0';
}
/*
reads in the first 1000 characters of the text document and calls encrypt with the buffer and password from the command line
*/
int main(int argc, char *argv[]) {
	char buffer[1000];
	FILE* f = fopen(argv[1], "r");
	if(f != NULL){
		fread(buffer, 1000, 1, f);
		encrypt(buffer, argv[2]); 
	}
	fclose(f);
  
  return 0;
}