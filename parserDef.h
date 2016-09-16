
#ifndef PARSERDEF_H_
#define PARSERDEF_H_

#include "lexerDef.h"

#define NUMBER_OF_GRAMMAR_RULES 88	/*not needed I guess*/
#define NUMBER_OF_NONTERMINALS (var+1)	/*since more_ids is the last non-terminal in the enum list*/
#define NUMBER_OF_TERMINALS (TK_WRITE - var)	/*since TK_ERROR is the last token, and more_ids is the last listed non-terminal*/

/*node that contains the symbols of a production rule*/
typedef struct ListNode
{
	symbol s;
	struct ListNode * next;
} listNode;

/*array of linked lists, that store the given grammar. A kind of adjacency list*/
typedef struct GrammarNode
{
	symbol nonTerminal;
	int numberOfRules;
	/*array of next nodes, since a non terminal can have multiple production rules*/
	struct ListNode ** list;
} grammarNode;

/*table is a 2D array of pointers to the production rules, with rows as non-terminals and column as terminals*/
/*so, this should be listNode instead?*/
typedef listNode**** table;

/*grammar is an array on nodes, that store the production rules*/
typedef grammarNode*** grammar;

/*node for the stack for predictive parsing*/
struct stackNode
{
	symbol s;
	struct stackNode * next;
};


#endif
