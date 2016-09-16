
#ifndef AST_H_
#define AST_H_

#include "parseTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "parseTree.h"

void AST( PTNode * pTree);
void process1( PTNode * pTree);
void process2( PTNode * pTree);
int InList(symbol s);
PTListNode * addToASTNode(PTListNode * list, PTNode * node);
int getSizeOfPTList( PTListNode *);

#endif
