#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"


/*traversal of the parse tree node*/
void inorderTraversal(parseTreeNode * PTNode, symbol lookup, parseTreeNode ** node)
{
	if( PTNode == NULL )
		return;

	if( PTNode->s == lookup )
	{
		*node = PTNode;
		//printf("At %s, returning node\n",tokenNameFromSymbol(PTNode->s));
		return;
	}

	/*check if core can be dumped*/
	int numberOfChildren = PTNode->numChildren;

	//printf("numberOfChildren %d\n",numberOfChildren);
	
	//printf("At %s, num children : %d\n",tokenNameFromSymbol(PTNode->s),PTNode->numChildren);
	int i;
	for( i=0; i<numberOfChildren; i++)
	{
		inorderTraversal( PTNode->children[i], lookup, node );
	}
	return;
}

/*to add children to a node in a parseTree node*/
parseTreeNode * addChildrenToNode(listNode * list, symbol stackTop, parseTreeNode * PT )
{
	parseTreeNode * nodeToAddChildren;
	inorderTraversal( PT, stackTop , &nodeToAddChildren);

	int numberOfChildren = getSizeList( list );

	//printf("numberOfChildren %d\n",numberOfChildren);
	
	nodeToAddChildren->children = ( parseTreeNode ** )malloc( sizeof( parseTreeNode *) * numberOfChildren);
	nodeToAddChildren->numChildren = numberOfChildren;

	listNode * head = list;
	int i =0;
	while( head )
	{
		nodeToAddChildren->children[i] = ( parseTreeNode * )malloc( sizeof( parseTreeNode ));
		nodeToAddChildren->children[i]->s = head->s;
		nodeToAddChildren->children[i]->children = NULL;
		nodeToAddChildren->children[i]->numChildren = 0;
	
		head = head->next;
		i++;
	}
	return PT;
}

int main()
{
	parseTree PT = NULL;
	PT = (parseTreeNode * )malloc( sizeof(parseTreeNode));
	PT->s = program;
	PT->numChildren = 0;
	PT->children = NULL;

	listNode * list = NULL;
	list = addSymbolToList( list, mainfunction);
	list = addSymbolToList( list, otherfunctions);

	PT = addChildrenToNode( list, program, PT);

	//printf("%ld\n", sizeof(PT->children) / sizeof(PT->children[0]));

	printf("%s\n",tokenNameFromSymbol(PT->children[0]->s));
	printf("%s\n",tokenNameFromSymbol(PT->children[1]->s));
	//printf("%s\n",tokenNameFromSymbol(PT->children[2]->s));
	//printListNode(list);

	list = NULL;
	list = addSymbolToList( list, TK_ID);
	list = addSymbolToList( list, TK_RNUM);

	PT = addChildrenToNode( list, otherfunctions, PT);

	list = NULL;
	list = addSymbolToList( list, TK_INT);
	list = addSymbolToList( list, TK_NUM);

	PT = addChildrenToNode( list, TK_ID, PT);

	//printf("%s\n",tokenNameFromSymbol(PT->children[1]->children[0]->s));
	//printf("%s\n",tokenNameFromSymbol(PT->children[1]->children[1]->s));

	
	
}
