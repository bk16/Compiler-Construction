
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parserDef.h"

char * mapping(symbol s)
{
	char ** symbols = (char ** ) malloc( sizeof(char*) * (NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS) );
	int i;
	for( i=0; i<=NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS; i++)
	{
		symbols[i] = (char *)malloc( sizeof(char) * 20 );
	}	

	strcpy(symbols[TK_NE], "n3");
	strcpy(symbols[TK_COMMA], "c1");
	strcpy(symbols[TK_EPS], "e2");
	strcpy(symbols[TK_DOLLAR], "$1");
	strcpy(symbols[TK_AND], "a2");
	strcpy(symbols[TK_OR], "o3");
	strcpy(symbols[TK_NOT], "n2");
	strcpy(symbols[TK_LT], "l2");
	strcpy(symbols[TK_LE], "l3");
	strcpy(symbols[TK_EQ], "e6");
	strcpy(symbols[TK_GT], "g2");
	strcpy(symbols[TK_GE], "g3");	
	strcpy(symbols[TK_ENDIF], "e5");
	strcpy(symbols[TK_READ], "r4");
	strcpy(symbols[TK_WRITE], "w3");
	strcpy(symbols[TK_DIV], "d2");
	strcpy(symbols[TK_CALL], "c3");
	strcpy(symbols[TK_RECORD], "r2");
	strcpy(symbols[TK_ENDRECORD], "e7");
	strcpy(symbols[TK_ELSE], "e4");	
	strcpy(symbols[TK_RETURN], "r6");
	strcpy(symbols[TK_PLUS], "p3");
	strcpy(symbols[TK_MINUS], "m3");
	strcpy(symbols[TK_MUL], "m2");
	strcpy(symbols[TK_OP], "o2");
	strcpy(symbols[TK_CL], "c4");
	strcpy(symbols[TK_IF], "i4");
	strcpy(symbols[TK_THEN], "t2");	
	strcpy(symbols[TK_SQL], "s2");
	strcpy(symbols[TK_SQR], "s3");
	strcpy(symbols[TK_INPUT], "i1");
	strcpy(symbols[TK_OUTPUT], "o1");
	strcpy(symbols[TK_SEM], "s1");
	strcpy(symbols[TK_COLON], "c2");
	strcpy(symbols[TK_DOT], "d1");
	strcpy(symbols[TK_ENDWHILE], "e3");
	strcpy(symbols[TK_WHILE], "w2");
	strcpy(symbols[TK_INT], "i3");
	strcpy(symbols[TK_REAL], "r1");
	strcpy(symbols[TK_TYPE], "t1");
	strcpy(symbols[TK_MAIN], "m1");
	strcpy(symbols[TK_GLOBAL], "g1");
	strcpy(symbols[TK_PARAMETER], "p1");
	strcpy(symbols[TK_LIST], "l1");	
	strcpy(symbols[TK_NUM], "n1");
	strcpy(symbols[TK_RNUM], "r5");
	strcpy(symbols[TK_FUNID], "f1");
	strcpy(symbols[TK_RECORDID], "r3");
	strcpy(symbols[TK_WITH], "w1");
	strcpy(symbols[TK_PARAMETERS], "p2");
	strcpy(symbols[TK_END], "e1");
	strcpy(symbols[TK_ASSIGNOP], "a1");
	strcpy(symbols[TK_FIELDID], "f2");
	strcpy(symbols[TK_ID], "i2");	
	strcpy(symbols[otherstmts], "O3");
	strcpy(symbols[singleorrecid_], "S4");
	strcpy(symbols[funcallstmt], "F4");
	strcpy(symbols[outputparameters], "O4");
	strcpy(symbols[inputparameters], "I4");
	strcpy(symbols[iterativestmt], "I2");
	strcpy(symbols[conditionalstmt], "C2");
	strcpy(symbols[elsepart], "E2");	
	strcpy(symbols[returnstmt], "R2");
	strcpy(symbols[optionalreturn], "O6");
	strcpy(symbols[idlist], "I5");
	strcpy(symbols[more_ids], "M3");	
	strcpy(symbols[plusminus], "L1");
	strcpy(symbols[all], "A4");
	strcpy(symbols[booleanexpression], "B1");
	strcpy(symbols[var], "V1");
	strcpy(symbols[logicalop], "L2");
	strcpy(symbols[relationalop], "R3");	
	strcpy(symbols[iostmt], "I3");
	strcpy(symbols[allvar], "A3");
	strcpy(symbols[arithmeticexpression], "A2");
	strcpy(symbols[innerterm], "E1");
	strcpy(symbols[term], "T3");
	strcpy(symbols[termprime], "T4");
	strcpy(symbols[factor], "F5");
	strcpy(symbols[muldiv], "H1");	
	strcpy(symbols[morefields], "M2");
	strcpy(symbols[declarations], "D2");
	strcpy(symbols[declaration], "D3");
	strcpy(symbols[global_or_not], "G1");	
	strcpy(symbols[typedefinitions], "T1");
	strcpy(symbols[typedefinition], "T2");
	strcpy(symbols[fielddefinitions], "F2");
	strcpy(symbols[fielddefinition], "F3");	
	strcpy(symbols[program], "P1");
	strcpy(symbols[mainfunction],"M1");
	strcpy(symbols[otherfunctions],"O1");
	strcpy(symbols[function],"F1");
	strcpy(symbols[input_par],"I1");
	strcpy(symbols[output_par], "O2");
	strcpy(symbols[parameter_list], "P2");
	strcpy(symbols[datatype], "D1");
	strcpy(symbols[primitivedatatype], "P3");
	strcpy(symbols[constructeddatatype], "C1");
	strcpy(symbols[remaining_list], "R1");
	strcpy(symbols[stmts], "S1");
	strcpy(symbols[stmt], "S2");
	strcpy(symbols[assignmentstmt], "A1");
	strcpy(symbols[singleorrecid], "S3");
	strcpy(symbols[recAdjust], "T5");
	//strcpy(symbols[operator], "O5");

	return symbols[s];
}
