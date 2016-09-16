#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

int main()
{
	listNode * list = NULL;

	list = addSymbolToList( list, TK_DOLLAR );
	list = addSymbolToList( list, TK_INT );
	list = addSymbolToList( list, TK_NUM );
	list = addSymbolToList( list, TK_RNUM );

	//printListNode( list );

	while( list )
	{
		printf("%d ",list->s);
		list = list->next;
	}
	return 0;
}	
