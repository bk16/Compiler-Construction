
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "parseTree.h"

char * ans( int i )
{
	if( i == 0 )
		return "no";
	else
		return "yes";
}

void dfs(PTNode * pTree, FILE * fp)
{
	//if( graph[v]->visited )
	//	return;

	//pTree->visited = 1;
	//cout << "visited : " << v << endl;	

	//printf("visited : %s\n",tokenNameFromSymbol( pTree->s ));

	if( pTree->t == NULL )
	{
		fprintf(fp,"------\t%s\t%s\t%s\n",tokenNameFromSymbol(pTree->parent->s),ans(pTree->ifLeafNode),tokenNameFromSymbol(pTree->s));
	}
	else
	{
			
		fprintf(fp,"%s \t %d \t %s \t %s \t %s \t %s \t %s\n",	
						pTree->t->lexeme,
						pTree->t->lineNum,
						tokenNameFromSymbol(pTree->s),
						pTree->t->lexeme,
						 tokenNameFromSymbol(pTree->parent->s),
						ans(pTree->ifLeafNode),
						tokenNameFromSymbol(pTree->s));		
	}	
	int numOfChildren = pTree->numOfChildren;

	int i = 0;

	while( i < numOfChildren )
	{
		if( !(pTree->children[i]->visited) )
		{
			dfs(pTree->children[i],fp);
			//pTree->children[i]->visited = 1;
		}
		i++;
	}
}

