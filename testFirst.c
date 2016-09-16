#include <stdio.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"


int main()
{
	listNode*** T = NULL;
	grammarNode** G = NULL;
	createParseTable( &G, &T );

	if( G == NULL )
		printf("Grammar not created");
	parseTree PT = parseInputSourceCode( "input.txt", T );

	int tableRows = NUMBER_OF_NONTERMINALS,i,j;
	int tableColumns = NUMBER_OF_TERMINALS + 1;
	int entries = 0;

	for( i=0; i<tableRows ; i++)
	{
		for( j=0; j<tableColumns ; j++)
		{
			if( T[i][j] == NULL )
				continue;
			entries++;
 			//printf("T[%d][%d] : ",i,j);        			
			//printListNode( T[i][j] );
		}
 	}

	listNode ** First;
	listNode ** Follow;

	/*populating first and follow sets*/
	First = populateFirst( First );
	Follow = populateFollow( Follow );

	if( First == NULL )
		printf("First is NULL\n");


	for(  i=0; i<NUMBER_OF_NONTERMINALS ; i++)
	{
		int numberOfRules = G[i]->numberOfRules;
		//printf("Number of rules : %d\n", numberOfRules);

		for( j=0; j<numberOfRules ; j++)
		{
			printf("Printing first set for the alpha : ");
			printListNode( G[i]->list[j] );
			listNode * first = getFirstOfAlpha( G[i]->list[j] , First, Follow );
			printf("First set is : ");
			printListNode( first );
			printf("\n");	
		}
	}

	/*for(  i=0; i<NUMBER_OF_NONTERMINALS + NUMBER_OF_TERMINALS ; i++)
	{
		printf("First of %s is : ",tokenNameFromSymbol(i));
		printListNode( First[i] );
	}*/

	
	printf("Entries : %d", entries );
}
