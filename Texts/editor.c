#include <stdio.h>
#include <ctype.h>
 
int main(int argc, char** argv)
{
    FILE *entrada, *saida;
    int c;
 
    if(argc != 3)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }
 
    entrada = fopen(argv[1],"r");
    if(!entrada)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }
 
    saida = fopen(argv[2],"w");
    if(!saida)
    {
        fclose(entrada);
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
        return 1;
    }
 
    c = fgetc(entrada);
    while(c != EOF)
    {
        if(isalpha(c)){
			c=tolower(c);
			fputc(c, saida);
        }
		if(c=='\n')
			fputc(c, saida);
		if(c==' ')
			fputc(c, saida);
		if(c=='\t')
			fputc(c, saida);
		
        c = getc(entrada);
    }
 
    fclose(entrada);
    fclose(saida);
    return 0;
}
