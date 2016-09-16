
#ifndef CONSTRUCTSYMBOLTABLE_H_
#define CONSTRUCTSYMBOLTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "symbolTable.h"


struct symbolTable * constructSymbolTable( PTNode * pTree );
void ConstructSymbolTable( PTNode * pTree, char * scope, struct symbolTable * st, int * offset );
void getInputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerInputParameters, 
			struct doubleListNode * realInputParameters, char * scope, int * offset);
void _getInputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerInputParameters, 
			struct doubleListNode * realInputParameters, char * scope, int * offset, symbol * type, symbol * identifier,char *value);
void getOutputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerOutputParameters, 
			struct doubleListNode * realOutputParameters, char * scope, int * offset);
void _getOutputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerOutputParameters, 
			struct doubleListNode * realOutputParameters, char * scope, int * offset, symbol * type, symbol * identifier,char *value);
struct integerListNode * addIntToList( struct integerListNode * list , int integerValue );
struct doubleListNode * addDoubleToList( struct doubleListNode * list , double realValue );

#endif
