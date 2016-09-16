
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#define NUMBER_OF_GRAMMAR_RULES 91	/*not needed I guess*/
#define NUMBER_OF_NONTERMINALS (more_ids+1)	/*since more_ids is the last non-terminal in the enum list*/
#define NUMBER_OF_TERMINALS (TK_ERROR - more_ids)	/*since TK_ERROR is the last token, and more_ids is the last listed non-terminal*/

void stringCopy( char string[20], char * lexeme)
{
	int i = 0;
	while( lexeme[i] != '\0' )
	{
		string[i] = lexeme[i];
		i++;
	}
	string[i] = '\0';
}

int main(){
	char** complete = (char**)malloc(sizeof(char*) * (NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS));
	int i;
	for(i=0;i<(NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS);i++)
	complete[i]=malloc(100);
	
	
	strcpy(complete[TK_NE], "TK_NE");
	strcpy(complete[TK_COMMA], "TK_COMMA");
	strcpy(complete[TK_EPS], "TK_EPS");
	strcpy(complete[TK_DOLLAR], "TK_DOLLAR");
	strcpy(complete[TK_ERROR], "TK_ERROR");
	strcpy(complete[TK_AND], "TK_AND");
	strcpy(complete[TK_OR], "TK_OR");
	strcpy(complete[TK_NOT], "TK_NOT");
	strcpy(complete[TK_LT], "TK_LT");
	strcpy(complete[TK_LE], "TK_LE");
	strcpy(complete[TK_EQ], "TK_EQ");
	strcpy(complete[TK_GT], "TK_GT");
	strcpy(complete[TK_GE], "TK_GE");	
	strcpy(complete[TK_ENDIF], "TK_ENDIF");
	strcpy(complete[TK_READ], "TK_READ");
	strcpy(complete[TK_WRITE], "TK_WRITE");
	strcpy(complete[TK_DIV], "TK_DIV");
	strcpy(complete[TK_CALL], "TK_CALL");
	strcpy(complete[TK_RECORD], "TK_RECORD");
	strcpy(complete[TK_ENDRECORD], "TK_ENDRECORD");
	strcpy(complete[TK_ELSE], "TK_ELSE");	
	strcpy(complete[TK_RETURN], "TK_RETURN");
	strcpy(complete[TK_PLUS], "TK_PLUS");
	strcpy(complete[TK_MINUS], "TK_MINUS");
	strcpy(complete[TK_MUL], "TK_MUL");
	strcpy(complete[TK_OP], "TK_OP");
	strcpy(complete[TK_CL], "TK_CL");
	strcpy(complete[TK_IF], "TK_IF");
	strcpy(complete[TK_THEN], "TK_THEN");	
	strcpy(complete[TK_SQL], "TK_SQL");
	strcpy(complete[TK_SQR], "TK_SQR");
	strcpy(complete[TK_INPUT], "TK_INPUT");
	strcpy(complete[TK_OUTPUT], "TK_OUPUT");
	strcpy(complete[TK_SEM], "TK_SEM");
	strcpy(complete[TK_COLON], "TK_COLON");
	strcpy(complete[TK_DOT], "TK_DOT");
	strcpy(complete[TK_ENDWHILE], "TK_ENDWHILE");
	strcpy(complete[TK_WHILE], "TK_WHILE");
	strcpy(complete[TK_INT], "TK_INT");
	strcpy(complete[TK_REAL], "TK_REAL");
	strcpy(complete[TK_TYPE], "TK_TYPE");
	strcpy(complete[TK_MAIN], "TK_MAIN");
	strcpy(complete[TK_GLOBAL], "TK_GLOBAL");
	strcpy(complete[TK_PARAMETER], "TK_PARAMETER");
	strcpy(complete[TK_LIST], "TK_LIST");	
	strcpy(complete[TK_NUM], "TK_NUM");
	strcpy(complete[TK_RNUM], "TK_RNUM");
	strcpy(complete[TK_FUNID], "TK_FUNID");
	strcpy(complete[TK_RECORDID], "TK_RECORDID");
	strcpy(complete[TK_WITH], "TK_WITH");
	strcpy(complete[TK_PARAMETERS], "TK_PARAMETERS");
	strcpy(complete[TK_END], "TK_END");
	strcpy(complete[TK_ASSIGNOP], "TK_ASSIGNOP");
	strcpy(complete[TK_COMMENT], "TK_COMMENT");
	strcpy(complete[TK_FIELDID], "TK_FIELDID");
	strcpy(complete[TK_ID], "TK_ID");	
	strcpy(complete[otherstmts], "otherstmts");
	strcpy(complete[newstate], "newstate");
	strcpy(complete[funcallstmt], "funcallstmt");
	strcpy(complete[outputparameters], "outputparameters");
	strcpy(complete[inputparameters], "inputparameters");
	strcpy(complete[iterativestmt], "iterativestmt");
	strcpy(complete[conditionalstmt], "conditionalstmt");
	strcpy(complete[elsepart], "elsepart");	
	strcpy(complete[returnstmt], "returnstmt");
	strcpy(complete[optionalreturn], "optionalreturn");
	strcpy(complete[idlist], "idlist");
	strcpy(complete[more_ids], "more_ids");	
	strcpy(complete[lowprecedenceoperators], "lowprecedenceoperators");
	strcpy(complete[all], "all");
	strcpy(complete[all2], "all2");
	strcpy(complete[temp], "temp");
	strcpy(complete[booleanexpression], "booleanexpression");
	strcpy(complete[var], "var");
	strcpy(complete[logicalop], "logicalop");
	strcpy(complete[relationalop], "relationalop");	
	strcpy(complete[iostmt], "iostmt");
	strcpy(complete[allvar], "allvar");
	strcpy(complete[arithmeticexpression], "arithmeticexpression");
	strcpy(complete[expprime], "expprime");
	strcpy(complete[term], "term");
	strcpy(complete[termprime], "termprime");
	strcpy(complete[factor], "factor");
	strcpy(complete[highprecedenceoperators], "highprecendenceoperators");	
	strcpy(complete[morefields], "morefields");
	strcpy(complete[declarations], "declarations");
	strcpy(complete[declaration], "declaration");
	strcpy(complete[global_or_not], "global_or_not");	
	strcpy(complete[typedefinitions], "typedefinitions");
	strcpy(complete[typedefinition], "typedefinition");
	strcpy(complete[fielddefinitions], "fielddefinitions");
	strcpy(complete[fielddefinition], "fielddefinition");	
	strcpy(complete[program], "program");
	strcpy(complete[mainfunction],"mainfunction");
	strcpy(complete[otherfunctions],"otherfunctions");
	strcpy(complete[function],"function");
	strcpy(complete[input_par],"input_par");
	strcpy(complete[output_par], "output_par");
	strcpy(complete[parameter_list], "parameter_list");
	strcpy(complete[datatype], "datatype");
	strcpy(complete[primitivedatatype], "primitivedatatype");
	strcpy(complete[constructeddatatype], "constructeddatatype");
	strcpy(complete[remaining_list], "remaining_list");
	strcpy(complete[stmts], "stmts");
	strcpy(complete[stmt], "stmt");
	strcpy(complete[assignmentstmt], "assignmentstmt");
	strcpy(complete[singleorrecid], "singleorrecid");
	
	for(i=0;i<(NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS);i++)
	{
		//printf("Lexeme for symbol number %d : %s\n",i,complete[i]);
	}
//		printf("%s\n", complete[i]);
	
	
	char** terminals = (char**)malloc(sizeof(char*) * (NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS));
	//for(i=0;i<(NUMBER_OF_TERMINALS);i++)
	//terminals[i]=malloc(100);

	for( i=0; i<=TK_ERROR; i++)
	{
		terminals[i] = (char *)malloc( sizeof(char) * 20 );
	}


	for( i=program; i<=more_ids; i++)
	{
		strcpy(terminals[i], "");
	}

	

	// wherever in a array, there is a special symbol and not a character error occurs
	
	strcpy(terminals[TK_WITH], "with");/* works fine for this*/
	strcpy(terminals[TK_AND], "&&&");// creates error here
	strcpy(terminals[TK_AND], "a&&&a");// creates error here as well, remove this
	strcpy(terminals[TK_MINUS], "-");//creates error here
	strcpy(terminals[TK_NE], "!=");//creates error here
	
	strcpy(terminals[TK_COMMA], ",");
	strcpy(terminals[TK_EPS], "epsilon");
	strcpy(terminals[TK_DOLLAR], "$");
	strcpy(terminals[TK_ERROR], "TK_ERROR");
	strcpy(terminals[TK_AND], "&&&");
	strcpy(terminals[TK_OR], "@@@");
	strcpy(terminals[TK_NOT], "~");
	strcpy(terminals[TK_LT], "<");
	strcpy(terminals[TK_LE], "<=");
	strcpy(terminals[TK_EQ], "==");
	strcpy(terminals[TK_GT], ">");
	strcpy(terminals[TK_GE], ">=");	
	strcpy(terminals[TK_ENDIF], "endif");
	strcpy(terminals[TK_READ], "read");
	strcpy(terminals[TK_WRITE], "write");
	strcpy(terminals[TK_DIV], "/");
	strcpy(terminals[TK_CALL], "call");
	strcpy(terminals[TK_RECORD], "record");
	strcpy(terminals[TK_ENDRECORD], "endrecord");
	strcpy(terminals[TK_ELSE], "else");	
	strcpy(terminals[TK_RETURN], "return");
	strcpy(terminals[TK_PLUS], "+");
	strcpy(terminals[TK_MINUS], "-");
	strcpy(terminals[TK_MUL], "*");
	strcpy(terminals[TK_OP], "(");
	strcpy(terminals[TK_CL], ")");
	strcpy(terminals[TK_IF], "if");
	strcpy(terminals[TK_THEN], "then");	
	strcpy(terminals[TK_SQL], "[");
	strcpy(terminals[TK_SQR], "]");
	strcpy(terminals[TK_INPUT], "input");
	strcpy(terminals[TK_OUTPUT], "output");
	strcpy(terminals[TK_SEM], ";");
	strcpy(terminals[TK_COLON], ":");
	strcpy(terminals[TK_DOT], ".");
	strcpy(terminals[TK_ENDWHILE], "endwhile");
	strcpy(terminals[TK_WHILE], "while");
	strcpy(terminals[TK_INT], "int");
	strcpy(terminals[TK_REAL], "real");
	strcpy(terminals[TK_TYPE], "type");
	strcpy(terminals[TK_MAIN], "_main");
	strcpy(terminals[TK_GLOBAL], "global");
	strcpy(terminals[TK_PARAMETER], "parameter");
	strcpy(terminals[TK_LIST], "list");	
	strcpy(terminals[TK_WITH], "with");
	strcpy(terminals[TK_PARAMETERS], "parameters");
	strcpy(terminals[TK_END], "end");
	strcpy(terminals[TK_ASSIGNOP], "<---");
	strcpy(terminals[TK_COMMENT], "%");
	
	for(i=TK_ASSIGNOP;i<=TK_ERROR;i++)
	{
		printf("%s\n", terminals[i]);
	}
	
	return 0;
	
}
