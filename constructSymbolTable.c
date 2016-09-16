
#include "symbolTable.h"
#include "constructSymbolTable.h"

struct symbolTable * constructSymbolTable( PTNode * pTree )
{
	char * scope;
	int offset = 0;
	strcpy( scope, "global");

	//printf("scope : %s\n",scope);
	struct symbolTable st;
	st.globalVariables = NULL;
	st.functions = NULL;
	ConstructSymbolTable( pTree, scope, &st , &offset);
	return &st;
}

void ConstructSymbolTable( PTNode * pTree, char * scope, struct symbolTable * st, int * offset )
{
	printf("Symbol is : %s\n", tokenNameFromSymbol(pTree->s));
	if( pTree == NULL )
		return;

	if( pTree->s == function )
	{
		printf("I am here 1\n");
		/*search for the function name*/
		char * functionName;
		struct integerListNode * integerInputParameters = NULL;
		struct doubleListNode * realInputParameters= NULL;
		struct integerListNode * integerOutputParameters = NULL;
		struct doubleListNode * realOutputParameters = NULL;
		struct variableNamesSymbolTableBSTNode * variablesInFunction = NULL;
		symbol * returnType = NULL;

		int numOfChildren = pTree->numOfChildren;
		int i = 0;
		while( i<numOfChildren )
		{
			if( pTree->children[i]->s == TK_FUNID )
			{
				strcpy( scope, pTree->children[i]->t->lexeme );
				strcpy( functionName, pTree->children[i]->t->lexeme );
				break;
			}
			i++;
		}

		printf("I am here 2\n");
		i = 0;
		while( i<numOfChildren )
		{
			if( pTree->children[i]->s == input_par )
			{
				getInputParInfo( pTree->children[i], variablesInFunction, integerInputParameters,realInputParameters, scope, offset);
				break;
			}
			i++;
		}

		printf("I am here 3\n");
		/*getting list of input parameters*/
		i = 0;
		while( i<numOfChildren )
		{
			if( pTree->children[i]->s == output_par )
			{
				getOutputParInfo( pTree->children[i],variablesInFunction,integerOutputParameters,realOutputParameters,scope, offset);
				break;
			}
			i++;
		}
		printf("I am here 4\n");
		/*getting list of output parameters*/
		i = 0;
		while( i<numOfChildren )
		{
			if( pTree->children[i]->s == stmts )
			{
				//getStatementsInfo( pTree->children[i], variablesInFunction, scope, offset);
				break;
			}
			i++;
		}
		printf("I am here 5\n");
		/*add function node to symbol table and return the symbol table*/
		st->functions = FN_BSTNodeInsert( st->functions,functionName,
								integerInputParameters,
								realInputParameters,
								integerOutputParameters,
								realOutputParameters,
								returnType, 
								variablesInFunction);
		printf("I am here 7	\n");
		return;
		/*no in-depth search after processing the function node*/	
	}

	int numOfChildren = pTree->numOfChildren;
	int i = 0;

	/*printf("Children of %s are :\n",tokenNameFromSymbol( pTree->s ));	
	while( i<numOfChildren )	
	{
		printf("child[i] : %s\n", tokenNameFromSymbol(pTree->children[i]->s));
		i++;
	}
	i = 0;	*/
	while( i<numOfChildren )	
	{		
		printf("I am here 6\n");
		
		ConstructSymbolTable( pTree->children[i], scope, st , offset);
		printf("I am here 8\n");
		i++;
	}

}

void getInputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerInputParameters, 
			struct doubleListNode * realInputParameters, char * scope, int * offset)
{
	int done = 0;
	symbol type = -1;
	symbol identifier = -1;
	char * value;

	_getInputParInfo( pTree, variablesInFunction, integerInputParameters, realInputParameters, scope, offset, &type, &identifier, value);
}

void _getInputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerInputParameters, 
			struct doubleListNode * realInputParameters, char * scope, int * offset, symbol * type, symbol * identifier,char *value)
{
	if( pTree == NULL )
		return;

	//printf("Ptree->s : %s\n",tokenNameFromSymbol(pTree->s));
	//printf("Type : %d, identifier : %d\n", *type, *identifier );
	//printf("1\n");
	if( pTree->s == TK_INT ||  pTree->s == TK_REAL )
	{
		//printf("inside if\n");
		*type = pTree->s;
		//printf(" type in if : %s\n",tokenNameFromSymbol(*type));
	}
	//printf("2\n");
	if(  pTree->s == TK_ID )
	{
		*identifier = TK_ID;
		strcpy( value, pTree->t->lexeme);	/*value stores identifier*/
	}
	//printf("3\n");
	//printf("Type : %d, identifier : %d\n", *type, *identifier );
	if( *type != -1 && *identifier != -1 )
	{
		//printf("5\n");
		/*variable data collected*/
		//char * variableName;
		/*if t == NULL, error*/

		//if( !pTree->t->lexeme )
		//	printf("error");
		//strcpy( variableName, pTree->t->lexeme);
	
		/*if( value == NULL )
		{		
			printf("variableName is NULL\n");
		}
		else
			printf("variableName : %s\n",value);
		printf("7\n");
		if value == NULL, error*/
		if( *type == TK_INT )
		{
			int integerValue = atoi( value );
			//printf("8\n");
			integerInputParameters = addIntToList( integerInputParameters, integerValue );

			variablesInFunction = VN_BSTNodeInsert( variablesInFunction, scope, *type, integerValue, INFINITY, value,
						-1, *offset);
			//printf("9\n");
			*offset = *offset + 2;
		}
		else
		{
			double realValue = atof( value );
			realInputParameters = addDoubleToList( realInputParameters, realValue );

			variablesInFunction = VN_BSTNodeInsert( variablesInFunction, scope, *type, INFINITY, realValue, value,
						-1, *offset);
			*offset = *offset + 4;
		}
		
		//printf("10\n");
		*type = -1;
		*identifier = -1;
		value = NULL;
	}
	
	int i  = 0;
	while( i<pTree->numOfChildren )
	{
		_getInputParInfo( pTree->children[i], variablesInFunction, integerInputParameters, realInputParameters, scope, offset, 					  type,identifier, value);
		i++;
	}
}	
	
void getOutputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerOutputParameters, 
			struct doubleListNode * realOutputParameters, char * scope, int * offset)
{
	symbol type = -1;
	symbol identifier = -1;
	char * value;

	_getOutputParInfo( pTree, variablesInFunction, integerOutputParameters, realOutputParameters, scope, offset, &type, &identifier,value);
}

void _getOutputParInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, struct integerListNode * integerOutputParameters, 
			struct doubleListNode * realOutputParameters, char * scope, int * offset, symbol * type, symbol * identifier, char *value)
{
	if( pTree == NULL )
		return;

	//printf("Ptree->s : %s\n",tokenNameFromSymbol(pTree->s));
	//printf("Output Type : %d, identifier : %d\n", *type, *identifier );
	//printf("1\n");
	if( pTree->s == TK_INT ||  pTree->s == TK_REAL )
	{
		//printf("inside if\n");
		*type = pTree->s;
		//printf(" type in if : %s\n",tokenNameFromSymbol(*type));
	}
	//printf("2\n");
	if(  pTree->s == TK_ID )
	{
		*identifier = TK_ID;
		strcpy( value, pTree->t->lexeme);	/*value stores identifier*/
	}
	//printf("Output 3\n");
	//printf("Output Type : %d, identifier : %d\n", *type, *identifier );
	if( *type != -1 && *identifier != -1 )
	{
		/*variable data collected*/
		//char * variableName;
		/*if t == NULL, error*/
		//strcpy( variableName, pTree->t->lexeme);
		/*if value == NULL, error*/
		if( *type == TK_INT )
		{
			int integerValue = atoi( value );
			integerOutputParameters = addIntToList( integerOutputParameters, integerValue );

			variablesInFunction = VN_BSTNodeInsert( variablesInFunction, scope, *type, integerValue, INFINITY, value,
						-1, *offset);
			*offset = *offset + 2;
		}
		else
		{
			double realValue = atof( value );
			realOutputParameters = addDoubleToList( realOutputParameters, realValue );

			variablesInFunction = VN_BSTNodeInsert( variablesInFunction, scope, *type, INFINITY, realValue, value,
						-1, *offset);
			*offset = *offset + 4;
		}
		
		*type = -1;
		*identifier = -1;
		value = NULL;
	}
	
	int i  = 0;
	if( pTree->numOfChildren == 0 )
		return;

	while( i<pTree->numOfChildren )
	{
		_getOutputParInfo( pTree->children[i], variablesInFunction, integerOutputParameters, realOutputParameters, scope, offset, 					  type,identifier,value);
		i++;
	}
}	
			
struct integerListNode * addIntToList( struct integerListNode * list , int integerValue )
{ 
	if( list == NULL )
	{
		list = (struct integerListNode *)malloc( sizeof( struct integerListNode ));
		list->integerValue = integerValue;
		list->next = NULL;
		return list;
	}
	else
	{
		struct integerListNode * head = list;
		while( head->next != NULL )
		{
			head = head->next;
		}
		struct integerListNode * newnode =  (struct integerListNode *)malloc( sizeof( struct integerListNode ));		
		newnode->integerValue = integerValue;
		newnode->next = NULL;	
		head->next = newnode;
		return list;
		
	}
}

struct doubleListNode * addDoubleToList( struct doubleListNode * list , double realValue )
{ 
	if( list == NULL )
	{
		list = (struct doubleListNode *)malloc( sizeof( struct doubleListNode ));
		list->realValue = realValue;
		list->next = NULL;
		return list;
	}
	else
	{
		struct doubleListNode * head = list;
		while( head->next != NULL )
		{
			head = head->next;
		}
		struct doubleListNode * newnode =  (struct doubleListNode *)malloc( sizeof( struct doubleListNode ));		
		newnode->realValue = realValue;
		newnode->next = NULL;	
		head->next = newnode;
		return list;
		
	}
}

void getStatementsInfo( PTNode * pTree, VN_BSTNode * variablesInFunction, char * scope, int offset)
{
	
}
