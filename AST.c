
#include "ast.h"

void AST( PTNode * pTree)
{
	process1( pTree );
	process2( pTree );
}

int getSizeOfPTList( PTListNode * list)
{
	PTListNode * head = list;
	if( head == NULL )
	{
		return 0;
	}
	else
	{
		return 1 + getSizeOfPTList( head->next );
	}
}

PTListNode * addToASTNode(PTListNode * list, PTNode * node)
{
	PTListNode * head = list;
	if( head == NULL )
	{
		head = (PTListNode *)malloc( sizeof( PTListNode ));
		head->s = node->s;
		head->numOfChildren = node->numOfChildren;
		head->children = node->children;
		head->t = node->t;
		head->parent = node->parent;
		head->ifLeafNode = node->ifLeafNode;
		head->visited = node->visited;
		head->next = NULL;
		return head;
	}
	else
	{
		while( head->next != NULL )
		{
			head = head->next;
		}
		PTListNode * newNode = (PTListNode *)malloc( sizeof( PTListNode ));
		newNode->s = node->s;
		newNode->numOfChildren = node->numOfChildren;
		newNode->children = node->children;
		newNode->t = node->t;
		newNode->parent = node->parent;
		newNode->ifLeafNode = node->ifLeafNode;
		newNode->visited = node->visited;
		newNode->next = NULL;
		head->next = newNode;
		return list;
	}
}

void process2( PTNode * pTree )
{
	//printf("pTree->s : %s\n",tokenNameFromSymbol( pTree->s ));
	if( pTree->numOfChildren == 0 )
	{
		pTree = NULL;
	}
	else
	{
		int numOfChildren = pTree->numOfChildren;
		int i = 0;

		//printf("I am here 1\n");
		while( i<numOfChildren )
		{
			if( isANonTerminal( pTree->children[i]->s ) )
			{
				process2( pTree->children[i] );
			}
			i++;
		}
		
		i = 0;
		PTListNode * newChildren = NULL;
		int newNumOfChildren = 0;

		//printf("I am here 2\n");
		while( i<numOfChildren )
		{
			if( pTree->children[i] != NULL )
			{
				newChildren = addToASTNode( newChildren, pTree->children[i] );
				newNumOfChildren++;
			}
			i++;
		}

		PTNode ** tempChildren = NULL;
		if( newNumOfChildren > 0 )
			tempChildren = (PTNode **)malloc( sizeof( PTNode *) * newNumOfChildren);

		i = 0;

		PTListNode * head = newChildren;

		//printf("I am here 3\n");
		while( i<newNumOfChildren && head != NULL)
		{
			tempChildren[i] = (PTNode *)malloc( sizeof( PTNode ));
			tempChildren[i]->s = head->s;
			tempChildren[i]->numOfChildren = head->numOfChildren;
			tempChildren[i]->children = head->children;
			tempChildren[i]->t = head->t;
			tempChildren[i]->parent = head->parent;
			tempChildren[i]->ifLeafNode = head->ifLeafNode;
			tempChildren[i]->visited = head->visited;
	
			head = head->next;
			i++;
		}

		pTree->numOfChildren = newNumOfChildren;
		pTree->children = tempChildren;

		//printf("I am here 4\n");
		if( newNumOfChildren == 1 )
		{
			if( isATerminal(pTree->children[0]->s) )
			{
				pTree->s = pTree->children[0]->s;
				pTree->numOfChildren = 0;
				pTree->t = pTree->children[0]->t;
				pTree->children = NULL;
				pTree->ifLeafNode = 1;
				pTree->visited = 0;
			}
			else
			{
				/*same with non terminal as well?*/
			}
		} 

	}
}		

void process1( PTNode * pTree )
{
	PTListNode * newChildren = NULL;
	int i = 0;
	int numOfChildren = pTree->numOfChildren;

	while( i<numOfChildren )
	{
		if( isATerminal( pTree->children[i]->s ) && !InList( pTree->children[i]->s ) )
		{
			newChildren = addToASTNode( newChildren, pTree->children[i] );
		}
		i++;
	}

	i = 0;
	while( i<numOfChildren )
	{
		if( isANonTerminal( pTree->children[i]->s ) )
		{
			process1( pTree->children[i] );
			newChildren = addToASTNode( newChildren, pTree->children[i] );
		}
		i++;
	}

	int sizeOfList = getSizeOfPTList( newChildren );

	PTNode ** tempChildren = (PTNode **)malloc( sizeof( PTNode *) * sizeOfList);
	i = 0;
		
	PTListNode * head = newChildren;

	while( i<sizeOfList && head != NULL)
	{
		tempChildren[i] = (PTNode *)malloc( sizeof( PTNode ));
		tempChildren[i]->s = head->s;
		tempChildren[i]->numOfChildren = head->numOfChildren;
		tempChildren[i]->children = head->children;
		tempChildren[i]->t = head->t;
		tempChildren[i]->parent = head->parent;
		tempChildren[i]->ifLeafNode = head->ifLeafNode;
		tempChildren[i]->visited = head->visited;
	
		head = head->next;
		i++;
	}

	pTree->numOfChildren = sizeOfList;
	pTree->children = tempChildren;
	 
}

int InList( symbol s )
{
	if( s == TK_MAIN ||
	    s == TK_END || 
	    s == TK_SEM ||
	    s == TK_INPUT ||
	    s == TK_PARAMETER ||
	    s == TK_LIST ||
	    s == TK_SQL ||
	    s == TK_SQR ||
	    s == TK_OUTPUT ||
	    s == TK_COMMA ||
	    s == TK_COLON ||
	    s == TK_DOT ||
	    s == TK_CALL ||
	    s == TK_WITH ||
	    s == TK_PARAMETERS ||
	    s == TK_WHILE ||
	    s == TK_ENDWHILE ||
	    s == TK_IF ||
	    s == TK_ENDIF ||
	    s == TK_OP ||
	    s == TK_CL ||
	    s == TK_TYPE ||
	    s == TK_EPS )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

