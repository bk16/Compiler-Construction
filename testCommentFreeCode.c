#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

int main()
{
	char * code = commentFreeCode("input.txt");
	
	printf("%s",code);

	return 0;
}	
