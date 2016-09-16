
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

int main(int argc, char *argv[])
{

	char testCaseFileName[30];
	char parseTreeFileName[30];
	int choice = -1;

	if( argc != 3 )
	{
		printf("Wrong format of command line execution! Retry!\n");
		return 1;
	}

	strcpy(testCaseFileName, argv[1]);
	strcpy(parseTreeFileName, argv[2]);

	FILE * testCaseFile = fopen( testCaseFileName , "r");
	if( testCaseFile == NULL )
	{
		printf("Can't open test case file!\n");
		return 2;
	}
	fclose(testCaseFile);

	FILE * parseTreeFile = fopen( parseTreeFileName , "r");
	if( parseTreeFile == NULL )
	{
		printf("Can't open parse tree file!\n");
		return 3;
	}
	fclose(parseTreeFile);
	
	printf("First set automation attempted. Follow set automation to be done.\n");
	printf("Lexical analyzer module developed.\n");
	printf("Syntax analysis module developed.\n");
	printf("Modules compile. Couple of warnings.\n");
	printf("Parse tree construction to be done.\n");
	printf("Errors not being reported very correctly.\n");

	listNode*** T;
	grammarNode** G;
	parseTree PT = NULL;

		printf("Enter choice :\n");
		printf("1. Removal Of Comments\n");
		printf("2. Print token list\n");
		printf("3. Parsing\n");
		printf("4. Parse Tree creation\n");
		printf("5. Quit\n");

		scanf("%d",&choice);
		if( choice == 1 )
		{
			char * code = commentFreeCode(testCaseFileName);
			printf("%s",code);
		}
		else if( choice == 2 )
		{
			tokenInfo t;
			testCaseFile = fopen( testCaseFileName , "r");
			while( t.s != TK_END )
			{
				t = getNextToken( testCaseFile );	
				printf("{Lexeme : %s | Line : %d | TokenID : %s}\n",t.lexeme,t.lineNum,tokenNameFromSymbol(t.s));
			}
			fclose(testCaseFile);
		}
		else if( choice == 3 )
		{
			T = NULL;
			G = NULL;
			createParseTable( &G, &T );
			PT = parseInputSourceCode( testCaseFileName, T );
		}
		else if( choice == 4 )
		{
			printParseTree( PT , parseTreeFileName);
		}
		else
		{
			printf("Wrong choice entered!\n");
		}
		
	return 0;
}	
