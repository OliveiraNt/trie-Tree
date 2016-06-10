#ifndef __TRIE_TREE__
#define __TRIE_TREE__


#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node Node;

struct _Node {
    int is_end;
    int next_char[26];
};


int createNode(FILE *trieFile);
int insertWord(char str[], FILE *trieFile);
void getWords(FILE *textFile, FILE *trieFile);
int check(char str[],FILE *out);

#endif
