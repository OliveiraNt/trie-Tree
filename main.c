#include "trieTree.h"

int main(int argc, char** argv){
	
	FILE *text, *trieFile;
        
        
	if(argc != 3){
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);

		return 1;
        }
 
	text = fopen(argv[1],"r");
	if(!text){
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);

		return 1;
	}
 
	trieFile = fopen(argv[2],"w+");
	if(!trieFile){
		fclose(text);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
	
		return 1;
	}
	
	createNode(trieFile);
	getWords(text, trieFile);

	char str1[] = "incidents";
	char str2[] = "adventures";

	check(str1, trieFile);
	check(str2, trieFile);

    fclose(text);
    fclose(trieFile);

    return 0;
}
