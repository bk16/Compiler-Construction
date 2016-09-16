
#ifndef LEXERDEF_H_
#define LEXERDEF_H_

#define buffer char*
#define buffersize int

/*addition of the dollar symbol at the end?*/
/* TK_DOLLAR added by me*/
typedef enum
{
	all,
	allvar,
	arithmeticexpression,
	assignmentstmt,
	booleanexpression, 
	conditionalstmt,
	constructeddatatype,
	datatype,
	declaration,
	declarations,
	elsepart,
	factor,
	fielddefinition,
	fielddefinitions,
	funcallstmt,
	function,
	global_or_not,
	idlist,
	innerterm,
	input_par,
	inputparameters,
	iostmt,
	iterativestmt,
	logicalop,
	mainfunction,
	more_ids,
	morefields,
	muldiv,
	/*operator*/
	optionalreturn, 
	otherfunctions,
	otherstmts,
	output_par,
	outputparameters,
	parameter_list,
	plusminus,
	primitivedatatype,
	program,   
 	relationalop,
	remaining_list,
	returnstmt,
	singleorrecid,
	singleorrecid_,
	stmt,
	stmts,	
	recAdjust,
	term,
	termprime,
	typedefinition,
	typedefinitions, 
	var,   

	TK_ASSIGNOP,
	TK_AND,
	TK_COMMA,
	TK_COLON,
	TK_CALL,
	TK_CL,
	TK_DOT,
	TK_DOLLAR,
	TK_DIV,
	TK_END,
	TK_EPS,	/*see if this needs to be changed*/
	TK_ENDWHILE,
	TK_ELSE,
	TK_ENDIF,
	TK_EQ,
	TK_ENDRECORD,
	TK_FUNID,
	TK_FIELDID,
	TK_GLOBAL,
	TK_GT,
	TK_GE,
	TK_INPUT,
	TK_ID,
	TK_INT,
	TK_IF,
	TK_LIST,
	TK_LT,
	TK_LE,
	TK_MAIN,
	TK_MUL,
	TK_MINUS,
	TK_NUM,
	TK_NOT,
	TK_NE,
	TK_OUTPUT,
	TK_OP,
	TK_OR,
	TK_PARAMETER,
	TK_PARAMETERS,
	TK_PLUS,
	TK_REAL,
	TK_RECORD,
	TK_RECORDID,
	TK_READ,
	TK_RNUM,
	TK_RETURN,
	TK_SEM,
	TK_SQL,
	TK_SQR,
	TK_TYPE,
	TK_THEN,
	TK_WITH,
	TK_WHILE,
	TK_WRITE,
} symbol;

/*node for the BST, which is our simple Symbol Table*/
struct BSTNode
{
	char value[15];
	symbol s;
	struct BSTNode * left;
	struct BSTNode * right;
};

typedef struct TokenInfo
{
	char lexeme[40];	/*or use a pointer and later allocate memory?*/
	int lineNum;
	symbol s;
	/*another field for the token enum, which you may define in the enum or something similar*/
	/*the class even, use a separate enum for it*/
} tokenInfo;

typedef struct TokenInfoNode
{
	tokenInfo t;
	struct TokenInfoNode * next;
} tokenInfoNode;

#endif

