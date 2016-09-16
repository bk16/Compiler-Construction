
#ifndef PARSER_H_
#define PARSER_H_

#include "parserDef.h"
#include "parseTree.h"

grammarNode ** populateGrammar(grammarNode ** G);
void createParseTable(grammar GG, table T);
struct ListNode * getListNodeMemory();
listNode * getEpsilonNode(listNode * epsilonNode);
listNode *  addSymbolToList( listNode * node, symbol s);
listNode ** populateFirst( listNode ** First );
listNode ** populateFollow( listNode ** Follow );
listNode *  getFirstOfAlpha( listNode * node, listNode ** First , listNode ** Follow  );
int isATerminal(symbol s);
int isANonTerminal(symbol s);
int containsEpsilon( listNode * node );
struct stackNode * addToStack( struct stackNode * stack, listNode * list );
int getSizeList( listNode * list );
tokenInfoNode * addTokenToList( tokenInfoNode * tokens, tokenInfo t);
int getSizeOfTokenList( tokenInfoNode * tokens );
void printListNode(listNode * head);
void printParseTree(parseTree PT, char *outfile);

/*functions for the stack*/
struct stackNode * createStack( struct stackNode * head );
struct stackNode * push( struct stackNode * head, symbol newSymbol);
struct stackNode * pop(struct stackNode * head, symbol * stackTop);
int empty(struct stackNode * head);
void print(struct stackNode * head);

#endif
