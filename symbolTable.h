
#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "parseTree.h"

#define INFINITY 1000000000
/*node for the BST, which is our simple Symbol Table*/

typedef struct doubleListNode
{
	double realValue;
	struct doubleListNode * next;
} DLNode;

typedef struct integerListNode
{
	int integerValue;
	struct integerListNode * next;
} ILNode;

typedef struct variableNamesSymbolTableBSTNode
{
	char scope[50];
	symbol type;
	int integerValue;
	double realValue;
	char * variableName;
	int offset;
	
	/*a linked list for TK-RECORD type definitions*/
	struct variableNamesSymbolTableBSTNode * left;
	struct variableNamesSymbolTableBSTNode * right;

}VN_BSTNode;

typedef struct recordInfoNode
{
	char * recordName;
	char * scope;
	struct variableNamesSymbolTableBSTNode * variables;
	struct recordInfoNode * next;
} RINode;

typedef struct functionNamesSymbolTableBSTNode
{
	struct integerListNode * integerInputParameters;
	struct doubleListNode * realInputParameters;
	struct integerListNode * integerOutputParameters;
	struct doubleListNode * realOutputParameters;
	struct recordInfoNode * records;
	char functionName[50];
	symbol * returnType;
	struct variableNamesSymbolTableBSTNode * variablesInFunction;

	struct functionNamesSymbolTableBSTNode * left;
	struct functionNamesSymbolTableBSTNode * right;

}FN_BSTNode;

typedef struct symbolTable
{
	VN_BSTNode * globalVariables;
	FN_BSTNode * functions;

}SymbolTable;

struct variableNamesSymbolTableBSTNode * getVariableNamesSymbolTableBSTNodeMemory( struct variableNamesSymbolTableBSTNode * node );
struct variableNamesSymbolTableBSTNode * VN_BSTNodeInsert(struct variableNamesSymbolTableBSTNode * x, 
						char * scope,
						symbol type,
						int integerValue,
						double realValue,
						char * variableName,
						int offset, int offsetValue);
int VN_BSTNodeSearch(struct variableNamesSymbolTableBSTNode * root, char * variableName);


struct functionNamesSymbolTableBSTNode * getFunctionNamesSymbolTableBSTNodeMemory( struct functionNamesSymbolTableBSTNode * node );
struct functionNamesSymbolTableBSTNode * FN_BSTNodeInsert(struct functionNamesSymbolTableBSTNode * x, 
						char * functionName,
						struct integerListNode * integerInputParameters,
						struct doubleListNode * realInputParameters,
						struct integerListNode * integerOutputParameters,
						struct doubleListNode * realOutputParameters,
						symbol * returnType, VN_BSTNode * variablesInFunction);
struct functionNamesSymbolTableBSTNode * FN_BSTNodeSearch(struct functionNamesSymbolTableBSTNode * root, char * functionName);

void printSymbolTable( struct symbolTable * );
void printFN_BSTNode( struct functionNamesSymbolTableBSTNode * functions );
void printVN_BSTNode( struct variableNamesSymbolTableBSTNode * variables );

#endif









