#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node Node;

struct _Node {
    int is_end;
    int next_char[26];
};


int check(char str[], FILE *trieFile){
	Node n;

	int i;
	int actReg;

	fseek(trieFile, 0, SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);

	while(n.next_char[str[i] - 'a'] != 0){
			if(n.is_end == 1 && i == (strlen(str)-1)){
				printf("palavra ja inserida\n");//db
				return 1;
			}
			actReg = n.next_char[str[i] - 'a'];
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			i++;
	}
	
	printf("Word Not Found\n");

	return 1;

    /*fseek(trieFile, 0, SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);
	for(i = 0; i<strlen(str); i++){
		if(n.next_char[str[i] - 'a'] != 0){
			actReg = n.next_char[str[i] - 'a'];
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			
		}
		else{
			if(n.is_end == 1){
				printf("Word Found\n");
				return 0;
			}
			else {
				printf("Word Not Found\n");
				return 1;
			}
		}
	}
	printf("Word Not Found\n");

	return 1;*/
	
}


int main(int argc, char** argv){
	
	FILE *text, *trieFile;
        
        
	if(argc != 2){
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);

		return 1;
        }
 
	trieFile = fopen(argv[1],"r");
	if(!text){
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);

		return 1;
	}
	
	
	char str1[] = "incidents";
	char str2[] = "adventures";

	check(str1, trieFile);
	check(str2, trieFile);

    
    fclose(trieFile);

    return 0;
}	
