#include "lexerDef.h"
#include <stdio.h>

#ifndef LEXER_H_
#define LEXER_H_


/*API's to be implemented, as per the assignement*/
FILE * getStream(FILE * fp, buffer B, buffersize k);
tokenInfo  getNextToken( FILE *fp);

/* auxillary funcitons*/
int isWhiteSpace( char c );
int checkForLexeme( char temp[45], struct BSTNode * STRoot );
int minimum(int a,int b);
int checkForIdentifiersAndNumbers( char temp[45] );
int DFA(char temp[45]);
symbol getSymbolForLexeme( char lexeme[45], struct BSTNode * STRoot );
void copyNCharacters( char temp[45], char * B, int n);
char * getLexemeFromSymbol( symbol s );
char * tokenNameFromSymbol( symbol s );
void resizeArray(char * temp);
char * commentFreeCode( char * testfile );

/*Functions for the BST implementation*/
struct BSTNode * insert(struct BSTNode * x, char * value, symbol s);
int search(struct BSTNode * root, char * value);
void inorder(struct BSTNode * root );
struct BSTNode * min(struct BSTNode * x); 
struct BSTNode * deleteMin(struct BSTNode * x); 
struct BSTNode * del(struct BSTNode * x, char * key); 	
int height(struct BSTNode* node);
void printGivenLevel(struct BSTNode* root, int level);
void printLevelOrder(struct BSTNode* root);
struct BSTNode * populateSymbolTable(struct BSTNode * root);

#endif
