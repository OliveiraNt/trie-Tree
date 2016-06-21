#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node Node;

struct _Node {
    int is_end;
    int next_char[26];
};


int check(char * str, FILE *trieFile){
	
	Node n;
	int i;
	int actReg = 0;
	
	fseek(trieFile, 0, SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);

	if(n.next_char[str[0] - 'a'] == 0){
		printf("Word not Found 1\n");
		return 1;
	}

	else{
		for(i = 0; i < strlen(str); i++){
			actReg = n.next_char[str[i] - 'a'];
			//printf("actReg = %d\n", actReg);//db
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			if(n.next_char[str[i + 1] - 'a'] == 0){
				printf("Word not Found 2\n");
				return 1;
			}
		}
		actReg = n.next_char[str[i] - 'a'];
		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fread(&n, sizeof(Node), 1, trieFile);
		if(n.is_end == 0){
			printf("Word not Found 3\n");
			return 1;
		}
		if(n.is_end == 1){
			printf("Word Found\n");
			return 0;
		}
	}
}


int main(int argc, char** argv){
	
	FILE *trieFile;
        
        
	if(argc != 3){
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);

		return 1;
        }
 
	trieFile = fopen(argv[1],"r");
	if(!trieFile){
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);

		return 1;
	}
	
	
	char* str1;
	str1 = argv[2];

	check(str1, trieFile);
	/*
	Node n;
	int reg = 0;

	
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['a' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['d' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['v' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['e' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['n' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['t' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['u' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['r' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['e' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	reg = n.next_char['s' - 'a'];
	printf("%d\n", reg);
	printf("%d\n", n.is_end);
	fseek(trieFile, reg*sizeof(Node), SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	printf("%d\n", n.is_end);
	*/
	
	

    
    fclose(trieFile);

    return 0;
}	
