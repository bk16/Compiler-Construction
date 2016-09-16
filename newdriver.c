
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "parseTree.h"
#include "constructSymbolTable.h"

int main(int argc, char *argv[])
{

	char testCaseFileName[30];
	char finalcodefilename[30];
	int choice = -1;

	if( argc != 3 )
	{
		printf("Wrong format of command line execution! Retry!\n");
		return 1;
	}

	strcpy(testCaseFileName, argv[1]);
	strcpy(finalcodefilename, argv[2]);

	FILE * testCaseFile = fopen( testCaseFileName , "r");
	if( testCaseFile == NULL )
	{
		printf("Can't open test case file!\n");
		return 2;
	}
	fclose(testCaseFile);

	FILE * parseTreeFile = fopen( finalcodefilename , "r");
	if( parseTreeFile == NULL )
	{
		printf("Can't open final code file!\n");
		return 3;
	}
	fclose(parseTreeFile);
	
	listNode*** T;
	grammarNode** G;
	parseTree PT = NULL;

		printf("Enter choice :\n");
		printf("1. Print token list\n");
		printf("2. Parsing and Parse Tree creation\n");
		printf("3. Print Abstract syntax Tree\n");
		printf("4. Memory Allocation\n");
		printf("5. Print Symbol Table\n");
		printf("6. Compile front end\n");
		printf("7. Generate final ASM code\n");
		printf("8. Quit\n");

		scanf("%d",&choice);
		if( choice == 1 )
		{
			tokenInfo t;
			testCaseFile = fopen( testCaseFileName , "r");
			while( !feof(testCaseFile) )
			{
				t = getNextToken( testCaseFile );	
				printf("{Lexeme : %s | Line : %d | TokenID : %s}\n",t.lexeme,t.lineNum,tokenNameFromSymbol(t.s));
			}
			fclose(testCaseFile);
		}
		else if( choice == 2 )
		{
			T = NULL;
			G = NULL;
			createParseTable( &G, &T );
			PT = parseInputSourceCode( testCaseFileName, T );
			dfs( PT , stdout);
		}
		else if( choice == 3 )
		{
			T = NULL;
			G = NULL;
			createParseTable( &G, &T );
			PT = parseInputSourceCode( testCaseFileName, T );
			AST( PT );
			dfs( PT , stdout);
		}
		else if( choice == 4 )
		{
			T = NULL;
			G = NULL;
			createParseTable( &G, &T );
			PT = parseInputSourceCode( testCaseFileName, T );
			int PTNodes = getPTNodes( PT );
			int PTSize  = getMemory( PT );
			AST( PT );
			int ASTNodes = getPTNodes( PT );
			int ASTSize = getMemory( PT );
			
			printf("Parse tree    Number of nodes = %d    Allocated Memory =  %d Bytes\n",PTNodes,PTSize);
			printf("AST           Number of nodes = %d    Allocated Memory =  %d Bytes\n",ASTNodes,ASTSize);

			double compressionPercentage = ((double)(PTSize - ASTSize)/(double)(PTSize)) * 100.0;
			printf("Compression Precentage : %lf%\n", compressionPercentage);
		}         
		else if( choice == 5 )
		{
			T = NULL;
			G = NULL;
			createParseTable( &G, &T );
			PT = parseInputSourceCode( testCaseFileName, T );
			//AST( PT );
			struct symbolTable * st = constructSymbolTable( PT );
			printSymbolTable( st );
		}
		else if( choice == 6 )
		{
			printf("Not done!");
		}
		else if( choice == 7 )
		{
			printf("Not done!\n");
		}
		else if( choice == 8 )
		{
			return 1;
		}
		else
		{	
			printf("Wrong choice entered!\n");
		}
	return 0;
}	
