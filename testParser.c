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

	printParseTree( PT, "parseTree.txt");
	int tableRows = NUMBER_OF_NONTERMINALS,i,j;
	int tableColumns = TK_WRITE + 1;
	int entries = 0;

	for( i=0; i<tableRows ; i++)
	{
		for( j=0; j<tableColumns ; j++)
		{
			if( T[i][j] == NULL )
				continue;
			entries++;
 			//printf("T[%s][%s] : ",tokenNameFromSymbol(i),tokenNameFromSymbol(j));        			
			//printListNode( T[i][j] );
		}
 	}

	//if( T[termprime][TK_CL] == NULL )
		//printf("T4c4 IS NULL\n");
	//printf("Entries : %d\n", entries );
	//printf("%d\n",var);	
	//printf("TK_DOLLAR -> %d\n",TK_DOLLAR); 
}
