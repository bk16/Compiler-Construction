#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

grammarNode ** giveMem( grammarNode ** G1 )
{
	G1 = ( grammarNode** )malloc( sizeof(grammarNode*) );
	return G1;
}

void check1( grammar G )
{
	grammarNode** G1;
	G1 = giveMem( G1 );
	if( G1 == NULL )
		printf("G1 is NULL\n");
	*G = G1;
}

int main()
{
	grammarNode ** G1 = NULL;
	
	check1( &G1 );

	if( G1 == NULL )
		printf("G1 is NULL\n");

	return 0;
}	
