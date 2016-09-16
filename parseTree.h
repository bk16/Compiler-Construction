
#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexerDef.h"
#include "parserDef.h"
#include "lexer.h"

typedef struct ptNode 
{
	symbol s;
	int numOfChildren;
	struct ptNode ** children;
	struct ptNode * parent;
	tokenInfo * t;
	int ifLeafNode;
	int visited;
}PTNode;

typedef struct ptListNode 
{
	symbol s;
	int numOfChildren;
	struct ptNode ** children;
	struct ptNode * parent;
	tokenInfo * t;
	int ifLeafNode;
	int visited;
	struct ptListNode * next;
}PTListNode;

PTNode Root;
	
typedef PTNode * parseTree;

PTNode * addToTree( symbol s, tokenInfo * t, listNode * list, PTNode * pTree);
void addToLMNonTerminal( symbol s, tokenInfo * t, listNode * list, PTNode * pTree,int *done);
PTNode * getPTNodeMemory( PTNode * pTree );
int getPTNodes( PTNode * pTree );
int getMemory( PTNode * pTree );
#endif

