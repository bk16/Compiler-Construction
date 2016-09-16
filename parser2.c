
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"

struct ListNode * getListNodeMemory()
{
	struct ListNode * newNode = malloc(sizeof( listNode ));
	return newNode;
}

grammarNode ** populateGrammar(grammarNode ** G)
{
	//printf("I am here 2\n");
	G = ( grammarNode **) malloc(sizeof( grammarNode * ) * NUMBER_OF_NONTERMINALS );

	/*to maintain array order, the enum will have to be properly defined*/
	/*also, 0 index start for non-terminals, and then later constants for terminals, since terminals are just constants*/

	/*program > otherfunctions mainfunction .checked*/
	G[program] = malloc(sizeof(grammarNode));
	G[program]->numberOfRules = 1;
	G[program]->list = malloc(sizeof( listNode * ) * 1 );	/* x1, since 1 production rule for program non-terminal*/
 	G[program]->list[0] = getListNodeMemory(); 	
	G[program]->list[0]->s = otherfunctions;
 	G[program]->list[0]->next = getListNodeMemory();
	G[program]->list[0]->next->s = mainfunction;
 	G[program]->list[0]->next->next = NULL;
	
	/*mainfunction > TK_MAIN stmts TK_END .checked*/

	G[mainfunction] = malloc(sizeof(grammarNode));
	G[mainfunction]->numberOfRules = 1;
	G[mainfunction]->list = malloc(sizeof( listNode * ) * 1 );	/* x1, since 1 production rule for program non-terminal*/
 	G[mainfunction]->list[0] = getListNodeMemory(); 	 	
	G[mainfunction]->list[0]->s = TK_MAIN;
 	G[mainfunction]->list[0]->next = getListNodeMemory();
	G[mainfunction]->list[0]->next->s = stmts;
 	G[mainfunction]->list[0]->next->next = getListNodeMemory();
 	G[mainfunction]->list[0]->next->next->s = TK_END;
 	G[mainfunction]->list[0]->next->next->next = NULL;


	/*otherfunctions > function otherfunctions .
	  otherfunctions > eps . checked*/
	G[otherfunctions] = malloc(sizeof(grammarNode));
	G[otherfunctions]->numberOfRules = 2;
	G[otherfunctions]->list = malloc(sizeof( listNode * ) * 2 );	/* x1, since 1 production rule for program non-terminal*/
 	G[otherfunctions]->list[0] = getListNodeMemory(); 	 	
	G[otherfunctions]->list[0]->s = function;
 	G[otherfunctions]->list[0]->next = getListNodeMemory();
	G[otherfunctions]->list[0]->next->s = otherfunctions;
 	G[otherfunctions]->list[0]->next->next = NULL;
 	G[otherfunctions]->list[1] = getListNodeMemory(); 	 	
	G[otherfunctions]->list[1]->s = TK_EPS;
 	G[otherfunctions]->list[1]->next = NULL;

	/*function > TK_FUNID input_par output_par TK_SEM stmts TK_END .checked*/

	G[function] = malloc(sizeof(grammarNode));
	G[function]->numberOfRules = 1;
	G[function]->list = malloc(sizeof( listNode * ) * 1 );	/* x1, since 1 production rule for program non-terminal*/
 	G[function]->list[0] = getListNodeMemory(); 	 	
	G[function]->list[0]->s = TK_FUNID;
 	G[function]->list[0]->next = getListNodeMemory();
	G[function]->list[0]->next->s = input_par;
 	G[function]->list[0]->next->next = getListNodeMemory();
 	G[function]->list[0]->next->next->s = output_par;
 	G[function]->list[0]->next->next->next = getListNodeMemory();
 	G[function]->list[0]->next->next->next->s = TK_SEM;
 	G[function]->list[0]->next->next->next->next = getListNodeMemory();
 	G[function]->list[0]->next->next->next->next->s = stmts;
 	G[function]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[function]->list[0]->next->next->next->next->next->s = TK_END;
 	G[function]->list[0]->next->next->next->next->next->next = NULL;

	/*input_par > TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR .checked*/

	G[input_par] = malloc(sizeof(grammarNode));
	G[input_par]->numberOfRules = 1;
	G[input_par]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[input_par]->list[0] = getListNodeMemory(); 	 	
	G[input_par]->list[0]->s = TK_INPUT;
 	G[input_par]->list[0]->next = getListNodeMemory();
	G[input_par]->list[0]->next->s = TK_PARAMETER;
 	G[input_par]->list[0]->next->next = getListNodeMemory();
 	G[input_par]->list[0]->next->next->s = TK_LIST ;
 	G[input_par]->list[0]->next->next->next = getListNodeMemory();
 	G[input_par]->list[0]->next->next->next->s = TK_SQL;
 	G[input_par]->list[0]->next->next->next->next = getListNodeMemory();
 	G[input_par]->list[0]->next->next->next->next->s = parameter_list;
 	G[input_par]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[input_par]->list[0]->next->next->next->next->next->s = TK_SQR;
 	G[input_par]->list[0]->next->next->next->next->next->next = NULL;

	/*output_par > TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR . checked
	  output_par > eps .checked*/

	G[output_par] = malloc(sizeof(grammarNode));
	G[output_par]->numberOfRules = 2;
	G[output_par]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[output_par]->list[0] = getListNodeMemory(); 	 	
	G[output_par]->list[0]->s = TK_OUTPUT;
 	G[output_par]->list[0]->next = getListNodeMemory();
	G[output_par]->list[0]->next->s = TK_PARAMETER;
 	G[output_par]->list[0]->next->next = getListNodeMemory();
 	G[output_par]->list[0]->next->next->s = TK_LIST ;
 	G[output_par]->list[0]->next->next->next = getListNodeMemory();
 	G[output_par]->list[0]->next->next->next->s = TK_SQL;
 	G[output_par]->list[0]->next->next->next->next = getListNodeMemory();
 	G[output_par]->list[0]->next->next->next->next->s = parameter_list;
 	G[output_par]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[output_par]->list[0]->next->next->next->next->next->s = TK_SQR;
 	G[output_par]->list[0]->next->next->next->next->next->next = NULL;
	G[output_par]->list[1] = getListNodeMemory(); 	 	
	G[output_par]->list[1]->s = TK_EPS;
 	G[output_par]->list[1]->next = NULL;
	
	/*parameter_list > datatype TK_ID remaining_list .checked*/
	
	G[parameter_list] = malloc(sizeof(grammarNode));
	G[parameter_list]->numberOfRules = 1;
	G[parameter_list]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[parameter_list]->list[0] = getListNodeMemory(); 	 	
	G[parameter_list]->list[0]->s = datatype;
 	G[parameter_list]->list[0]->next = getListNodeMemory();
	G[parameter_list]->list[0]->next->s = TK_ID;
 	G[parameter_list]->list[0]->next->next = getListNodeMemory();
 	G[parameter_list]->list[0]->next->next->s = remaining_list ;
 	G[parameter_list]->list[0]->next->next->next = NULL;

	/*datatype > primitivedatatype .checked
	  datatype > constructeddatatype .checked*/

	G[datatype] = malloc(sizeof(grammarNode));
	G[datatype]->numberOfRules = 2;
	G[datatype]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[datatype]->list[0] = getListNodeMemory(); 	 	
	G[datatype]->list[0]->s = primitivedatatype;
 	G[datatype]->list[0]->next = NULL;
	G[datatype]->list[1] = getListNodeMemory(); 	 	
	G[datatype]->list[1]->s = constructeddatatype;
 	G[datatype]->list[1]->next = NULL;

	/*primitivedatatype > TK_INT .checked
	  primitivedatatype > TK_REAL .checked*/

	G[primitivedatatype] = malloc(sizeof(grammarNode));
	G[primitivedatatype]->numberOfRules = 2;
	G[primitivedatatype]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[primitivedatatype]->list[0] = getListNodeMemory(); 	 	
	G[primitivedatatype]->list[0]->s = TK_INT ;
 	G[primitivedatatype]->list[0]->next = NULL;
	G[primitivedatatype]->list[1] = getListNodeMemory(); 	 	
	G[primitivedatatype]->list[1]->s = TK_REAL;
 	G[primitivedatatype]->list[1]->next = NULL;

	/*constructeddatatype > TK_RECORD TK_RECORDID .checked*/

	G[constructeddatatype] = malloc(sizeof(grammarNode));
	G[constructeddatatype]->numberOfRules = 1;
	G[constructeddatatype]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[constructeddatatype]->list[0] = getListNodeMemory(); 	 	
	G[constructeddatatype]->list[0]->s = TK_RECORD;
 	G[constructeddatatype]->list[0]->next = getListNodeMemory();
	G[constructeddatatype]->list[0]->next->s = TK_RECORDID;
 	G[constructeddatatype]->list[0]->next->next = NULL;

	/*remaining_list > TK_COMMA parameter_list .checked
	  remaining_list > eps .checked*/

	G[remaining_list] = malloc(sizeof(grammarNode));
	G[remaining_list]->numberOfRules = 2;
	G[remaining_list]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[remaining_list]->list[0] = getListNodeMemory(); 	 	
	G[remaining_list]->list[0]->s = TK_COMMA;
 	G[remaining_list]->list[0]->next = getListNodeMemory();
	G[remaining_list]->list[0]->next->s = parameter_list;
 	G[remaining_list]->list[0]->next->next = NULL;
	G[remaining_list]->list[1] = getListNodeMemory(); 	 	
	G[remaining_list]->list[1]->s = TK_EPS;
 	G[remaining_list]->list[1]->next = NULL;

	/*stmts > typedefinitions declarations otherstmts returnstmt .checked*/

	G[stmts] = malloc(sizeof(grammarNode));
	G[stmts]->numberOfRules = 1;
	G[stmts]->list = malloc(sizeof( listNode * ) *1 );	
 	G[stmts]->list[0] = getListNodeMemory(); 	 	
	G[stmts]->list[0]->s = typedefinitions;
 	G[stmts]->list[0]->next = getListNodeMemory();
	G[stmts]->list[0]->next->s = declarations;
 	G[stmts]->list[0]->next->next = getListNodeMemory();
 	G[stmts]->list[0]->next->next->s = otherstmts ;
 	G[stmts]->list[0]->next->next->next = getListNodeMemory();
 	G[stmts]->list[0]->next->next->next->s = returnstmt;
 	G[stmts]->list[0]->next->next->next->next = NULL;
	
	/*typedefinitions > typedefinition typedefinitions .checked
	  typedefinitions > eps .checked*/

	G[typedefinitions] = malloc(sizeof(grammarNode));
	G[typedefinitions]->numberOfRules = 2;
	G[typedefinitions]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[typedefinitions]->list[0] = getListNodeMemory(); 	 	
	G[typedefinitions]->list[0]->s = typedefinition;
 	G[typedefinitions]->list[0]->next = getListNodeMemory();
	G[typedefinitions]->list[0]->next->s = typedefinitions;
 	G[typedefinitions]->list[0]->next->next = NULL;
	G[typedefinitions]->list[1] = getListNodeMemory(); 	 	
	G[typedefinitions]->list[1]->s = TK_EPS;
 	G[typedefinitions]->list[1]->next = NULL;
	
	/*typedefinition > TK_RECORD TK_RECORDID fielddefinitions TK_ENDRECORD TK_SEM .checked*/

	G[typedefinition] = malloc(sizeof(grammarNode));
	G[typedefinition]->numberOfRules = 1;
	G[typedefinition]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[typedefinition]->list[0] = getListNodeMemory(); 	 	
	G[typedefinition]->list[0]->s = TK_RECORD;
 	G[typedefinition]->list[0]->next = getListNodeMemory();
	G[typedefinition]->list[0]->next->s = TK_RECORDID;
 	G[typedefinition]->list[0]->next->next = getListNodeMemory();
 	G[typedefinition]->list[0]->next->next->s = fielddefinitions ;
 	G[typedefinition]->list[0]->next->next->next = getListNodeMemory();
 	G[typedefinition]->list[0]->next->next->next->s = TK_ENDRECORD;
 	G[typedefinition]->list[0]->next->next->next->next = getListNodeMemory();
	G[typedefinition]->list[0]->next->next->next->next->s = TK_SEM;
	G[typedefinition]->list[0]->next->next->next->next->next = NULL;

	/*fielddefinitions > fielddefinition fielddefinition morefields checked.*/

	G[fielddefinitions] = malloc(sizeof(grammarNode));
	G[fielddefinitions]->numberOfRules = 1;
	G[fielddefinitions]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[fielddefinitions]->list[0] = getListNodeMemory(); 	 	
	G[fielddefinitions]->list[0]->s = fielddefinition;
 	G[fielddefinitions]->list[0]->next = getListNodeMemory();
	G[fielddefinitions]->list[0]->next->s = fielddefinition;
 	G[fielddefinitions]->list[0]->next->next = getListNodeMemory();
 	G[fielddefinitions]->list[0]->next->next->s = morefields ;
 	G[fielddefinitions]->list[0]->next->next->next = NULL;

	/*fielddefinition > TK_TYPE primitivedatatype TK_COLON TK_FIELDID TK_SEM .checked*/

	G[fielddefinition] = malloc(sizeof(grammarNode));
	G[fielddefinition]->numberOfRules = 1;
	G[fielddefinition]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[fielddefinition]->list[0] = getListNodeMemory(); 	 	
	G[fielddefinition]->list[0]->s = TK_TYPE;
 	G[fielddefinition]->list[0]->next = getListNodeMemory();
	G[fielddefinition]->list[0]->next->s = primitivedatatype;
 	G[fielddefinition]->list[0]->next->next = getListNodeMemory();
 	G[fielddefinition]->list[0]->next->next->s = TK_COLON ;
 	G[fielddefinition]->list[0]->next->next->next = getListNodeMemory();
 	G[fielddefinition]->list[0]->next->next->next->s = TK_FIELDID;
 	G[fielddefinition]->list[0]->next->next->next->next = getListNodeMemory();
	G[fielddefinition]->list[0]->next->next->next->next->s = TK_SEM;
	G[fielddefinition]->list[0]->next->next->next->next->next = NULL;

	/*morefields > fielddefinition morefields .checked
	  morefields > eps .checked*/

	G[morefields] = malloc(sizeof(grammarNode));
	G[morefields]->numberOfRules = 2;
	G[morefields]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[morefields]->list[0] = getListNodeMemory(); 	 	
	G[morefields]->list[0]->s = fielddefinition;
 	G[morefields]->list[0]->next = getListNodeMemory();
	G[morefields]->list[0]->next->s = morefields;
 	G[morefields]->list[0]->next->next = NULL;
	G[morefields]->list[1] = getListNodeMemory(); 	 	
	G[morefields]->list[1]->s = TK_EPS;
 	G[morefields]->list[1]->next = NULL;

	/*declarations > declaration declarations .checked
 	  declarations > eps .checked*/
	
	G[declarations] = malloc(sizeof(grammarNode));
	G[declarations]->numberOfRules = 2;
	G[declarations]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[declarations]->list[0] = getListNodeMemory(); 	 	
	G[declarations]->list[0]->s = declaration;
 	G[declarations]->list[0]->next = getListNodeMemory();
	G[declarations]->list[0]->next->s = declarations;
 	G[declarations]->list[0]->next->next = NULL;
	G[declarations]->list[1] = getListNodeMemory(); 	 	
	G[declarations]->list[1]->s = TK_EPS;
 	G[declarations]->list[1]->next = NULL;

	/*declaration > TK_TYPE datatype TK_COLON TK_ID global_or_not TK_SEM .checked*/

	G[declaration] = malloc(sizeof(grammarNode));
	G[declaration]->numberOfRules = 1;
	G[declaration]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[declaration]->list[0] = getListNodeMemory(); 	 	
	G[declaration]->list[0]->s = TK_TYPE;
 	G[declaration]->list[0]->next = getListNodeMemory();
	G[declaration]->list[0]->next->s = datatype;
 	G[declaration]->list[0]->next->next = getListNodeMemory();
 	G[declaration]->list[0]->next->next->s = TK_COLON ;
 	G[declaration]->list[0]->next->next->next = getListNodeMemory();
 	G[declaration]->list[0]->next->next->next->s = TK_ID;
 	G[declaration]->list[0]->next->next->next->next = getListNodeMemory();
 	G[declaration]->list[0]->next->next->next->next->s = global_or_not ;
 	G[declaration]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[declaration]->list[0]->next->next->next->next->next->s = TK_SEM;
 	G[declaration]->list[0]->next->next->next->next->next->next = NULL;	
	
	/*global_or_not > TK_COLON TK_GLOBAL .checked
	  global_or_not > eps .checked*/

	G[global_or_not] = malloc(sizeof(grammarNode));
	G[global_or_not]->numberOfRules = 2;
	G[global_or_not]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[global_or_not]->list[0] = getListNodeMemory(); 	 	
	G[global_or_not]->list[0]->s = TK_COLON;
 	G[global_or_not]->list[0]->next = getListNodeMemory();
	G[global_or_not]->list[0]->next->s = TK_GLOBAL;
 	G[global_or_not]->list[0]->next->next = NULL;
	G[global_or_not]->list[1] = getListNodeMemory(); 	 	
	G[global_or_not]->list[1]->s = TK_EPS;
 	G[global_or_not]->list[1]->next = NULL;

	/*otherstmts > stmt otherstmts .checked
	otherstmts > eps .checked*/

	G[otherstmts] = malloc(sizeof(grammarNode));
	G[otherstmts]->numberOfRules = 2;
	G[otherstmts]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[otherstmts]->list[0] = getListNodeMemory(); 	 	
	G[otherstmts]->list[0]->s = stmt;
 	G[otherstmts]->list[0]->next = getListNodeMemory();
	G[otherstmts]->list[0]->next->s = otherstmts;
 	G[otherstmts]->list[0]->next->next = NULL;
	G[otherstmts]->list[1] = getListNodeMemory(); 	 	
	G[otherstmts]->list[1]->s = TK_EPS;
 	G[otherstmts]->list[1]->next = NULL;

	/*stmt > assignmentstmt .checked
	  stmt > iterativestmt .checked
	  stmt > conditionalstmt .checked
	  stmt > iostmt .checked
	  stmt > funcallstmt .checked*/
	
	G[stmt] = malloc(sizeof(grammarNode));
	G[stmt]->numberOfRules = 5;
	G[stmt]->list = malloc(sizeof( listNode * ) * 5 );	
 	G[stmt]->list[0] = getListNodeMemory(); 	 	
	G[stmt]->list[0]->s = assignmentstmt;
 	G[stmt]->list[0]->next = NULL;
	G[stmt]->list[1] = getListNodeMemory(); 	 	
	G[stmt]->list[1]->s = iterativestmt;
 	G[stmt]->list[1]->next = NULL;
	G[stmt]->list[2] = getListNodeMemory(); 	 	
	G[stmt]->list[2]->s = conditionalstmt;
 	G[stmt]->list[2]->next = NULL;
	G[stmt]->list[3] = getListNodeMemory(); 	 	
	G[stmt]->list[3]->s = iostmt;
 	G[stmt]->list[3]->next = NULL;
	G[stmt]->list[4] = getListNodeMemory(); 	 	
	G[stmt]->list[4]->s = funcallstmt;
 	G[stmt]->list[4]->next = NULL;

	/*assignmentstmt > singleorrecid TK_ASSIGNOP arithmeticexpression TK_SEM . checked*/

	G[assignmentstmt] = malloc(sizeof(grammarNode));
	G[assignmentstmt]->numberOfRules = 1;
	G[assignmentstmt]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[assignmentstmt]->list[0] = getListNodeMemory(); 	 	
	G[assignmentstmt]->list[0]->s = singleorrecid;
 	G[assignmentstmt]->list[0]->next = getListNodeMemory();
	G[assignmentstmt]->list[0]->next->s = TK_ASSIGNOP;
 	G[assignmentstmt]->list[0]->next->next = getListNodeMemory();
 	G[assignmentstmt]->list[0]->next->next->s = arithmeticexpression ;
 	G[assignmentstmt]->list[0]->next->next->next = getListNodeMemory();
 	G[assignmentstmt]->list[0]->next->next->next->s = TK_SEM;
 	G[assignmentstmt]->list[0]->next->next->next->next = NULL;
	
	/*singleorrecid > TK_ID singleorrecid_ .*/

	G[singleorrecid] = malloc(sizeof(grammarNode));
	G[singleorrecid]->numberOfRules = 1;
	G[singleorrecid]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[singleorrecid]->list[0] = getListNodeMemory(); 	 	
	G[singleorrecid]->list[0]->s = TK_ID;
 	G[singleorrecid]->list[0]->next = getListNodeMemory();
	G[singleorrecid]->list[0]->next->s = singleorrecid_;
 	G[singleorrecid]->list[0]->next->next = NULL;

	/*singleorrecord_ > TK_DOT TK_FIELDID .
	  singleorrecord_ > eps .*/

	G[singleorrecid_] = malloc(sizeof(grammarNode));
	G[singleorrecid_]->numberOfRules = 2;
	G[singleorrecid_]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[singleorrecid_]->list[0] = getListNodeMemory(); 	 	
	G[singleorrecid_]->list[0]->s = TK_DOT;
 	G[singleorrecid_]->list[0]->next = getListNodeMemory();
	G[singleorrecid_]->list[0]->next->s = TK_FIELDID ;
 	G[singleorrecid_]->list[0]->next->next = NULL;
	G[singleorrecid_]->list[1] = getListNodeMemory(); 	 	
	G[singleorrecid_]->list[1]->s = TK_EPS;
 	G[singleorrecid_]->list[1]->next = NULL;

	/*funcallstmt > outputparameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputparameters TK_SEM. checked*/

	G[funcallstmt] = malloc(sizeof(grammarNode));
	G[funcallstmt]->numberOfRules = 1;
	G[funcallstmt]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[funcallstmt]->list[0] = getListNodeMemory(); 	 	
	G[funcallstmt]->list[0]->s = outputparameters;
 	G[funcallstmt]->list[0]->next = getListNodeMemory();
	G[funcallstmt]->list[0]->next->s = TK_CALL;
 	G[funcallstmt]->list[0]->next->next = getListNodeMemory();
 	G[funcallstmt]->list[0]->next->next->s = TK_FUNID ;
 	G[funcallstmt]->list[0]->next->next->next = getListNodeMemory();
 	G[funcallstmt]->list[0]->next->next->next->s = TK_WITH;
 	G[funcallstmt]->list[0]->next->next->next->next = getListNodeMemory();
 	G[funcallstmt]->list[0]->next->next->next->next->s = TK_PARAMETERS;
 	G[funcallstmt]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[funcallstmt]->list[0]->next->next->next->next->next->s = inputparameters;
 	G[funcallstmt]->list[0]->next->next->next->next->next->next = getListNodeMemory();
 	G[funcallstmt]->list[0]->next->next->next->next->next->next->s = TK_SEM;
 	G[funcallstmt]->list[0]->next->next->next->next->next->next->next = NULL;

	/*outputparameters > TK_SQL idlist TK_SQR TK_ASSIGNOP . checked
	  outputparameters > eps . checked*/

	G[outputparameters] = malloc(sizeof(grammarNode));
	G[outputparameters]->numberOfRules = 2;
	G[outputparameters]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[outputparameters]->list[0] = getListNodeMemory(); 	 	
	G[outputparameters]->list[0]->s = TK_SQL;
 	G[outputparameters]->list[0]->next = getListNodeMemory();
	G[outputparameters]->list[0]->next->s = idlist ;
	G[outputparameters]->list[0]->next->next = getListNodeMemory();
 	G[outputparameters]->list[0]->next->next->s = TK_SQR ;
 	G[outputparameters]->list[0]->next->next->next = getListNodeMemory();
 	G[outputparameters]->list[0]->next->next->next->s = TK_ASSIGNOP;
 	G[outputparameters]->list[0]->next->next->next->next = NULL;
	G[outputparameters]->list[1] = getListNodeMemory(); 	 	
	G[outputparameters]->list[1]->s = TK_EPS;
 	G[outputparameters]->list[1]->next = NULL;

	/*inputparameters > TK_SQL idlist TK_SQR . checked*/
	
	G[inputparameters] = malloc(sizeof(grammarNode));
	G[inputparameters]->numberOfRules = 1;
	G[inputparameters]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[inputparameters]->list[0] = getListNodeMemory(); 	 	
	G[inputparameters]->list[0]->s = TK_SQL;
 	G[inputparameters]->list[0]->next = getListNodeMemory();
	G[inputparameters]->list[0]->next->s = idlist ;
	G[inputparameters]->list[0]->next->next = getListNodeMemory();
 	G[inputparameters]->list[0]->next->next->s = TK_SQR ;
 	G[inputparameters]->list[0]->next->next->next = NULL;
	
	/*iterativestmt > TK_WHILE TK_OP booleanexpression TK_CL stmt otherstmts TK_ENDWHILE . checked*/

	G[iterativestmt] = malloc(sizeof(grammarNode));
	G[iterativestmt]->numberOfRules = 1;
	G[iterativestmt]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[iterativestmt]->list[0] = getListNodeMemory(); 	 	
	G[iterativestmt]->list[0]->s = TK_WHILE;
 	G[iterativestmt]->list[0]->next = getListNodeMemory();
	G[iterativestmt]->list[0]->next->s = TK_OP;
 	G[iterativestmt]->list[0]->next->next = getListNodeMemory();
 	G[iterativestmt]->list[0]->next->next->s = booleanexpression ;
 	G[iterativestmt]->list[0]->next->next->next = getListNodeMemory();
 	G[iterativestmt]->list[0]->next->next->next->s = TK_CL;
 	G[iterativestmt]->list[0]->next->next->next->next = getListNodeMemory();
 	G[iterativestmt]->list[0]->next->next->next->next->s = stmt;
 	G[iterativestmt]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[iterativestmt]->list[0]->next->next->next->next->next->s = otherstmts;
 	G[iterativestmt]->list[0]->next->next->next->next->next->next = getListNodeMemory();
 	G[iterativestmt]->list[0]->next->next->next->next->next->next->s = TK_ENDWHILE;
 	G[iterativestmt]->list[0]->next->next->next->next->next->next->next = NULL;

	/*conditionalstmt > TK_IF TK_OP booleanexpression TK_CL TK_THEN stmt otherstmts elsepart . checked*/

	G[conditionalstmt] = malloc(sizeof(grammarNode));
	G[conditionalstmt]->numberOfRules = 1;
	G[conditionalstmt]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[conditionalstmt]->list[0] = getListNodeMemory(); 	 	
	G[conditionalstmt]->list[0]->s = TK_IF;
 	G[conditionalstmt]->list[0]->next = getListNodeMemory();
	G[conditionalstmt]->list[0]->next->s = TK_OP;
 	G[conditionalstmt]->list[0]->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->s = booleanexpression ;
 	G[conditionalstmt]->list[0]->next->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->next->s = TK_CL;
 	G[conditionalstmt]->list[0]->next->next->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->next->next->s = TK_THEN;
 	G[conditionalstmt]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->next->next->next->s = stmt;
 	G[conditionalstmt]->list[0]->next->next->next->next->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->next->next->next->next->s = otherstmts;
 	G[conditionalstmt]->list[0]->next->next->next->next->next->next->next = getListNodeMemory();
 	G[conditionalstmt]->list[0]->next->next->next->next->next->next->next->s = elsepart;
 	G[conditionalstmt]->list[0]->next->next->next->next->next->next->next->next = NULL;

	/*elsepart > TK_ELSE stmt otherstmts TK_ENDIF . checked
	  elsepart > TK_ENDIF . checked*/

	G[elsepart] = malloc(sizeof(grammarNode));
	G[elsepart]->numberOfRules = 2;
	G[elsepart]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[elsepart]->list[0] = getListNodeMemory(); 	 	
	G[elsepart]->list[0]->s = TK_ELSE;
 	G[elsepart]->list[0]->next = getListNodeMemory();
	G[elsepart]->list[0]->next->s = stmt ;
	G[elsepart]->list[0]->next->next = getListNodeMemory();
 	G[elsepart]->list[0]->next->next->s = otherstmts ;
 	G[elsepart]->list[0]->next->next->next = getListNodeMemory();
 	G[elsepart]->list[0]->next->next->next->s = TK_ENDIF;
 	G[elsepart]->list[0]->next->next->next->next = NULL;
	G[elsepart]->list[1] = getListNodeMemory(); 	 	
	G[elsepart]->list[1]->s = TK_ENDIF;
 	G[elsepart]->list[1]->next = NULL;

	/*iostmt > TK_READ TK_OP singleorrecid TK_CL TK_SEM . checked
	  iostmt > TK_WRITE TK_OP allvar TK_CL TK_SEM . checked*/

	G[iostmt] = malloc(sizeof(grammarNode));
	G[iostmt]->numberOfRules = 2;
	G[iostmt]->list = malloc(sizeof( listNode * ) * 2 );	
 	G[iostmt]->list[0] = getListNodeMemory(); 	 	
	G[iostmt]->list[0]->s = TK_READ;
 	G[iostmt]->list[0]->next = getListNodeMemory();
	G[iostmt]->list[0]->next->s = TK_OP;
 	G[iostmt]->list[0]->next->next = getListNodeMemory();
 	G[iostmt]->list[0]->next->next->s = singleorrecid ;
 	G[iostmt]->list[0]->next->next->next = getListNodeMemory();
 	G[iostmt]->list[0]->next->next->next->s = TK_CL;
 	G[iostmt]->list[0]->next->next->next->next = getListNodeMemory();
 	G[iostmt]->list[0]->next->next->next->next->s = TK_SEM;
 	G[iostmt]->list[0]->next->next->next->next->next = NULL;
	G[iostmt]->list[1] = getListNodeMemory(); 	 	
	G[iostmt]->list[1]->s = TK_WRITE;
 	G[iostmt]->list[1]->next = getListNodeMemory();
	G[iostmt]->list[1]->next->s = TK_OP;
 	G[iostmt]->list[1]->next->next = getListNodeMemory();
 	G[iostmt]->list[1]->next->next->s = allvar ;
 	G[iostmt]->list[1]->next->next->next = getListNodeMemory();
 	G[iostmt]->list[1]->next->next->next->s = TK_CL;
 	G[iostmt]->list[1]->next->next->next->next = getListNodeMemory();
 	G[iostmt]->list[1]->next->next->next->next->s = TK_SEM;
 	G[iostmt]->list[1]->next->next->next->next->next = NULL;

	/*allvar > var . checked
	  allvar > TK_RECORDID TK_DOT TK_FIELDID . checked*/

	G[allvar] = malloc(sizeof(grammarNode));
	G[allvar]->numberOfRules = 2;
	G[allvar]->list = malloc(sizeof( listNode * ) * 2 );
	G[allvar]->list[0] = getListNodeMemory(); 	 	
	G[allvar]->list[0]->s = var;
 	G[allvar]->list[0]->next = NULL;	
 	G[allvar]->list[1] = getListNodeMemory(); 	 	
	G[allvar]->list[1]->s = TK_RECORDID;
 	G[allvar]->list[1]->next = getListNodeMemory();
	G[allvar]->list[1]->next->s = TK_DOT;
 	G[allvar]->list[1]->next->next = getListNodeMemory();
 	G[allvar]->list[1]->next->next->s = TK_FIELDID ;
 	G[allvar]->list[1]->next->next->next = NULL;

	/*arithmeticexpression > term innerterm . -new*/

	G[arithmeticexpression] = malloc(sizeof(grammarNode));
	G[arithmeticexpression]->numberOfRules = 1;
	G[arithmeticexpression]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[arithmeticexpression]->list[0] = getListNodeMemory(); 	 	
	G[arithmeticexpression]->list[0]->s = term;
 	G[arithmeticexpression]->list[0]->next = getListNodeMemory();
	G[arithmeticexpression]->list[0]->next->s = innerterm;
 	G[arithmeticexpression]->list[0]->next->next = NULL;

	/* innerterm > plusminus term innerterm	
	   innerterm > TK_EPS. - new*/

	G[innerterm] = malloc(sizeof(grammarNode));
	G[innerterm]->numberOfRules = 2;
	G[innerterm]->list = malloc(sizeof( listNode * ) * 2 );
	G[innerterm]->list[0] = getListNodeMemory(); 	 	
	G[innerterm]->list[0]->s = plusminus;
 	G[innerterm]->list[0]->next = getListNodeMemory();
	G[innerterm]->list[0]->next->s = term;
 	G[innerterm]->list[0]->next->next = getListNodeMemory();
 	G[innerterm]->list[0]->next->next->s = innerterm ;
 	G[innerterm]->list[0]->next->next->next = NULL;
	G[innerterm]->list[1] = getListNodeMemory(); 	 	
	G[innerterm]->list[1]->s = TK_EPS;
 	G[innerterm]->list[1]->next = NULL;	
 	
	/*term > factor termprime . checked*/

	G[term] = malloc(sizeof(grammarNode));
	G[term]->numberOfRules = 1;
	G[term]->list = malloc(sizeof( listNode * ) * 1 );
	G[term]->list[0] = getListNodeMemory(); 	 	
	G[term]->list[0]->s = factor;
 	G[term]->list[0]->next = getListNodeMemory();
	G[term]->list[0]->next->s = termprime;
 	G[term]->list[0]->next->next = NULL;
	
	/* new
	   termprime > muldiv factor termprime .
	  termprime > eps .*/

	G[termprime] = malloc(sizeof(grammarNode));
	G[termprime]->numberOfRules = 2;
	G[termprime]->list = malloc(sizeof( listNode * ) * 2 );
	G[termprime]->list[0] = getListNodeMemory(); 	 	
	G[termprime]->list[0]->s = muldiv;
 	G[termprime]->list[0]->next = getListNodeMemory();
	G[termprime]->list[0]->next->s = factor;
 	G[termprime]->list[0]->next->next = getListNodeMemory();
 	G[termprime]->list[0]->next->next->s = termprime ;
 	G[termprime]->list[0]->next->next->next = NULL;
	G[termprime]->list[1] = getListNodeMemory(); 	 	
	G[termprime]->list[1]->s = TK_EPS;
 	G[termprime]->list[1]->next = NULL;
	
	/*factor > TK_OP arithmeticexpression TK_CL .checked
	  factor > all .checked*/

	G[factor] = malloc(sizeof(grammarNode));
	G[factor]->numberOfRules = 2;
	G[factor]->list = malloc(sizeof( listNode * ) * 2 );
	G[factor]->list[0] = getListNodeMemory(); 	 	
	G[factor]->list[0]->s = TK_OP;
 	G[factor]->list[0]->next = getListNodeMemory();
	G[factor]->list[0]->next->s = arithmeticexpression;
 	G[factor]->list[0]->next->next = getListNodeMemory();
 	G[factor]->list[0]->next->next->s = TK_CL ;
 	G[factor]->list[0]->next->next->next = NULL;
	G[factor]->list[1] = getListNodeMemory(); 	 	
	G[factor]->list[1]->s = all;
 	G[factor]->list[1]->next = NULL;

	/*muldiv > TK_MUL .
	  muldiv > TK_DIV .*/

	G[muldiv] = malloc(sizeof(grammarNode));
	G[muldiv]->numberOfRules = 2;
	G[muldiv]->list = malloc(sizeof( listNode * ) * 2 );
	G[muldiv]->list[0] = getListNodeMemory(); 	 	
	G[muldiv]->list[0]->s = TK_MUL;
 	G[muldiv]->list[0]->next = NULL;
	G[muldiv]->list[1] = getListNodeMemory(); 	 	
	G[muldiv]->list[1]->s = TK_DIV;
 	G[muldiv]->list[1]->next = NULL;

	/*plusminus > TK_PLUS .
	   plusminus > TK_MINUS .*/

	G[plusminus] = malloc(sizeof(grammarNode));
	G[plusminus]->numberOfRules = 2;
	G[plusminus]->list = malloc(sizeof( listNode * ) * 2 );
	G[plusminus]->list[0] = getListNodeMemory(); 	 	
	G[plusminus]->list[0]->s = TK_PLUS;
 	G[plusminus]->list[0]->next = NULL;
	G[plusminus]->list[1] = getListNodeMemory(); 	 	
	G[plusminus]->list[1]->s = TK_MINUS;
 	G[plusminus]->list[1]->next = NULL;

	/*all > TK_NUM .
	  all > TK_RNUM .
	  all > TK_ID singleorrecid_ */
	

	G[all] = malloc(sizeof(grammarNode));
	G[all]->numberOfRules = 3;
	G[all]->list = malloc(sizeof( listNode * ) * 3 );
	G[all]->list[0] = getListNodeMemory(); 	 	
	G[all]->list[0]->s = TK_NUM;
 	G[all]->list[0]->next = NULL;
	G[all]->list[1] = getListNodeMemory(); 	 	
	G[all]->list[1]->s = TK_RNUM;
 	G[all]->list[1]->next = NULL;
	G[all]->list[2] = getListNodeMemory(); 	 	
	G[all]->list[2]->s = TK_ID;
 	G[all]->list[2]->next = getListNodeMemory();
 	G[all]->list[2]->next->s = singleorrecid_;
 	G[all]->list[2]->next->next = NULL;

	/*booleanexpression > TK_OP booleanexpression TK_CL logicalop TK_OP booleanexpression TK_CL . checked
	booleanexpression > var relationalop var .checked
	booleanexpression > TK_NOT TK_OP booleanexpression TK_CL .checked*/

	G[booleanexpression] = malloc(sizeof(grammarNode));
	G[booleanexpression]->numberOfRules = 3;
	G[booleanexpression]->list = malloc(sizeof( listNode * ) * 3 );	
 	G[booleanexpression]->list[0] = getListNodeMemory(); 	 	
	G[booleanexpression]->list[0]->s = TK_OP;
 	G[booleanexpression]->list[0]->next = getListNodeMemory();
	G[booleanexpression]->list[0]->next->s = booleanexpression;
 	G[booleanexpression]->list[0]->next->next = getListNodeMemory();
 	G[booleanexpression]->list[0]->next->next->s = TK_CL ;
 	G[booleanexpression]->list[0]->next->next->next = getListNodeMemory();
 	G[booleanexpression]->list[0]->next->next->next->s = logicalop;
 	G[booleanexpression]->list[0]->next->next->next->next = getListNodeMemory();
 	G[booleanexpression]->list[0]->next->next->next->next->s = TK_OP;
 	G[booleanexpression]->list[0]->next->next->next->next->next = getListNodeMemory();
 	G[booleanexpression]->list[0]->next->next->next->next->next->s = booleanexpression;
 	G[booleanexpression]->list[0]->next->next->next->next->next->next = getListNodeMemory();
 	G[booleanexpression]->list[0]->next->next->next->next->next->next->s = TK_CL;
 	G[booleanexpression]->list[0]->next->next->next->next->next->next->next = NULL;
	G[booleanexpression]->list[1] = getListNodeMemory(); 	 	
	G[booleanexpression]->list[1]->s = var;
 	G[booleanexpression]->list[1]->next = getListNodeMemory();
	G[booleanexpression]->list[1]->next->s = relationalop;
 	G[booleanexpression]->list[1]->next->next = getListNodeMemory();
 	G[booleanexpression]->list[1]->next->next->s = var ;
 	G[booleanexpression]->list[1]->next->next->next = NULL;
	G[booleanexpression]->list[2] = getListNodeMemory(); 	 	
	G[booleanexpression]->list[2]->s = TK_NOT;
 	G[booleanexpression]->list[2]->next = getListNodeMemory();
	G[booleanexpression]->list[2]->next->s = TK_OP;
 	G[booleanexpression]->list[2]->next->next = getListNodeMemory();
 	G[booleanexpression]->list[2]->next->next->s =booleanexpression ;
 	G[booleanexpression]->list[2]->next->next->next = getListNodeMemory();
 	G[booleanexpression]->list[2]->next->next->next->s = TK_CL;
 	G[booleanexpression]->list[2]->next->next->next->next = NULL;

	/*var > TK_ID singleorrecid_
	var > TK_NUM .
	var > TK_RNUM .*/
	
	G[var] = malloc(sizeof(grammarNode));
	G[var]->numberOfRules = 3;
	G[var]->list = malloc(sizeof( listNode * ) * 3 );
	G[var]->list[0] = getListNodeMemory(); 	 	
	G[var]->list[0]->s = TK_ID;
 	G[var]->list[0]->next = getListNodeMemory();
	G[var]->list[0]->next->s = singleorrecid_;
 	G[var]->list[0]->next->next = NULL;
	G[var]->list[1] = getListNodeMemory(); 	 	
	G[var]->list[1]->s = TK_NUM;
 	G[var]->list[1]->next = NULL;
	G[var]->list[2] = getListNodeMemory(); 	 	
	G[var]->list[2]->s = TK_RNUM;
 	G[var]->list[2]->next = NULL;

	/*logicalop > TK_AND . checked
	logicalop > TK_OR . checked*/

	G[logicalop] = malloc(sizeof(grammarNode));
	G[logicalop]->numberOfRules = 2;
	G[logicalop]->list = malloc(sizeof( listNode * ) * 2 );
	G[logicalop]->list[0] = getListNodeMemory(); 	 	
	G[logicalop]->list[0]->s = TK_AND;
 	G[logicalop]->list[0]->next = NULL;
	G[logicalop]->list[1] = getListNodeMemory(); 	 	
	G[logicalop]->list[1]->s = TK_OR;
 	G[logicalop]->list[1]->next = NULL;

	/*relationalop > TK_LT .checked
	relationalop > TK_LE .checked
	relationalop > TK_EQ .checked
	relationalop > TK_GT .checked
	relationalop > TK_GE .checked
	relationalop > TK_NE .checked*/

	G[relationalop] = malloc(sizeof(grammarNode));
	G[relationalop]->numberOfRules = 6;
	G[relationalop]->list = malloc(sizeof( listNode * ) * 6 );	
 	G[relationalop]->list[0] = getListNodeMemory(); 	 	
	G[relationalop]->list[0]->s = TK_LT;
 	G[relationalop]->list[0]->next = NULL;
	G[relationalop]->list[1] = getListNodeMemory(); 	 	
	G[relationalop]->list[1]->s = TK_LE;
 	G[relationalop]->list[1]->next = NULL;
	G[relationalop]->list[2] = getListNodeMemory(); 	 	
	G[relationalop]->list[2]->s = TK_EQ;
 	G[relationalop]->list[2]->next = NULL;
	G[relationalop]->list[3] = getListNodeMemory(); 	 	
	G[relationalop]->list[3]->s = TK_GT;
 	G[relationalop]->list[3]->next = NULL;
	G[relationalop]->list[4] = getListNodeMemory(); 	 	
	G[relationalop]->list[4]->s = TK_GE;
 	G[relationalop]->list[4]->next = NULL;
	G[relationalop]->list[5] = getListNodeMemory(); 	 	
	G[relationalop]->list[5]->s = TK_NE;
 	G[relationalop]->list[5]->next = NULL;

	/*returnstmt > TK_RETURN optionalreturn TK_SEM .checked*/

	G[returnstmt] = malloc(sizeof(grammarNode));
	G[returnstmt]->numberOfRules = 1;
	G[returnstmt]->list = malloc(sizeof( listNode * ) * 1 );	
 	G[returnstmt]->list[0] = getListNodeMemory(); 	 	
	G[returnstmt]->list[0]->s = TK_RETURN;
 	G[returnstmt]->list[0]->next = getListNodeMemory();
	G[returnstmt]->list[0]->next->s = optionalreturn;
 	G[returnstmt]->list[0]->next->next = getListNodeMemory();
 	G[returnstmt]->list[0]->next->next->s = TK_SEM ;
 	G[returnstmt]->list[0]->next->next->next = NULL;

	/*optionalreturn > TK_SQL idlist TK_SQR .checked
	optionalreturn > eps .checked*/

	G[optionalreturn] = malloc(sizeof(grammarNode));
	G[optionalreturn]->numberOfRules = 2;
	G[optionalreturn]->list = malloc(sizeof( listNode * ) * 2 );
	G[optionalreturn]->list[0] = getListNodeMemory(); 	 	
	G[optionalreturn]->list[0]->s = TK_SQL;
 	G[optionalreturn]->list[0]->next = getListNodeMemory();
 	G[optionalreturn]->list[0]->next->s = idlist;
 	G[optionalreturn]->list[0]->next->next = getListNodeMemory();
 	G[optionalreturn]->list[0]->next->next->s = TK_SQR;
 	G[optionalreturn]->list[0]->next->next->next = NULL;
	G[optionalreturn]->list[1] = getListNodeMemory(); 	 	
	G[optionalreturn]->list[1]->s = TK_EPS;
 	G[optionalreturn]->list[1]->next = NULL;

	/*idlist > TK_ID more_ids .checked*/
	
	G[idlist] = malloc(sizeof(grammarNode));
	G[idlist]->numberOfRules = 1;
	G[idlist]->list = malloc(sizeof( listNode * ) * 1 );
	G[idlist]->list[0] = getListNodeMemory(); 	 	
	G[idlist]->list[0]->s = TK_ID;
 	G[idlist]->list[0]->next = getListNodeMemory();
 	G[idlist]->list[0]->next->s = more_ids;
 	G[idlist]->list[0]->next->next = NULL;

	/*more_ids > TK_COMMA idlist .checked
	more_ids > eps .checked*/

	G[more_ids] = malloc(sizeof(grammarNode));
	G[more_ids]->numberOfRules = 2;
	G[more_ids]->list = malloc(sizeof( listNode * ) * 2 );
	G[more_ids]->list[0] = getListNodeMemory(); 	 	
	G[more_ids]->list[0]->s = TK_COMMA;
 	G[more_ids]->list[0]->next = getListNodeMemory();
 	G[more_ids]->list[0]->next->s =idlist;
 	G[more_ids]->list[0]->next->next = NULL;
	G[more_ids]->list[1] = getListNodeMemory(); 	 	
	G[more_ids]->list[1]->s = TK_EPS;
 	G[more_ids]->list[1]->next = NULL;

	/* recAdjust > eps*/

	G[recAdjust] = malloc(sizeof(grammarNode));
	G[recAdjust]->numberOfRules = 1;
	G[recAdjust]->list = malloc(sizeof( listNode * ) * 1 );
	G[recAdjust]->list[0] = getListNodeMemory(); 	 	
	G[recAdjust]->list[0]->s = TK_EPS;
 	G[recAdjust]->list[0]->next = NULL;
	
	return G;
	
}

/*function to populate First sets. Each First set is a linked list*/
listNode ** populateFirst( listNode ** First )
{
	First = (listNode **)malloc( (NUMBER_OF_NONTERMINALS + NUMBER_OF_TERMINALS) * sizeof(listNode *));

	int i;	
	for( i=0; i<(NUMBER_OF_NONTERMINALS + NUMBER_OF_TERMINALS); i++ )
	{
		First[i] = NULL;
	}

	First[TK_ASSIGNOP] = addSymbolToList( First[TK_ASSIGNOP], TK_ASSIGNOP );
	First[TK_FIELDID] = addSymbolToList( First[TK_FIELDID], TK_FIELDID );
	First[TK_ID] = addSymbolToList( First[TK_ID], TK_ID );
	First[TK_NUM] = addSymbolToList( First[TK_NUM], TK_NUM );
	First[TK_RNUM] = addSymbolToList( First[TK_RNUM], TK_RNUM );
	First[TK_FUNID] = addSymbolToList( First[TK_FUNID], TK_FUNID );
	First[TK_RECORDID] = addSymbolToList( First[TK_RECORDID], TK_RECORDID );
	First[TK_WITH] = addSymbolToList( First[TK_WITH], TK_WITH );
	First[TK_PARAMETERS] = addSymbolToList( First[TK_PARAMETERS], TK_PARAMETERS );
	First[TK_END] = addSymbolToList( First[TK_END], TK_END );
	First[TK_WHILE] = addSymbolToList( First[TK_WHILE], TK_WHILE );
	First[TK_INT] = addSymbolToList( First[TK_INT], TK_INT );
	First[TK_REAL] = addSymbolToList( First[TK_REAL], TK_REAL );
	First[TK_TYPE] = addSymbolToList( First[TK_TYPE], TK_TYPE );
	First[TK_MAIN] = addSymbolToList( First[TK_MAIN], TK_MAIN );
	First[TK_GLOBAL] = addSymbolToList( First[TK_GLOBAL], TK_GLOBAL );
	First[TK_PARAMETER] = addSymbolToList( First[TK_PARAMETER], TK_PARAMETER );
	First[TK_LIST] = addSymbolToList( First[TK_LIST], TK_LIST );
	First[TK_SQL] = addSymbolToList( First[TK_SQL], TK_SQL );
	First[TK_SQR] = addSymbolToList( First[TK_SQR], TK_SQR );
	First[TK_INPUT] = addSymbolToList( First[TK_INPUT], TK_INPUT );
	First[TK_OUTPUT] = addSymbolToList( First[TK_OUTPUT], TK_OUTPUT );
	First[TK_SEM] = addSymbolToList( First[TK_SEM], TK_SEM );
	First[TK_COLON] = addSymbolToList( First[TK_COLON], TK_COLON );
	First[TK_DOT] = addSymbolToList( First[TK_DOT], TK_DOT );
	First[TK_ENDWHILE] = addSymbolToList( First[TK_ENDWHILE], TK_ENDWHILE );
	First[TK_OP] = addSymbolToList( First[TK_OP], TK_OP );
	First[TK_CL] = addSymbolToList( First[TK_CL], TK_CL );
	First[TK_IF] = addSymbolToList( First[TK_IF], TK_IF );
	First[TK_THEN] = addSymbolToList( First[TK_THEN], TK_THEN );
	First[TK_ENDIF] = addSymbolToList( First[TK_ENDIF], TK_ENDIF );
	First[TK_READ] = addSymbolToList( First[TK_READ], TK_READ );
	First[TK_WRITE] = addSymbolToList( First[TK_WRITE], TK_WRITE );
	First[TK_RETURN] = addSymbolToList( First[TK_RETURN], TK_RETURN );
	First[TK_PLUS] = addSymbolToList( First[TK_PLUS], TK_PLUS );
	First[TK_MINUS] = addSymbolToList( First[TK_MINUS], TK_MINUS );
	First[TK_MUL] = addSymbolToList( First[TK_MUL], TK_MUL );
	First[TK_DIV] = addSymbolToList( First[TK_DIV], TK_DIV );
	First[TK_CALL] = addSymbolToList( First[TK_CALL], TK_CALL );
	First[TK_RECORD] = addSymbolToList( First[TK_RECORD], TK_RECORD );
	First[TK_ENDRECORD] = addSymbolToList( First[TK_ENDRECORD], TK_RECORD );
	First[TK_ELSE] = addSymbolToList( First[TK_ELSE], TK_ELSE );
	First[TK_AND] = addSymbolToList( First[TK_AND], TK_AND );
	First[TK_OR] = addSymbolToList( First[TK_OR], TK_OR );
	First[TK_NOT] = addSymbolToList( First[TK_NOT], TK_NOT );
	First[TK_LT] = addSymbolToList( First[TK_LT], TK_LT );
	First[TK_LE] = addSymbolToList( First[TK_LE], TK_LE );
	First[TK_EQ] = addSymbolToList( First[TK_EQ], TK_EQ );
	First[TK_GT] = addSymbolToList( First[TK_GT], TK_GT );
	First[TK_GE] = addSymbolToList( First[TK_GE], TK_GE );
	First[TK_NE] = addSymbolToList( First[TK_NE], TK_NE );
	First[TK_COMMA] = addSymbolToList( First[TK_COMMA], TK_COMMA );
	First[TK_EPS] = addSymbolToList( First[TK_EPS], TK_EPS );
	First[TK_DOLLAR] = addSymbolToList( First[TK_DOLLAR], TK_DOLLAR );
	
	First[program] = addSymbolToList( First[program], TK_FUNID );
	First[program] = addSymbolToList( First[program], TK_MAIN );
	First[mainfunction] = addSymbolToList( First[mainfunction], TK_MAIN );
	First[otherfunctions] = addSymbolToList( First[otherfunctions], TK_FUNID );
	First[otherfunctions] = addSymbolToList( First[otherfunctions], TK_EPS );
	First[function] = addSymbolToList( First[function], TK_FUNID );
	First[input_par] = addSymbolToList( First[input_par], TK_INPUT );
	First[output_par] = addSymbolToList( First[output_par], TK_OUTPUT );
	First[output_par] = addSymbolToList( First[output_par], TK_EPS );
	First[parameter_list] = addSymbolToList( First[parameter_list], TK_INT );
	First[parameter_list] = addSymbolToList( First[parameter_list], TK_REAL );
	First[parameter_list] = addSymbolToList( First[parameter_list], TK_RECORD );
	First[datatype] = addSymbolToList( First[datatype], TK_INT );
	First[datatype] = addSymbolToList( First[datatype], TK_REAL );
	First[datatype] = addSymbolToList( First[datatype], TK_RECORD );
	First[primitivedatatype] = addSymbolToList( First[primitivedatatype], TK_INT );
	First[primitivedatatype] = addSymbolToList( First[primitivedatatype], TK_REAL );
	First[constructeddatatype] = addSymbolToList( First[constructeddatatype], TK_RECORD );
	First[remaining_list] = addSymbolToList( First[remaining_list], TK_COMMA );
	First[remaining_list] = addSymbolToList( First[remaining_list], TK_EPS );
	First[stmts] = addSymbolToList( First[stmts], TK_RECORD );
	First[stmts] = addSymbolToList( First[stmts], TK_TYPE );
	First[stmts] = addSymbolToList( First[stmts], TK_ID );
	First[stmts] = addSymbolToList( First[stmts], TK_RECORDID );
	First[stmts] = addSymbolToList( First[stmts], TK_WHILE );
	First[stmts] = addSymbolToList( First[stmts], TK_IF );
	First[stmts] = addSymbolToList( First[stmts], TK_READ );
	First[stmts] = addSymbolToList( First[stmts], TK_SQL );
	First[stmts] = addSymbolToList( First[stmts], TK_CALL );
	First[stmts] = addSymbolToList( First[stmts], TK_RETURN );
	First[stmts] = addSymbolToList( First[stmts], TK_WRITE );
	First[typedefinitions] = addSymbolToList( First[typedefinitions], TK_EPS );
	First[typedefinitions] = addSymbolToList( First[typedefinitions], TK_RECORD );
	First[typedefinition] = addSymbolToList( First[typedefinition], TK_RECORD );
	First[fielddefinitions] = addSymbolToList( First[fielddefinitions], TK_TYPE );
	First[fielddefinition] = addSymbolToList( First[fielddefinition], TK_TYPE );
	First[morefields] = addSymbolToList( First[morefields], TK_TYPE );
	First[morefields] = addSymbolToList( First[morefields], TK_EPS );
	First[declarations] = addSymbolToList( First[declarations], TK_TYPE );
	First[declarations] = addSymbolToList( First[declarations], TK_EPS );
	First[declaration] = addSymbolToList( First[declaration], TK_TYPE );
	First[global_or_not] = addSymbolToList( First[global_or_not], TK_COLON );
	First[global_or_not] = addSymbolToList( First[global_or_not], TK_EPS );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_ID );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_WRITE );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_IF );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_READ );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_WHILE );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_SQL );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_CALL );
	First[otherstmts] = addSymbolToList( First[otherstmts], TK_EPS );
	First[stmt] = addSymbolToList( First[stmt], TK_ID );
	First[stmt] = addSymbolToList( First[stmt], TK_WRITE );
	First[stmt] = addSymbolToList( First[stmt], TK_IF );
	First[stmt] = addSymbolToList( First[stmt], TK_READ );
	First[stmt] = addSymbolToList( First[stmt], TK_WHILE );
	First[stmt] = addSymbolToList( First[stmt], TK_SQL );
	First[stmt] = addSymbolToList( First[stmt], TK_CALL );
	First[assignmentstmt] = addSymbolToList( First[assignmentstmt], TK_ID );
	First[singleorrecid] = addSymbolToList( First[singleorrecid], TK_ID );
	First[singleorrecid_] = addSymbolToList( First[singleorrecid_], TK_DOT );
	First[singleorrecid_] = addSymbolToList( First[singleorrecid_], TK_EPS );
	First[funcallstmt] = addSymbolToList( First[funcallstmt], TK_SQL );
	First[funcallstmt] = addSymbolToList( First[funcallstmt], TK_CALL );
	First[outputparameters] = addSymbolToList( First[outputparameters], TK_EPS );
	First[outputparameters] = addSymbolToList( First[outputparameters], TK_SQL );
	First[inputparameters] = addSymbolToList( First[inputparameters], TK_SQL );
	First[iterativestmt] = addSymbolToList( First[iterativestmt], TK_WHILE );
	First[conditionalstmt] = addSymbolToList( First[conditionalstmt], TK_IF );
	First[elsepart] = addSymbolToList( First[elsepart], TK_ELSE );
	First[elsepart] = addSymbolToList( First[elsepart], TK_ENDIF );
	First[iostmt] = addSymbolToList( First[iostmt], TK_READ );
	First[iostmt] = addSymbolToList( First[iostmt], TK_WRITE );
	First[allvar] = addSymbolToList( First[allvar], TK_ID );
	First[allvar] = addSymbolToList( First[allvar], TK_RNUM );
	First[allvar] = addSymbolToList( First[allvar], TK_NUM );
	First[allvar] = addSymbolToList( First[allvar], TK_RECORDID );
	First[arithmeticexpression] = addSymbolToList( First[arithmeticexpression], TK_ID );
	First[arithmeticexpression] = addSymbolToList( First[arithmeticexpression], TK_NUM );
	First[arithmeticexpression] = addSymbolToList( First[arithmeticexpression], TK_RNUM );
	First[arithmeticexpression] = addSymbolToList( First[arithmeticexpression], TK_RECORDID );
	First[arithmeticexpression] = addSymbolToList( First[arithmeticexpression], TK_OP );
	First[innerterm] = addSymbolToList( First[innerterm], TK_PLUS );
	First[innerterm] = addSymbolToList( First[innerterm], TK_MINUS );
	First[innerterm] = addSymbolToList( First[innerterm], TK_EPS );
	First[term] = addSymbolToList( First[term], TK_ID );
	First[term] = addSymbolToList( First[term], TK_NUM );
	First[term] = addSymbolToList( First[term], TK_RNUM );
	First[term] = addSymbolToList( First[term], TK_RECORDID );
	First[term] = addSymbolToList( First[term], TK_OP );
	First[termprime] = addSymbolToList( First[termprime], TK_MUL );
	First[termprime] = addSymbolToList( First[termprime], TK_DIV );
	First[termprime] = addSymbolToList( First[termprime], TK_EPS );
	First[factor] = addSymbolToList( First[factor], TK_ID );
	First[factor] = addSymbolToList( First[factor], TK_NUM );
	First[factor] = addSymbolToList( First[factor], TK_RNUM );
	First[factor] = addSymbolToList( First[factor], TK_RECORDID );
	First[factor] = addSymbolToList( First[factor], TK_OP );
	First[muldiv] = addSymbolToList( First[muldiv], TK_MUL );
	First[muldiv] = addSymbolToList( First[muldiv], TK_DIV );
	First[plusminus] = addSymbolToList( First[plusminus], TK_PLUS );
	First[plusminus] = addSymbolToList( First[plusminus], TK_MINUS );
	First[all] = addSymbolToList( First[all], TK_NUM );
	First[all] = addSymbolToList( First[all], TK_RNUM );
	First[all] = addSymbolToList( First[all], TK_ID );
	First[all] = addSymbolToList( First[all], TK_RECORDID );
	First[booleanexpression] = addSymbolToList( First[booleanexpression], TK_OP );
	First[booleanexpression] = addSymbolToList( First[booleanexpression], TK_ID );
	First[booleanexpression] = addSymbolToList( First[booleanexpression], TK_NUM );
	First[booleanexpression] = addSymbolToList( First[booleanexpression], TK_RNUM );
	First[booleanexpression] = addSymbolToList( First[booleanexpression], TK_NOT );
	First[var] = addSymbolToList( First[var], TK_ID );
	First[var] = addSymbolToList( First[var], TK_NUM );
	First[var] = addSymbolToList( First[var], TK_RNUM );
	First[logicalop] = addSymbolToList( First[logicalop], TK_AND );
	First[logicalop] = addSymbolToList( First[logicalop], TK_OR );
	First[relationalop] = addSymbolToList( First[relationalop], TK_LT );
	First[relationalop] = addSymbolToList( First[relationalop], TK_LE );
	First[relationalop] = addSymbolToList( First[relationalop], TK_EQ );
	First[relationalop] = addSymbolToList( First[relationalop], TK_GT );
	First[relationalop] = addSymbolToList( First[relationalop], TK_GE );
	First[relationalop] = addSymbolToList( First[relationalop], TK_NE );
	First[returnstmt] = addSymbolToList( First[returnstmt], TK_RETURN );
	First[optionalreturn] = addSymbolToList( First[optionalreturn], TK_SQL );
	First[optionalreturn] = addSymbolToList( First[optionalreturn], TK_EPS );
	First[idlist] = addSymbolToList( First[idlist], TK_ID );
	First[more_ids] = addSymbolToList( First[more_ids], TK_COMMA );
	First[more_ids] = addSymbolToList( First[more_ids], TK_EPS );
	First[recAdjust] = addSymbolToList( First[recAdjust], TK_EPS );

	return First;
}

/*function to populate Follow sets. Each Follow set is a linked list*/
listNode ** populateFollow( listNode ** Follow )
{
	Follow = (listNode **)malloc( (NUMBER_OF_NONTERMINALS + NUMBER_OF_TERMINALS) * sizeof(listNode *));

	int i;	
	for( i=0; i<(NUMBER_OF_NONTERMINALS + NUMBER_OF_TERMINALS); i++ )
	{
		Follow[i] = NULL;
	}

	Follow[program] = addSymbolToList( Follow[program], TK_DOLLAR );
	Follow[mainfunction] = addSymbolToList( Follow[mainfunction], TK_DOLLAR );
	Follow[otherfunctions] = addSymbolToList( Follow[otherfunctions], TK_MAIN );
	Follow[function] = addSymbolToList( Follow[function], TK_FUNID );
	Follow[function] = addSymbolToList( Follow[function], TK_MAIN );
	Follow[input_par] = addSymbolToList( Follow[input_par], TK_OUTPUT );
	Follow[input_par] = addSymbolToList( Follow[input_par], TK_SEM );
	Follow[output_par] = addSymbolToList( Follow[output_par], TK_SEM );
	Follow[parameter_list] = addSymbolToList( Follow[parameter_list], TK_SQR );
	Follow[datatype] = addSymbolToList( Follow[datatype], TK_ID );
	Follow[datatype] = addSymbolToList( Follow[datatype], TK_COLON );
	Follow[primitivedatatype] = addSymbolToList( Follow[primitivedatatype], TK_ID );
	Follow[primitivedatatype] = addSymbolToList( Follow[primitivedatatype], TK_COLON );
	Follow[constructeddatatype] = addSymbolToList( Follow[constructeddatatype], TK_ID );
	Follow[constructeddatatype] = addSymbolToList( Follow[constructeddatatype], TK_COLON );
	Follow[remaining_list] = addSymbolToList( Follow[remaining_list], TK_SQR );
	Follow[stmts] = addSymbolToList( Follow[stmts], TK_END );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_TYPE );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_ID );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_RETURN );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_WHILE );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_IF );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_READ );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_WRITE );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_SQL );
	Follow[typedefinitions] = addSymbolToList( Follow[typedefinitions], TK_CALL );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_RETURN );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_TYPE );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_ID );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_RECORD );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_WHILE );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_IF );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_READ );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_WRITE );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_SQL );
	Follow[typedefinition] = addSymbolToList( Follow[typedefinition], TK_CALL );
	Follow[fielddefinitions] = addSymbolToList( Follow[fielddefinitions], TK_ENDRECORD );
	Follow[fielddefinition] = addSymbolToList( Follow[fielddefinition], TK_TYPE );
	Follow[fielddefinition] = addSymbolToList( Follow[fielddefinition], TK_ENDRECORD );
	Follow[morefields] = addSymbolToList( Follow[morefields], TK_ENDRECORD );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_ID );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_WHILE );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_IF );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_READ );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_WRITE );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_SQL );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_CALL );
	Follow[declarations] = addSymbolToList( Follow[declarations], TK_RETURN );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_TYPE );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_ID );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_WHILE );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_IF );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_READ );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_WRITE );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_SQL );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_CALL );
	Follow[declaration] = addSymbolToList( Follow[declaration], TK_RETURN );
	Follow[global_or_not] = addSymbolToList( Follow[global_or_not], TK_SEM );
	Follow[otherstmts] = addSymbolToList( Follow[otherstmts], TK_RETURN );
	Follow[otherstmts] = addSymbolToList( Follow[otherstmts], TK_ENDIF );
	Follow[otherstmts] = addSymbolToList( Follow[otherstmts], TK_ENDWHILE );
	Follow[otherstmts] = addSymbolToList( Follow[otherstmts], TK_ELSE );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_ID );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_ENDWHILE );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_WHILE );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_IF );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_ENDIF );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_READ );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_WRITE );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_SQL );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_CALL );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_RETURN );
	Follow[stmt] = addSymbolToList( Follow[stmt], TK_ELSE );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_ID );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_WHILE );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_IF );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_READ );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_WRITE );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_SQL );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_CALL );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_RETURN );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_ENDIF );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_ENDWHILE );
	Follow[assignmentstmt] = addSymbolToList( Follow[assignmentstmt], TK_ELSE );
	Follow[singleorrecid] = addSymbolToList( Follow[singleorrecid], TK_ASSIGNOP );
	Follow[singleorrecid] = addSymbolToList( Follow[singleorrecid], TK_CL );
	Follow[singleorrecid_] = addSymbolToList( Follow[singleorrecid_], TK_ASSIGNOP );	
	Follow[singleorrecid_] = addSymbolToList( Follow[singleorrecid_], TK_CL );	
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_ID );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_WHILE );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_IF );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_READ );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_WRITE );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_SQL );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_CALL );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_RETURN );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_ENDIF );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_ENDWHILE );
	Follow[funcallstmt] = addSymbolToList( Follow[funcallstmt], TK_ELSE );
	Follow[outputparameters] = addSymbolToList( Follow[outputparameters], TK_CALL );
	Follow[inputparameters] = addSymbolToList( Follow[inputparameters], TK_SEM );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_ID );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_WHILE );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_IF );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_READ );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_WRITE );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_SQL );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_CALL );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_RETURN );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_ENDIF );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_ENDWHILE );
	Follow[iterativestmt] = addSymbolToList( Follow[iterativestmt], TK_ELSE );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_ID );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_WHILE );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_IF );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_READ );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_WRITE );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_SQL );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_CALL );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_RETURN );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_ENDIF );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_ENDWHILE );
	Follow[conditionalstmt] = addSymbolToList( Follow[conditionalstmt], TK_ELSE );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_ID );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_WHILE );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_IF );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_READ );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_WRITE );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_SQL );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_CALL );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_RETURN );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_ENDIF );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_ENDWHILE );
	Follow[elsepart] = addSymbolToList( Follow[elsepart], TK_ELSE );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_ID );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_WHILE );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_IF );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_READ );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_WRITE );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_SQL );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_CALL );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_RETURN );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_ENDIF );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_ENDWHILE );
	Follow[iostmt] = addSymbolToList( Follow[iostmt], TK_ELSE );
	Follow[allvar] = addSymbolToList( Follow[allvar], TK_CL );
	Follow[arithmeticexpression] = addSymbolToList( Follow[arithmeticexpression], TK_SEM );
	Follow[arithmeticexpression] = addSymbolToList( Follow[arithmeticexpression], TK_CL );
	Follow[innerterm] = addSymbolToList( Follow[innerterm], TK_SEM );
	Follow[innerterm] = addSymbolToList( Follow[innerterm], TK_CL );
	Follow[term] = addSymbolToList( Follow[term], TK_PLUS );
	Follow[term] = addSymbolToList( Follow[term], TK_MINUS );
	Follow[term] = addSymbolToList( Follow[term], TK_SEM );
	Follow[term] = addSymbolToList( Follow[term], TK_CL );
	Follow[termprime] = addSymbolToList( Follow[termprime], TK_PLUS );
	Follow[termprime] = addSymbolToList( Follow[termprime], TK_MINUS );
	Follow[termprime] = addSymbolToList( Follow[termprime], TK_SEM );
	Follow[muldiv] = addSymbolToList( Follow[muldiv], TK_OP );
	Follow[muldiv] = addSymbolToList( Follow[muldiv], TK_RNUM );
	Follow[muldiv] = addSymbolToList( Follow[muldiv], TK_NUM );
	Follow[muldiv] = addSymbolToList( Follow[muldiv], TK_ID );
	Follow[muldiv] = addSymbolToList( Follow[muldiv], TK_RECORDID );
	Follow[plusminus] = addSymbolToList( Follow[plusminus], TK_OP );
	Follow[plusminus] = addSymbolToList( Follow[plusminus], TK_RNUM );
	Follow[plusminus] = addSymbolToList( Follow[plusminus], TK_NUM );
	Follow[plusminus] = addSymbolToList( Follow[plusminus], TK_ID );
	Follow[plusminus] = addSymbolToList( Follow[plusminus], TK_RECORDID );
	Follow[factor] = addSymbolToList( Follow[factor], TK_MUL );
	Follow[factor] = addSymbolToList( Follow[factor], TK_DIV );
	Follow[factor] = addSymbolToList( Follow[factor], TK_PLUS );
	Follow[factor] = addSymbolToList( Follow[factor], TK_MINUS );
	Follow[factor] = addSymbolToList( Follow[factor], TK_SEM );
	Follow[factor] = addSymbolToList( Follow[factor], TK_CL );
	Follow[all] = addSymbolToList( Follow[all], TK_MUL );
	Follow[all] = addSymbolToList( Follow[all], TK_DIV );
	Follow[all] = addSymbolToList( Follow[all], TK_PLUS );
	Follow[all] = addSymbolToList( Follow[all], TK_MINUS );
	Follow[all] = addSymbolToList( Follow[all], TK_SEM );
	Follow[all] = addSymbolToList( Follow[all], TK_CL );
	Follow[booleanexpression] = addSymbolToList( Follow[booleanexpression], TK_CL );
	Follow[var] = addSymbolToList( Follow[var], TK_LT );
	Follow[var] = addSymbolToList( Follow[var], TK_LE );
	Follow[var] = addSymbolToList( Follow[var], TK_EQ );
	Follow[var] = addSymbolToList( Follow[var], TK_GT );
	Follow[var] = addSymbolToList( Follow[var], TK_GE );
	Follow[var] = addSymbolToList( Follow[var], TK_NE );
	Follow[var] = addSymbolToList( Follow[var], TK_CL );
	Follow[logicalop] = addSymbolToList( Follow[logicalop], TK_OP );
	Follow[relationalop] = addSymbolToList( Follow[relationalop], TK_ID );
	Follow[relationalop] = addSymbolToList( Follow[relationalop], TK_NUM );
	Follow[relationalop] = addSymbolToList( Follow[relationalop], TK_RNUM );
	Follow[returnstmt] = addSymbolToList( Follow[returnstmt], TK_END );
	Follow[optionalreturn] = addSymbolToList( Follow[optionalreturn], TK_SEM );
	Follow[idlist] = addSymbolToList( Follow[idlist], TK_SQR );
	Follow[more_ids] = addSymbolToList( Follow[more_ids], TK_SQR );
	
	return Follow;
}

/*to add another symbol to a linked list. The linked list may correspond to a terminal or a non-terminal*/
listNode *  addSymbolToList( listNode * node, symbol s)
{
	if( node == NULL )
	{
		node = getListNodeMemory();
		node->s = s;
		node->next = NULL;
	}
	else
	{
		listNode * head = node;
		while( head->next != NULL )
		{
			head = head->next;
		}
		//node->next = getListNodeMemory();
		//node->next->s = s;
		//node->next->next = NULL;
		listNode * newNode = getListNodeMemory();
		newNode->s = s;
		newNode->next = NULL;
		head->next = newNode;
	}
	return node;
}

/*add multiple symbols of a list to the given list */
listNode *  addSymbolsToList( listNode * newList, listNode * symbolList)
{
	listNode * head = symbolList;

	while( head != NULL )
	{
		newList = addSymbolToList( newList, head->s );
		head = head->next;
	}
	return newList;
}

/*function that returns the first of Alpha, where A->alpha, is any production*/
/*node is the starting of the production rule*/
listNode *  getFirstOfAlpha( listNode * node, listNode ** First , listNode ** Follow  )
{
	listNode * newList = NULL;
	listNode * head = node;
	if( isATerminal( head->s ) )
	{
		//newList = getListNodeMemory();
		newList = addSymbolToList( newList, head->s );
		//newList->
		//printf("Is a terminal\n");
		return newList;
	}

	/*Incase the first symbol in the production rule is a non terminal*/
	head = node;
	while( head != NULL )
	{
		newList = addSymbolsToList( newList, First[head->s] );
		if( containsEpsilon( First[head->s] ) )
		{
			head = head->next;
		}
		else
		{
			break;
		}
	}
	return newList;
}

/*check if a list contains Epsilon*/
int containsEpsilon( listNode * node )
{
	/*redundant check. Not required. If the if condition here is true, there is some error!*/

	listNode * head = node;
	if( head == NULL )
		return 0;

	while( head != NULL )
	{
		if( head->s == TK_EPS )
		{
			return 1;
		}
		head = head->next;
	}
	return 0;
}

/*to check if a symbol is a terminal*/
int isATerminal(symbol s)
{
	if( s >= TK_ASSIGNOP && s <= TK_WRITE )
	{
		return 1;
	}
	return 0;
}

/*to check if a symbol is a non-terminal*/
int isANonTerminal(symbol s)
{
	if( s <= var )
	{
		return 1;
	}
	return 0;
}


/*to check if the symbol is contained in the linked list*/
int checkIfListContainsSymbol(listNode * node, symbol s)
{
	listNode * head = node;
	if( head == NULL )
	{
		return 0;
	}
	else
	{
		while( head != NULL )
		{
			if( head->s == s )	
				return 1;
			head = head->next;
		}
		return 0;
	}
}

/*to get the size of the list*/
int getSizeList( listNode * list )
{
	listNode * head = list;
	if( head == NULL )
		return 0;

	return 1 + getSizeList(head->next);
}

/*epsilon node, since parse table contains an epsilon node too*/
listNode * getEpsilonNode(listNode * epsilonNode)
{
	epsilonNode = getListNodeMemory();
	epsilonNode->s = TK_EPS;
	epsilonNode->next = NULL;
	return epsilonNode;
}

/*
void createParseTable(grammar G, table T): 

This function takes as input the grammar G, uses FIRST and FOLLOW information to populate  the table T appropriately. 
*/
void createParseTable(grammar GG, table TT)
{
	//printf("I am here 1\n");
	/*If I have the grammar here, where do I pupulate it?*/
	grammarNode** G;
	G = populateGrammar(G);
	*GG = G;

	/*data structure to hold first and follow sets */
	listNode ** First;
	listNode ** Follow;

	/*populating first and follow sets*/
	First = populateFirst( First );
	Follow = populateFollow( Follow );
	
	//printf("Sample list node print\n");
	//printListNode( Follow[program] );
	
	/*get epsilonNode, since this can also be a part of the parse Table*/
	listNode * epsilonNode;
	epsilonNode = getEpsilonNode(epsilonNode);

	int tableRows = NUMBER_OF_NONTERMINALS;
	//int tableColumns = NUMBER_OF_TERMINALS + 1;	/* plus 1 for the dollar sign*/
	int tableColumns = TK_WRITE + 1;	/* plus 1 for the dollar sign*/
	
	listNode *** T = (listNode***)malloc(tableRows * sizeof( listNode ** ));
    	/*can experiment here a little with dereferencing*/
	
	int i,j;
	for( i=0; i<tableRows ; i++)
	{
         	T[i] = ( listNode** )malloc(tableColumns * sizeof( listNode* ));
 	}
	
	/*make all entries of the table as NULL*/
	for( i=0; i<tableRows ; i++)
	{
		for( j=0; j<tableColumns ; j++)
		{
         		T[i][j] = NULL;
		}
 	}

	*TT = T;
	/*DRY RUN - CHECK*/

	int rulesadded = 0;
	for(  i=all; i<=var ; i++)
	{
		/*for the ith non-terminal*/
		//int numberOfRules = sizeof(G[i]->list)/sizeof(G[i]->list[0]);
		int numberOfRules = G[i]->numberOfRules;

		//printf("Number of rules : %d\n", numberOfRules);

		/*for each production rule*/
		for( j=0; j<numberOfRules ; j++)
		{
			listNode * first = NULL;
			listNode * temporary;

			first = getFirstOfAlpha( G[i]->list[j] , First, Follow );
			temporary = first;

			//printf("The rule is %s -> ",tokenNameFromSymbol(i) );
			//printListNode( G[i]->list[j] );
			//printf("First set is : ");
			//printListNode( temp );
			//printf("\n");
			/*for each terminal t that belongs to First(alpha), do T[A,t] = alpha*/ 
			while(temporary != NULL)
			{
				/*check for null condition, if violated, there is error*/
				/*see if there has to be a row for epsilon*/
				//printf("Non terminal : %s,Temporary->s = %s\n",tokenNameFromSymbol(i), tokenNameFromSymbol( temporary->s ));	
				if( temporary->s == TK_EPS )
				{
					temporary = temporary->next;
					continue;
				}				

				if( T[i][temporary->s] != NULL )
				{
					//printf("The already entry is :");
					//printListNode( T[i][temporary->s] );
					//printf("\n");
					//printf("ERORRRRRRRRRRRRRRRRRRRRRR!!!!!\n");
				}
				/*addition of epsilon nodes*/
				rulesadded++;
				T[i][temporary->s] = G[i]->list[j];
				temporary = temporary->next;
			}
			
			/*if epsilon belongs to First(alpha), for each terminal t belongs to Follow(A), do, T[A,t] = alpha*/
			temporary = first;
			if( containsEpsilon( temporary ) )
			{
				listNode * followA = Follow[i];
				listNode * temporary1 = followA;

				while(temporary1 != NULL)
				{
					/*check for null condition, if voilated, there is error*/
					if( T[i][temporary1->s] != NULL )
					{	
						//printf("The already entry is :");
						//printListNode( T[i][temporary->s] );
						//printf("\n");
						//printf("ERORRRRRRRRRRRRRRRRRRRRRR!!!!!\n");
					}
					T[i][temporary1->s] = G[i]->list[j];
					rulesadded++;
					temporary1 = temporary1->next;
				}	
			}
			temporary = first;
			if( containsEpsilon( temporary ) && checkIfListContainsSymbol( Follow[i] , TK_DOLLAR) )
			{
				T[i][TK_DOLLAR] = G[i]->list[j];
				rulesadded++;
				
			}
			
			/*complete populating the table*/
			/*add epsilon nodes to the table. Parsing works well*/
		}
	}
	T[termprime][TK_CL] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_SEM] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_MINUS] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_PLUS] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_MUL] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_DIV] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_LT] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_LE] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_GE] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_GT] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_NE] = G[otherfunctions]->list[1];
	T[singleorrecid_][TK_EQ] = G[otherfunctions]->list[1];
	
	//printf("Rules added : %d\n", rulesadded); 
	/*parse table is printed - works*/
	/*for( i=0; i<tableRows ; i++)
	{
		for( j=0; j<tableColumns ; j++)
		{
			if( T[i][j] != NULL )
			{
				printf("Printing list node [%d,%d]", i,j);
         			printListNode( T[i][j] );
			}
		}
 	}*/
	/*see if the function should modify pointer or return the modified pointer as well!!*/
}

/*------------------------------- stack functions for predictive parsing -------------------------------*/

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

int stackTop(struct stackNode * head)
{
	/*check if this condition arises*/
	if( head == NULL )
		return -1;

	int stackTop = head->s;		

	return stackTop;
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
		printf("%s  ",tokenNameFromSymbol(temp->s));
		temp = temp->next;
	}
	printf("\n");
}

/*-------------------------------------------------------------------------------*/ 

struct stackNode * addToStack( struct stackNode * stack, listNode * list )
{
	/*not very efficient coding, try making it double linked*/
	
	symbol symbols[25];
		
	listNode * head = list;
	int index = 0;

	while( head != NULL )
	{
		symbols[index++] = head->s;
		head = head->next;
	}

	index--;

	while( index >= 0 )
	{
		if( symbols[index] == TK_EPS )
		{
			index--;
			continue;
		}
		stack = push( stack, symbols[index--] );
	}
	return stack;
}
/*

parseTree  parseInputSourceCode(char *testcaseFile, table T): 

This function takes as input the source code file and parses using the rules as per the predictive parse table T. The function gets the tokens using lexical analysis interface and establishes the syntactic structure of the input source code using rules in T. The function must report errors as per the list of error specifications (will be provided to you soon) if the source code is syntactically incorrect. If the source code is correct then the token and all its relevant information is added to the parse tree. The start symbol of the grammar is the root of the parse tree and the tree grows as the syntax analysis moves in top down way. The function must display a message " Compiled Successfully: Input source code is syntactically correct!!" for successful parsing.

*/

/*add a token to token list*/
tokenInfoNode * addTokenToList( tokenInfoNode * tokens, tokenInfo t)
{
	if( tokens == NULL )
	{
		tokens = ( tokenInfoNode * )malloc( sizeof( tokenInfoNode ));
		tokens->t = t;
		tokens->next = NULL;
	}
	else
	{
		tokenInfoNode * head = tokens;
		while( head->next != NULL )
		{
			head = head->next;
		}
		
		tokenInfoNode * newNode = ( tokenInfoNode * )malloc( sizeof( tokenInfoNode ));
		newNode->t = t;
		newNode->next = NULL;
		head->next = newNode;
	}
	return tokens;
}

/*get size of a list*/
int getSizeOfTokenList( tokenInfoNode * tokens )
{
	if( tokens == NULL )
		return 0;

	return 1 + getSizeOfTokenList( tokens->next );
}

/*print ListNode */
void printListNode(listNode * head)
{
	listNode * temp = head;
	while( temp )
	{
		printf("%s  ",tokenNameFromSymbol(temp->s));
		//printf("%s  ",mapping(temp->s));
		temp = temp->next;
	}
	printf("\n");
}

parseTree parseInputSourceCode(char *testcaseFile, table T)
{
	//parseTree PT = NULL;
	struct stackNode * stack;
	symbol nextToken;

	/*get the stream of tokens*/

	FILE * fp = fopen(testcaseFile, "r");
	
	//if ( fp )
	//{
	///	printf("File pointer not null!\n");
	//}

	tokenInfoNode * tokens = NULL;
	tokenInfo t;
	
	t.s = -1;
	while( t.s != TK_END )
	{
		t = getNextToken(fp);
		//printf("Lexeme Information ------- %s Line : %d TokenID %d\n",t.lexeme,t.lineNum, t.s);
		tokens = addTokenToList( tokens, t );
	}

	int numberOfTokens = getSizeOfTokenList( tokens );

	//printf("Number of tokens : %d\n", numberOfTokens);
	tokenInfo tokenArray[ numberOfTokens + 1 ];

	tokenInfoNode * head = tokens;

	int i = 0;
	while( head != NULL)
	{
		//printf("Currently at %d\n",(head->t).s);
		tokenArray[ i ] = head->t;
		head = head->next;
		i++;
	}

	/*for( i=0; i<numberOfTokens; i++)
	{
		printf("%s ",tokenNameFromSymbol(tokenArray[i].s));
	}printf("\n");*/

	t.s = TK_DOLLAR;
	strcpy( t.lexeme, "$");
	tokenArray[ numberOfTokens ] = t;
	
	stack = createStack( stack );

	stack = push( stack, TK_DOLLAR );
	stack = push( stack, program );

	//printf("Print stack :");
	//print(stack);

	int next = 0;

	parseTree pTree = NULL;
	pTree = addToTree( program, NULL, NULL, pTree); 

	/*parsing with stack works. create parse tree*/
	//FILE * fp = fopen("TestStack.txt","w");
	while( !empty( stack ) )
	{
		symbol st;
		//stack = pop( stack, &stackTop );
		//nextToken = 
		st = stackTop( stack );
		//printf("Stack top is : %s\n", tokenNameFromSymbol(st));

		//printf("Stack is : ");
	
		//print( stack );

		//printf("Next symbol is : %s\n",tokenNameFromSymbol(tokenArray[next].s));

		/*if( st == TK_EPS )
		{
			symbol temp;
			stack = pop( stack, &temp);
			continue;
		}*/

		if( st == TK_END )
			break;
		if( isANonTerminal( st ) )
		{
			listNode * list = T[st][ tokenArray[next].s ];

			//printf("Printing list : ");
			//printListNode( list );
			if( list != NULL )
			{
				symbol temp;
				stack = pop( stack, &temp);
				stack = addToStack( stack, list );
			}
			
			else 
			{
				//printf("List is null for Stacktop : %d, Symbol : %d\n",stackTop,tokenArray[next].s);
				//printf("List is null for Stacktop : %s, Symbol : %s\n",tokenNameFromSymbol(stackTop),tokenNameFromSymbol(tokenArray[next].s));
				/*raise parse error*/			
				printf("Parse error!!!!!!!!!!!!!");

			}	

			addToTree( st, tokenArray + next, list, pTree );
		}
		if( isATerminal( st ) )	/*stack top is a terminal*/
		{
			//printf("Terminal : %s\n",tokenNameFromSymbol(tokenArray[next].s));
			if( st == tokenArray[next++].s )
			{
				/*already popped the top stack symbol*/
				/*move to the next token*/
				symbol temp;
				stack = pop( stack, &temp);
			}
			else
			{
				/*raise parse error*/
				printf("Parsing error!\n");

			}
			addToTree( st, tokenArray + next - 1, NULL, pTree );	
		}
		
	}
	fclose(fp);	

	//fp = fopen("parsetree.txt","w");
		
	//dfs(pTree, fp );

	//AST( pTree );
	
	//printf("After\n");
		
	//dfs(pTree, fp );
	//fclose(fp);
	return pTree;	
}


void printParseTree(parseTree  PT, char *outfile)
{
	FILE * fp = fopen(outfile,"w");
	dfs( PT, fp );
}
/*

void printParseTree(parseTree  PT, char *outfile): 

function provides an interface for observing the correctness of the creation of parse tree. The function prints the parse tree in depth first order in the file outfile. The output is such that each line of the file outfile must contain the information corresponding to the currently  visited node of the parse tree in the following format 

             lexemeCurrentNode     lineno   token   valueIfNumber   parentNodeSymbol   isLeafNode(yes/no)    NodeSymbol

    The lexeme of the current node is printed when it is the leaf node else a dummy string of characters "----" is printed. The line number is the information collected by the lexical analyzer during single pass of the source code. The token name corresponding to the current node is printed third. If the lexeme is an integer or real number, then its value computed by the lexical analyzer should be printed at the fourth place. Print the grammar symbol (non terminal symbol) of the parent node of the currently visited node appropriately at fifth place (for the root node  print ROOT for parent symbol) . The sixth column is for printing yes or no appropriately. Print the nonterminal symbol of the node being currently visited at the 7th place, if the node is not the leaf node [Print the actual nonterminal symbol and not the enumerated values for the nonterminal]. Ensure appropriate justification so that the columns appear neat and straight.*/

