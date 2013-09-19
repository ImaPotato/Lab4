
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int prob[26];
char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* table = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
char b[26];

void print(char* c){
	int i, j;

	for(i = 0; i < strlen(c); i++){
		for(j = 0; j < 26; j++){
			if(c[i] == alpha[j]){
				printf("%c", b[j]);
			}
		}
		if(c[i] == ' ')
			printf("%c",c[i]);
	}
	printf("\n");
}

void swap(char* a){
	int x,y,i;
	char t;
	for(i = 0; i < 26; i++){
		if(b[i] == a[0]){
			x = i;
		} 
		if(b[i] == a[1]){
			y = i;
		}
	}
	t = b[x];
	b[x] = b[y];
	b[y] = t;
}

void loopUntilComplete(char* c){
	print(c);
	printf("Enter two characters to swap (ab) or (qy) without the brackets or (end) when you're finished. \n");
	int i;
	char* a = malloc(10*sizeof(char));
	while(1 == 1){
		scanf("%s",a);
		if(strcmp(a,"end") == 0){
			break;
		}
		for(i = 0; i < 2; i++){
			a[i] = toupper(a[i]);
		}
		swap(a);
		print(c);
	}
}

int decrypt(char* c){
	int i;
	int j;
	for(i = 0; i < strlen(c); i++){
		if( (c[i] >= 'A') && (c[i] <= 'Z'))
		prob[c[i] - 65]++;
	}

	int high = -1;
	int _high = 0;


	for(i = 0; i < 26; i++){
		for(j = 0; j < 26; j++){
			if(prob[j] > high){
				high = prob[j];
				_high = j;
			}
		}
		printf("%i\n",_high);
		b[_high] = table[i];
		prob[_high] = -1;
		high = -1;
	}	

	for(i = 0; i < 26; i++){
		printf("%c",b[i]);
	}
	printf("\n");
	loopUntilComplete(c);
}


int main(int arc, char *argv[]){
	char buffer[2048];
	FILE* f = fopen(argv[1], "r");
	if(f!=NULL){
		fread(buffer, 2048, 1, f);
		decrypt(buffer);
	}
	fclose(f);
	return 0;
}