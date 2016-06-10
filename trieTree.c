#include "trieTree.h"

//write a new node into file
int createNode(FILE *trieFile){
	Node n;
	int reg;
	memset(&n, 0, sizeof(Node));
	fseek(trieFile, 0, SEEK_END);
	fwrite(&n, sizeof(Node), 1, trieFile);
	fseek(trieFile, 0, SEEK_END);
	reg = (int)((ftell(trieFile)/sizeof(Node))-1);
	//printf("reg = %d\n", reg);//db
	return reg;
}


//to insert the string in the trie tree
int insertWord(char str[], FILE *trieFile){
	
	int k;

	for(k = 0; k < strlen(str); k++){
		if(str[k] == ' ' || str[k] == '\n' || str[k] == '\t'){
			printf("k=%d\n", k);

			return 0;
		}
	}

	Node n;
	int i = 0;
	int j = 0;
	int newReg;
	int actReg = 0;
	
	
	fseek(trieFile, 0, SEEK_SET);
	fread(&n, sizeof(Node), 1, trieFile);

	//printf("child: %d\n", n.next_char[str[0] - 'a']);//db
	if(n.next_char[str[0] - 'a'] == 0){
		printf("entrou no 1\n");//db
		for(i = 0; i< strlen(str); i++){
			printf("%c\n", str[i]);//db
			newReg = createNode(trieFile);
			//printf("newReg = %d\n", newReg);//db
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			n.next_char[str[i] - 'a'] = newReg;
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fwrite(&n, sizeof(Node), 1, trieFile);
			//printf("next = %d\n", n.next_char[str[i] - 'a']);//db
			actReg = newReg;
			//printf("actReg = %d\n", actReg);//db
			
		}

		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fread(&n, sizeof(Node), 1, trieFile);
		n.is_end = 1;
		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fwrite(&n, sizeof(Node), 1, trieFile);
		printf("nova palavra\n");//db
		
		/*   //db
		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fread(&n, sizeof(Node), 1, trieFile);
		printf("is_end = %d\n", n.is_end);
		*/
	
		return 1;
	}
	
	else{
		printf("entrou no 2\n");//db
		while(n.next_char[str[j] - 'a'] != 0){
			if(n.is_end == 1){
				printf("palavra ja inserida\n");//db
				return 0;
			}
			actReg = n.next_char[str[j] - 'a'];
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			j++;
		}
		for(i = j; i<strlen(str); i++){
			printf("%c\n", str[i]);//db
			newReg = createNode(trieFile);
			//printf("newReg = %d\n", newReg);//db
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fread(&n, sizeof(Node), 1, trieFile);
			n.next_char[str[i] - 'a'] = newReg;
			fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
			fwrite(&n, sizeof(Node), 1, trieFile);
			//printf("next = %d\n", n.next_char[str[i] - 'a']);//db
			actReg = newReg;
			//printf("actReg = %d\n", actReg);//db
			
		}

		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fread(&n, sizeof(Node), 1, trieFile);
		n.is_end = 1;
		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fwrite(&n, sizeof(Node), 1, trieFile);
		printf("nova palavra\n");//db

		/*   //db
		fseek(trieFile, actReg*sizeof(Node), SEEK_SET);
		fread(&n, sizeof(Node), 1, trieFile);
		printf("is_end = %d\n", n.is_end);
		*/
	
		return 1;
	}
}

//get words from file
void getWords(FILE *textFile, FILE *trieFile){
	int c;
	int i = 0;
	char str[99];
	c = fgetc(textFile);
	while(c != EOF){
		if(isalpha(c)){
			str[i] = c;
			i++;
			c = fgetc(textFile);
		}
		else{
			insertWord(str, trieFile);
			//printf("%s", str);//db
			//printf("...\n");//db
			memset(str, 0, 99);
			i = 0;
			c = fgetc(textFile);
		}
	}
	
}



// to check if the string is in trie tree
int check(char str[], FILE *trieFile){
	Node n;
	memset(&n, 0, sizeof(Node));
	int i;
	int actReg;

    fseek(trieFile, 0, SEEK_SET);
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
				return 1;
			}
			else {
				printf("Word Not Found\n");
				return 0;
			}
		}
	}
	printf("Word Not Found\n");

	return 0;
	
}
