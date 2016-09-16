#include "parseTree.h"

int getPTNodes( PTNode * pTree )
{
	if( pTree == NULL )
		return 0;

	int result = 1;

	int i = 0;
	while( i<pTree->numOfChildren )
	{
		result = result + getPTNodes( pTree->children[i] );
		i++;
	}
	return result;
}

int getMemory( PTNode * pTree )
{
	if( pTree == NULL )
		return 0;

	int result = sizeof( pTree ) ;

	int i = 0;
	while( i<pTree->numOfChildren )
	{
		result = result + getMemory( pTree->children[i] );
		i++;
	}
	return result;
}

PTNode * getPTNodeMemory( PTNode * pTree)
{
	pTree = (PTNode *)malloc( sizeof( PTNode ));
	return pTree;
}

PTNode * addToTree( symbol s, tokenInfo * t, listNode * list, PTNode * pTree)
{
	/*no checking for terminal/non-terminal here, check if needed to be added*/
	//printf("Symbol to add is %s\n",tokenNameFromSymbol(s));		
	if( pTree == NULL )
	{
		pTree = getPTNodeMemory( pTree );
		pTree->s = s;
		pTree->numOfChildren = 0;
		pTree->children = NULL;
		pTree->t = NULL;
		pTree->parent = &Root;
		pTree->ifLeafNode = 1;
		//pTree->children = 0;
		pTree->visited = 0;

		//printf("In 1\n");
	}
	else
	{
		int done  = 0;
		addToLMNonTerminal( s, t, list, pTree, &done );
		//printf("In 2\n");
	}

	return pTree;
}

void addToLMNonTerminal( symbol s, tokenInfo * t, listNode * list, PTNode * pTree,int * done)
{
	if( *done )
	{
		printf("Done\n");
		return ;
	}

	//printf("Symbol s is %s\n",tokenNameFromSymbol(s));	
	//printf("Ptree->s is %s\n",tokenNameFromSymbol(pTree->s));			
	if( isANonTerminal( s ))
	{

		if( pTree->children == NULL && pTree->s == s )
		{
			int numOfChildren = getSizeList( list );
			pTree->children = (PTNode **)malloc( sizeof( PTNode *) * numOfChildren);
			pTree->ifLeafNode = 0;
			pTree->numOfChildren = numOfChildren;
			pTree->visited = 0;

			int i;
			for( i=0; i<numOfChildren; i++)
				pTree->children[i] = NULL;

			listNode * head = list;
			i = 0;
			
			while( head != NULL )
			{
				pTree->children[i] = getPTNodeMemory( pTree->children[i] );
				pTree->children[i]->s = head->s;
				pTree->children[i]->numOfChildren = 0;
				pTree->children[i]->children = NULL;
				pTree->children[i]->t = NULL;
				pTree->children[i]->parent = pTree;
				pTree->children[i]->ifLeafNode = 1;
				pTree->children[i]->visited = 0;

				head = head->next;
				i++;
			}
			*done = 1;
			//printf("In 3\n");
		}
		else
		{
			int numOfChildren = pTree->numOfChildren;
			int i = 0;
			
			while( i<numOfChildren && *done == 0)
			{
				addToLMNonTerminal( s, t, list, pTree->children[i], done );		
				i++;
			}

			//printf("In 4\n");
		}
	}
	else
	{
		//printf("Ptree->s inside terminal else is %s\n",tokenNameFromSymbol(pTree->s));			
		if( pTree->t == NULL && pTree->s == s )
		{
			
			pTree->t = (tokenInfo *)malloc(sizeof( tokenInfo ));

			//printf("s : %s, t->s %s\n",tokenNameFromSymbol(s),tokenNameFromSymbol(t->s));
			if( s != t->s )
			{
				printf("token match error!!!!!!!\n");
			}
			pTree->t->lineNum = t->lineNum;
			strcpy( pTree->t->lexeme, t->lexeme);
			pTree->ifLeafNode = 1;
			*done = 1;
			//printf("In 5\n");
		}
		
		else
		{
			int numOfChildren = pTree->numOfChildren;
			int i = 0;

			while( i<numOfChildren && *done == 0)
			{
				addToLMNonTerminal( s, t, list, pTree->children[i], done );		
				i++;
			}
			//printf("In 6\n");
		}
		
	}	
}
