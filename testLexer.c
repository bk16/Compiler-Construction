
#include <stdio.h>
#include "lexer.h"

int main()
{
	FILE * fp = fopen("input.txt","r");

	tokenInfo t;

	/*printf("%s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);

	t = getNextToken( fp );

	printf("%s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);

	t = getNextToken( fp );

	printf("%s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);

	t = getNextToken( fp );

	printf("%s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);

	t = getNextToken( fp );

	printf("%s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);*/

	
	int i;
	while( fp )
	{
		t = getNextToken( fp );

		printf("Lexeme Information ------- %s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);
	}
	
	return 0;
}
