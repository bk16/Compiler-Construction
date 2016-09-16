
#include "symbolTable.h"

/*symbol table to add and search variable names*/
struct variableNamesSymbolTableBSTNode * getVariableNamesSymbolTableBSTNodeMemory( struct variableNamesSymbolTableBSTNode * node )
{
	node = (struct variableNamesSymbolTableBSTNode *)malloc( sizeof( struct variableNamesSymbolTableBSTNode ));
	//node->scope = NULL;
	node->type = -1;
	node->integerValue = INFINITY;
	node->realValue = INFINITY;
	node->variableName = NULL;
	node->offset = -1;
	node->left = NULL;
	node->right = NULL;

	return node;
}

	

struct variableNamesSymbolTableBSTNode * VN_BSTNodeInsert(struct variableNamesSymbolTableBSTNode * x, 
						char * scope,
						symbol type,
						int integerValue,
						double realValue,
						char * variableName,
						int offset, int offsetValue)	/*offset useless*/
{
	if( x == NULL )
	{	

		//printf("in BST 1\n");
		x = getVariableNamesSymbolTableBSTNodeMemory( x );
		//printf("in BST 2\n");
		strcpy(x->scope, scope);
		//printf("in BST 3\n");
		x->type = type;
		//printf("in BST 4\n");
		if( type == TK_INT )
			x->integerValue = integerValue;

		//printf("in BST 5\n");
		if( type == TK_REAL )
			x->realValue = realValue;
		//printf("in BST 6\n");
		x->offset = offsetValue;
		//printf("in BST 7\n");
	}
	else
	{
		if( strcmp(x->variableName, variableName) > 0 )
		{
			x->left = VN_BSTNodeInsert(x->left,scope,type,integerValue,realValue,variableName,offset,offsetValue);
		}
		else
		{
			x->right = VN_BSTNodeInsert(x->right,scope,type,integerValue,realValue,variableName,offset,offsetValue);
		}
	}
			//printf("in BST return \n");
	return x;
}
int VN_BSTNodeSearch(struct variableNamesSymbolTableBSTNode * root, char * variableName)
{
	if( root == NULL )
	{	
		return -1;
	}
	else
	{
		if( strcmp(root->variableName, variableName) > 0 )
		{
			return VN_BSTNodeSearch(root->left,variableName);
		}
		else if(  strcmp(root->variableName, variableName) < 0 )
		{
			return VN_BSTNodeSearch(root->right,variableName);
		}
		else
		{
			return root->type;
		}
	}
}

/*symbol table to add and search function names*/
struct functionNamesSymbolTableBSTNode * getFunctionNamesSymbolTableBSTNodeMemory( struct functionNamesSymbolTableBSTNode * node )
{
	node = (struct functionNamesSymbolTableBSTNode *)malloc( sizeof( struct functionNamesSymbolTableBSTNode ));
	node->integerInputParameters = NULL;
	node->realInputParameters = NULL;
	node->integerOutputParameters = NULL;
	node->realOutputParameters = NULL;
	node->records = NULL;
	//node->functionName = NULL;
	node->returnType = NULL;
	node->variablesInFunction = NULL;
	node->left = NULL;
	node->right = NULL;
		
	return node;
}

/*add record Info*/
struct functionNamesSymbolTableBSTNode * FN_BSTNodeInsert(struct functionNamesSymbolTableBSTNode * x, char * functionName,struct integerListNode * integerInputParameters,struct doubleListNode * realInputParameters,struct integerListNode * integerOutputParameters,struct doubleListNode * realOutputParameters,symbol * returnType, VN_BSTNode * variablesInFunction)
{
	if( x == NULL )
	{	
		//printf("In FBST 1\n");
		x = getFunctionNamesSymbolTableBSTNodeMemory( x );
		//printf("In FBST 2\n");
		strcpy(x->functionName, functionName);
		//printf("In FBST 3\n");
		x->integerInputParameters = integerInputParameters;
		x->realInputParameters = realInputParameters;
		x->integerOutputParameters = integerOutputParameters;
		x->realOutputParameters = realOutputParameters;
		x->returnType = returnType;
		x->variablesInFunction = variablesInFunction;
	}
	else
	{
		if( strcmp(x->functionName, functionName) > 0 )
		{
			x->left = FN_BSTNodeInsert(x->left,
							functionName,
							integerInputParameters,
							realInputParameters,
							integerOutputParameters,
							realOutputParameters,
							returnType,
							variablesInFunction);
		}
		else
		{
			x->right = FN_BSTNodeInsert(x->right,
							functionName,
							integerInputParameters,
							realInputParameters,
							integerOutputParameters,
							realOutputParameters,
							returnType,
							variablesInFunction);
		}
	}
	
	return x;
}
struct functionNamesSymbolTableBSTNode * FN_BSTNodeSearch(struct functionNamesSymbolTableBSTNode * root, char * functionName)
{
	if( root == NULL )
	{	
		return NULL;
	}
	else
	{
		if( strcmp(root->functionName, functionName) > 0 )
		{
			return FN_BSTNodeSearch(root->left,functionName);
		}
		else if(  strcmp(root->functionName, functionName) < 0 )
		{
			return FN_BSTNodeSearch(root->right,functionName);
		}
		else
		{
			return root;
		}
	}
}

void printFN_BSTNode( struct functionNamesSymbolTableBSTNode * functions )
{
	if( functions == NULL )
		return;

	if( functions->left != NULL )
		printFN_BSTNode( functions->left);

	printf("Function name : %s\n", functions->functionName);
	printf("Function variables :\n");
	printVN_BSTNode( functions->variablesInFunction );

	if( functions->right != NULL )
		printFN_BSTNode( functions->right);
		
}

void printVN_BSTNode( struct variableNamesSymbolTableBSTNode * variables )
{
	if( variables == NULL )
		return;

	if( variables->left != NULL )
		printVN_BSTNode( variables->left);

	printf("Variable name : %s, Type : %s, IntValue : %d, RealValue %lf, Scope : %s, Offset : %d\n",
			variables->variableName,
			tokenNameFromSymbol(variables->type),
			variables->integerValue,
			variables->realValue,
			variables->scope,	
			variables->offset);


	if( variables->right != NULL )
		printVN_BSTNode( variables->right);
}


void printSymbolTable( struct symbolTable * st)
{
	printFN_BSTNode( st->functions );
	printVN_BSTNode( st->globalVariables);
}
