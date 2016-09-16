#include <stdio.h>
#include <stdlib.h>

#include "lexerDef.h"

struct stackNode
{
	symbol s;
	struct stackNode * next;
};

struct stackNode * createStack( struct stackNode * head )
{
	head = NULL;
	return head;
}

struct stackNode * push( struct stackNode * head, symbol newSymbol)
{
	if( head == NULL )
	{
		head = (struct stackNode*)malloc(sizeof(struct stackNode));
		head->s = newSymbol;
		head->next = NULL;
	}
	else
	{
		struct stackNode * temp = (struct stackNode *)malloc(sizeof(struct stackNode));
		temp->s = newSymbol;
		temp->next = head;
		head = temp;
	}
	return head;
}

struct stackNode * pop(struct stackNode * head, symbol * stackTop)
{
	/*check if this condition arises*/
	if( head == NULL )
		return NULL;

	*stackTop = head->s;		

	head = head->next;
	return head;
}

int empty(struct stackNode * head)
{
	return head == NULL;
}

void print(struct stackNode * head)
{
	struct stackNode * temp = head;
	while( temp )
	{
		printf("%d  \n",temp->s);
		temp = temp->next;
	}
}

int main()
{
	struct stackNode * head = createStack( head );
	head = push( head, TK_NUM );
	head = push( head, TK_INT );
	head = push( head, TK_RNUM );

	print( head );

	symbol st;
	head = pop( head , &st );


	//printf("%d \n",st); 
	print( head );

	head = pop( head , &st );
	print( head );

	head = pop( head , &st );

	if( empty( head ) )
		printf("Empty\n");
	return 0;
}

	
