#include "parseTree.h"

PTNode * getPTNodeMemory( PTNode * pTree)
{
	pTree = (PTNode *)malloc( sizeof( PTNode ));
	return pTree;
}

PTNode * addToTree( symbol s, tokenInfo * t, listNode * list, PTNode * pTree)
{
	/*no checking for terminal/non-terminal here, check if needed to be added*/
	printf("Symbol to add is %s\n",tokenNameFromSymbol(s));		
	if( pTree == NULL )
	{
		pTree = getPTNodeMemory( pTree );
		pTree->s = s;
		pTree->numOfChildren = 0;
		pTree->children = NULL;
		pTree->t = NULL;
		pTree->parent = &Root;
		pTree->ifLeafNode = 1;

		printf("In 1\n");
	}
	else
	{
		int done  = 0;
		pTree = addToLMNonTerminal( s, t, list, pTree, &done );
		printf("In 2\n");
	}


	return pTree;
}

PTNode * addToLMNonTerminal( symbol s, tokenInfo * t, listNode * list, PTNode * pTree,int * done)
{
	if( *done )
	{
		printf("Done\n");
		return pTree;
	}

	//printf("Symbol s is %s\n",tokenNameFromSymbol(s));	
	printf("Ptree->s is %s\n",tokenNameFromSymbol(pTree->s));			
	if( isANonTerminal( s ))
	{

		if( pTree->children == NULL && pTree->s == s )
		{
			int numOfChildren = getSizeList( list );
			pTree->children = (PTNode **)malloc( sizeof( PTNode *) * numOfChildren);
			pTree->ifLeafNode = 0;
			pTree->numOfChildren = numOfChildren;

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

				head = head->next;
				i++;
			}
			*done = 1;
			printf("In 3\n");
		}
		else
		{
			int numOfChildren = pTree->numOfChildren;
			int i = 0;
			
			while( i<numOfChildren && *done == 0)
			{
				pTree = addToLMNonTerminal( s, t, list, pTree->children[i], done );		
				i++;
			}

			printf("In 4\n");
		}
	}
	else
	{
		if( pTree->children == NULL )
		{
			if( pTree->t == NULL )
			{
				pTree->t = (tokenInfo *)malloc(sizeof( tokenInfo ));

				if( s != t->s )
				{
					printf("token match error\n");
				}
				pTree->t->lineNum = t->lineNum;
				strcpy( pTree->t->lexeme, t->lexeme);
				*done = 1;
			printf("In 5\n");
			}
			else
			{
				/*PTNode * temp;
				temp = pTree->parent;
				pTree = addToLMNonTerminal( s, t, list, temp, done);	*/
				printf("In 6\n");
				
			}
		}
		else
		{                        
			int numOfChildren = pTree->numOfChildren;
			int i = 0;
			while( i<numOfChildren && *done == 0)
			{
				pTree = addToLMNonTerminal( s, t, list, pTree->children[i],done );		
				i++;
			}
			printf("In 8\n");
		}

	}
	return pTree;
}
