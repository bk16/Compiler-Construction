#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parserDef.h"

/*

FILE *getStream(FILE *fp, buffer B, buffersize k): 

This function takes the  input from the file pointed to by 'fp'. This file is the source code written in the given language. The function uses efficient technique to bring the fixed sized piece (of size k)  of source code into the buffer B  for processing so as to avoid intensive I/O operations mixed with CPU intensive tasks. The function also maintains the file pointer after every access so that it can get more data into the memory on demand.

*/

FILE * getStream(FILE * fp, buffer B, buffersize k)
{
	/*value of k is 30, i.e. the length of the buffer*/
	int index = 0;
	int c;
	while (((c = fgetc(fp)) != EOF) && index < k)
    	{
		B[index++] = (char) c;
    	}

	B[index] = '\0';
	/* just check index out of bounds once*/

	return fp;
}

/*

tokenInfo  getNextToken( FILE *fp): 

This function reads the input character stream and uses efficient mechanism to recognize lexemes. The function tokenizes the lexeme appropriately and returns all relevant information it collects in this phase (lexical analysis phase) encapsulated as  tokenInfo. The function also displays lexical errors appropriately (list of errors to be uploaded soon). The input parameters are made flexible and students can select appropriate input parameters. The function also takes care of ignoring the white spaces and comments.

*/

/*only issue is with the last token*/
tokenInfo  getNextToken( FILE *fp)
{

	int k = 45;
	buffer B;
	int i = 0;

	/*providing memory to the buffer*/
	B = malloc( sizeof(char) * k );

	static int lineNum = 1; /*line num info to be updated*/ 
	fp = getStream(fp, B, k);

	/*keeping the buffer length*/
	int buffLen = 0;
	while( B[i] != '\0')
	{
		buffLen++;
		i++;
	}
	
	//B[buffLen] = '\0';
	/*analyse the stream in the buffer*/

	/*this will create symbol table everytime this function is called. FInd solution for only once!*/
	struct BSTNode * STroot = NULL;
	STroot = populateSymbolTable(STroot);

	tokenInfo t;

	i = 0;
	while( B[i] != '\0' )	/*do i put <k condition?*/
	{
	
		//printf("Buffer is : %s\n----------\n",B);		

		/*ignore comments*/
		if( B[i] == '%' )
		{
			while( B[i] != '\0' && B[i] != '\n' )
				i++;
			
			/*update file pointer and get another batch of stream?*/

			/*did not encounter change line after seeing % symbol*/
			if( B[i] == '\0' )	
			{
				fp = getStream(fp, B, k);
				i = 0;
				continue;
			}
	
			/*since encountered line number*/
			lineNum++;

			if( feof(fp ) )
			{
				/*go back to the start of the buffer*/
				fseek(fp,-buffLen, SEEK_CUR); 

				/*go to the end of the comment*/
				fseek(fp,i+1, SEEK_CUR);

				//printf("FP at the end\n");
			
			}
			else
			{
				/*go back to the start of the buffer*/
				fseek(fp,-buffLen-1, SEEK_CUR); 

				/*go to the end of the comment*/
				fseek(fp,i+1, SEEK_CUR);
			}

			/*move one step ahead*/
			/*fseek(fp,1, SEEK_CUR);*/

			fp = getStream(fp, B, k);		
			i = 0;
		}

		/*ignore whitespaces*/
		else if( isWhiteSpace(B[i]) )
		{
			
			while( B[i] != '\0' && isWhiteSpace(B[i]) )
			{
				if( B[i] == '\n' )
				{
					lineNum++;
					//printf("I am here\n");
				}

				i++;
			}

			/*update file pointer and get another batch of stream*/

			/*buffer full of only whitespaces*/
			if( B[i] == '\0' )	
			{
				fp = getStream(fp, B, k);
				i = 0;
				continue;
			}

			/*similarly for comments too*/
			if( feof(fp ) )
			{
				/*go back to the start of the buffer*/
				fseek(fp,-buffLen, SEEK_CUR); 

				/*go to the end of the comment*/
				fseek(fp,i, SEEK_CUR);

				//printf("FP at the end\n");
			
			}
			else
			{
				/*go back to the start of the buffer*/
				fseek(fp,-buffLen-1, SEEK_CUR); 

				/*go to the end of the comment*/
				fseek(fp,i, SEEK_CUR);
			}

			fp = getStream(fp, B, k);

			//printf("Buffer after removing whitespace is : %s\n",B);		
			i = 0;
		}

		else
		{
			int n = 0;
			char temp[45];
			char lexeme[45] = "";

			//strncpy( temp, B, n );
			copyNCharacters( temp, B, n );
			strcpy( lexeme, temp );	
			
			while( i+n < minimum(30,buffLen) )	/*since maximum length of an identifier is 30*/
			{
				n++;
				/*whitespace issue?*/

				//strncpy( temp, B, n );
				copyNCharacters( temp, B, n );

				//printf("Temp %s\n",temp);
				//printf("Lexeme %s\n",lexeme);

				//printf("i = %d\n",i);
				//printf("n = %d\n",n);
				//printf("buffLen = %d\n",buffLen);
	
				/*lookahead*/
				/*if( !checkForLexeme(temp, STroot) && checkForLexeme(lexeme, STroot) )
				{
					break;	
				}
				else
				{
					strcpy( lexeme, temp );	
				}*/

				if( checkForLexeme(temp, STroot) )
				{
					strcpy( lexeme, temp );	
				}

				/* buffer overflow to check for lexeme should not occur, cause we are updating the filepointer too*/
			}

			if( strlen(lexeme) == 0 )
			{
				/*unidentified lexeme. ERROR!! */
				printf("Lexical ERROR!!\n");
			}

			/*collect lexeme info*/
		
			strcpy( t.lexeme, lexeme );	
			t.lineNum = lineNum;
			symbol s = getSymbolForLexeme( lexeme, STroot );
			t.s = s;
			
			/*update the file pointer here too*/
			/*go back to the start of the buffer*/
			
			if( feof(fp) )
			{
				//printf("FP at the end\n");
				fseek(fp,-buffLen, SEEK_CUR); 

				fseek(fp,strlen(lexeme) + 1, SEEK_CUR);
			}
			else
			{
				//printf("FP not at the end\n");
				fseek(fp,-buffLen-1, SEEK_CUR); 

				fseek(fp,strlen(lexeme), SEEK_CUR);
			}
			
			return t;
			/*break the loop*/
		}
	}

	return t;
}

/*resizing array*/
void resizeArray(char * temp)
{
	int length = strlen(temp);
	char * newArray = (char *)malloc( sizeof(char) * (2*length) );
	
	int i = 0;
	while( temp[i] != '\0' )
	{
		newArray[i] = temp[i];
		i++;
	}
	newArray[i] = '\0';
	temp = newArray;
}

/*function to create a comment free code*/
char * commentFreeCode( char * testfile )
{
	FILE * fp = fopen(testfile, "r");
	char * code = (char *)malloc( sizeof(char) * (1) );

	int c,i;
	int currentSize = 1;
	i = 0;
	int commentFound = 0;
	while( (c = fgetc(fp)) != EOF )
	{
		
			if( (char)c == '%' )
			{
				commentFound = 1;
				continue;	
			}
			else if( commentFound == 1 && (char)c == '\n' )
			{
				commentFound = 0;
			}
			else if( commentFound == 0 )
			{
				code[i++] = (char)c;
				if(  i == currentSize )
					resizeArray( code );
			}

	}
	//fclose(fp);
	return code;
}

	
		
/*copy n characters of B[] to temp[]*/
void copyNCharacters( char temp[45], char * B, int n)
{
	int k;
	for( k=0; k<n; k++)
		temp[k] = B[k];
			
	temp[k] = '\0';	
}

/*to get the appropriate symbol for the given lexeme*/
symbol getSymbolForLexeme( char lexeme[45], struct BSTNode * STRoot )
{
	symbol s = search(STRoot, lexeme );
	if( s != -1 )
		return s;

	return DFA( lexeme );
}
		
/*function to check for whitespaces. Modification to check line numbers?*/
int isWhiteSpace( char c )
{	
	if( c==' ' || c=='\t' || c=='\n' )
		return 1;
	else
		return 0;
}

/*return the minimum of two numbers*/
int minimum(int a,int b)
{
	return a<b?a:b;
}

/*function to check if the given string is a lexeme*/
int checkForLexeme( char temp[45], struct BSTNode * STRoot )
{
	if( search(STRoot, temp ) != -1 )
		return 1;

	/*check for identifiers and numbers*/
	
	return checkForIdentifiersAndNumbers( temp );
	/*return some other positive values for separate identifiers*/
}

/*DFA to check for identifiers and numbers*/
int DFA(char temp[45])
{

	int ps = 0;
	char c;
	int index = 0;

	while( temp[index] != '\0' )
	{
		c = temp[index];
		
		if( ps == 0 )
		{
			if( c >= '0' && c <= '9')
				ps = 6;
		
			else if( c == '_' )
				ps = 12;
			
			else if( c >= 'b' && c <= 'd' )
				ps = 2;
			
			else if( c == 'a' || (c >= 'e' && c <= 'z') )	
				ps = 1;

			else if( c == '#' )
				ps = 10;

			else
				return 0;
		}
		else if( ps == 1 )	
		{
			if( c >= 'a' && c <= 'z' )
				ps = 1;/*check value of i*/

			else
				return 0;
		}
		else if( ps == 2 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 1;
			
			else if( c >= '2' && c <= '7')
				ps = 3;
			
			else
				return 0;
		}
		else if( ps == 3 )
		{
			if( c >= 'b' && c <= 'd' )
				ps = 4;
			
			else if( c >= '2' && c <= '7')
				ps = 5;
			
			else
				return 0;
		}
		else if( ps == 4 )
		{
			if( c >= 'b' && c <= 'd' )
				ps = 4;	/*check value of i here to confirm length of the identifier*/
			
			else if( c >= '2' && c <= '7')
				ps = 5;/*check value of i*/
			
			else
				return 0;
		}
		else if( ps == 5 )
		{
			if( c >= '2' && c <= '7')
				ps = 5;/*check value of i*/
			else
				return 0;
		}
		else if( ps == 6 )
		{
			if( c >= '0' && c <= '9')
				ps = 6;/*check value of i*/

			else if( c == '.' )
				ps = 7;
			
			else
				return 0;
		}
		else if( ps == 7 )
		{
			if( c >= '0' && c <= '9')
				ps = 8;
			
			else
				return 0;
		}
		else if( ps == 8 )
		{
			if( c >= '0' && c <= '9')
				ps = 9;
		}
		else if( ps == 9 )
		{
			/*accept state*/
			return 0;
		}
		else if( ps == 10 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 11;
			
			else
				return 0;
		}
		else if( ps == 11 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 11;/*check value of i*/
			
			else
				return 0;
		}
		else if( ps == 12 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 13;
			
			else
				return 0;
		}
		else if( ps == 13 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 14;/*check value of i*/

			else if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
			
			else
				return 0;
		}
		else if( ps == 14 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 14;/*check value of i*/

			else if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
			
			else
				return 0;
		}
		else if( ps == 15 )
		{
			if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
			
			else
				return 0;
		}
		index++;
	}

	if( ps == 1 )
		return TK_FIELDID;

	else if( ps == 3 || ps == 4 || ps == 5 )
		return TK_ID;

	else if( ps == 6 )
		return TK_NUM;

	else if( ps == 9 )
		return TK_RNUM;

	else if( ps == 11 )
		return TK_RECORDID;
	
	else if( ps == 13 || ps == 14 || ps == 15 )
		return TK_FUNID;
	
	/*redundant - check!*/	
	return 0;
}

/*function to check for identifiers and numbers*/
int checkForIdentifiersAndNumbers( char temp[45] )
{
	return DFA(temp);
}
	
/*edit the unnecessary functions*/
/*---------------------------BST - Symbol Table---------------------------*/

struct BSTNode * insert(struct BSTNode * x, char * value, symbol s)
{
	if( x == NULL )
	{	
		x = (struct BSTNode *)malloc(sizeof(struct BSTNode));
		strcpy(x->value, value);
		x->s = s;
		x->right = NULL;
		x->left = NULL;
	}
	else
	{
		if( strcmp(x->value, value) > 0 )
		{
			x->left = insert(x->left,value,s);
		}
		else
		{
			x->right = insert(x->right,value,s);
		}
	}
	return x;
}
int search(struct BSTNode * root, char * value)
{
	if( root == NULL )
	{	
		return -1;
	}
	else
	{
		if( strcmp(root->value, value) > 0 )
		{
			return search(root->left,value);
		}
		else if(  strcmp(root->value, value) < 0 )
		{
			return search(root->right,value);
		}
		else
		{
			return root->s;
		}
	}
}
void inorder(struct BSTNode * root )
{
	if( root == NULL )
		return;

	inorder(root->left);
	//cout << root->value << " ";
	printf("%s ",root->value);
	inorder(root->right);
}
struct BSTNode * min(struct BSTNode * x) 
{ 
        if (x->left == NULL) 
		return x; 
        else                
		return min(x->left); 
} 
struct BSTNode * deleteMin(struct BSTNode * x) 
{
        if (x->left == NULL) 
		return x->right;
        x->left = deleteMin(x->left);
        return x;
}
struct BSTNode * del(struct BSTNode * x, char * key) 
{
        if (x == NULL) 
		return NULL;

	if( strcmp(key,x->value) < 0 )
		x->left  = del(x->left,  key);
	else if( strcmp(key,x->value) > 0 ) 
		x->right = del(x->right, key);
        else 
	{ 
            	if (x->right == NULL) 
			return x->left;
            	if (x->left  == NULL) 
			return x->right;
            	struct BSTNode * t = x;
            	x = min(t->right);
            	x->right = deleteMin(t->right);
            	x->left = t->left;
        } 
        return x;
} 	
int height(struct BSTNode* node)
{
   	if (node==NULL)
       		return 0;
   	else
   	{

		int lheight = height(node->left);
     		int rheight = height(node->right);
 
     		if (lheight > rheight)
         		return(lheight+1);
     		else 
			return(rheight+1);
   	}
}
void printGivenLevel(struct BSTNode* root, int level)
{
  	if(root == NULL)
    		return;
  	if(level == 1)
    		printf("%s ", root->value);
  	else if (level > 1)
  	{
    		printGivenLevel(root->left, level-1);
    		printGivenLevel(root->right, level-1);
  	}
}
void printLevelOrder(struct BSTNode* root)
{
  	int h = height(root);
  	int i;
  	for(i=1; i<=h; i++)
    	{
		printGivenLevel(root, i);
		printf("\n");
	}
}     

struct BSTNode * populateSymbolTable(struct BSTNode * root)
{
	root = insert(root, "<---",TK_ASSIGNOP);
	//root = insert(root, "%",TK_COMMENT);
	root = insert(root, "with",TK_WITH);
	root = insert(root, "parameters",TK_PARAMETERS);
	root = insert(root, "end", TK_END);
	root = insert(root, "while",TK_WHILE);
	root = insert(root, "int",TK_INT);
	root = insert(root, "real",TK_REAL);
	root = insert(root, "type",TK_TYPE);
	root = insert(root, "_main",TK_MAIN);
	root = insert(root, "global",TK_GLOBAL);
	root = insert(root, "parameter",TK_PARAMETER);
	root = insert(root, "list",TK_LIST);
	root = insert(root, "[",TK_SQL);
	root = insert(root, "]",TK_SQR);
	root = insert(root, "input",TK_INPUT);
	root = insert(root, "output",TK_OUTPUT);
	root = insert(root, ":",TK_COLON);
	root = insert(root, ";",TK_SEM);
	root = insert(root, ".",TK_DOT);
	root = insert(root, ",",TK_COMMA);
	root = insert(root, "endwhile",TK_ENDWHILE);
	root = insert(root, "(",TK_OP);
	root = insert(root, ")",TK_CL);
	root = insert(root, "if",TK_IF);
	root = insert(root, "then",TK_THEN);
	root = insert(root, "endif",TK_ENDIF);
	root = insert(root, "read",TK_READ);
	root = insert(root, "write",TK_WRITE);
	root = insert(root, "return",TK_RETURN);
	root = insert(root, "+",TK_PLUS);
	root = insert(root, "-",TK_MINUS);
	root = insert(root, "*",TK_MUL);
	root = insert(root, "/",TK_DIV);
	root = insert(root, "call",TK_CALL);
	root = insert(root, "record",TK_RECORD);
	root = insert(root, "endrecord",TK_ENDRECORD);
	root = insert(root, "else",TK_ELSE);
	root = insert(root, "&&&",TK_AND);
	root = insert(root, "@@@",TK_OR);
	root = insert(root, "~",TK_NOT);
	root = insert(root, "<",TK_LT);
	root = insert(root, "<=",TK_LE);
	root = insert(root, "==",TK_EQ);
	root = insert(root, ">",TK_GT);
	root = insert(root, ">=",TK_GE);
	root = insert(root, "!=",TK_NE);
	root = insert(root, "$",TK_DOLLAR);
	
	return root;
}	
/*------------------Above are all symbol table functions------------------*/

/*function to return lexemes from symbol number*/
char * getLexemeFromSymbol( symbol s )
{
	char ** lexemes = (char ** ) malloc( sizeof(char*) * (NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS) );
	int i;
	for( i=0; i<=TK_WRITE; i++)
	{
		lexemes[i] = (char *)malloc( sizeof(char) * 20 );
	}

	for( i=program; i<=more_ids; i++)
	{
		strcpy(lexemes[i], "");
	}
	
	strcpy(lexemes[TK_WITH], "with");
	strcpy(lexemes[TK_AND], "&&&");
	strcpy(lexemes[TK_AND], "a&&&a");
	strcpy(lexemes[TK_MINUS], "-");
	strcpy(lexemes[TK_NE], "!=");
	strcpy(lexemes[TK_COMMA], ",");
	strcpy(lexemes[TK_EPS], "epsilon");
	strcpy(lexemes[TK_DOLLAR], "$");
	//strcpy(lexemes[TK_ERROR], "TK_ERROR");
	strcpy(lexemes[TK_AND], "&&&");
	strcpy(lexemes[TK_OR], "@@@");
	strcpy(lexemes[TK_NOT], "~");
	strcpy(lexemes[TK_LT], "<");
	strcpy(lexemes[TK_LE], "<=");
	strcpy(lexemes[TK_EQ], "==");
	strcpy(lexemes[TK_GT], ">");
	strcpy(lexemes[TK_GE], ">=");	
	strcpy(lexemes[TK_ENDIF], "endif");
	strcpy(lexemes[TK_READ], "read");
	strcpy(lexemes[TK_WRITE], "write");
	strcpy(lexemes[TK_DIV], "/");
	strcpy(lexemes[TK_CALL], "call");
	strcpy(lexemes[TK_RECORD], "record");
	strcpy(lexemes[TK_ENDRECORD], "endrecord");
	strcpy(lexemes[TK_ELSE], "else");	
	strcpy(lexemes[TK_RETURN], "return");
	strcpy(lexemes[TK_PLUS], "+");
	strcpy(lexemes[TK_MINUS], "-");
	strcpy(lexemes[TK_MUL], "*");
	strcpy(lexemes[TK_OP], "(");
	strcpy(lexemes[TK_CL], ")");
	strcpy(lexemes[TK_IF], "if");
	strcpy(lexemes[TK_THEN], "then");	
	strcpy(lexemes[TK_SQL], "[");
	strcpy(lexemes[TK_SQR], "]");
	strcpy(lexemes[TK_INPUT], "input");
	strcpy(lexemes[TK_OUTPUT], "output");
	strcpy(lexemes[TK_SEM], ";");
	strcpy(lexemes[TK_COLON], ":");
	strcpy(lexemes[TK_DOT], ".");
	strcpy(lexemes[TK_ENDWHILE], "endwhile");
	strcpy(lexemes[TK_WHILE], "while");
	strcpy(lexemes[TK_INT], "int");
	strcpy(lexemes[TK_REAL], "real");
	strcpy(lexemes[TK_TYPE], "type");
	strcpy(lexemes[TK_MAIN], "_main");
	strcpy(lexemes[TK_GLOBAL], "global");
	strcpy(lexemes[TK_PARAMETER], "parameter");
	strcpy(lexemes[TK_LIST], "list");	
	strcpy(lexemes[TK_WITH], "with");
	strcpy(lexemes[TK_PARAMETERS], "parameters");
	strcpy(lexemes[TK_END], "end");
	strcpy(lexemes[TK_ASSIGNOP], "<---");
	//strcpy(lexemes[TK_COMMENT], "%");

	return lexemes[s];
}

/*function to return function name from symbol*/
char * tokenNameFromSymbol( symbol s )
{
	char ** symbols = (char ** ) malloc( sizeof(char*) * (NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS) );
	int i;
	for( i=0; i<=NUMBER_OF_NONTERMINALS+NUMBER_OF_TERMINALS; i++)
	{
		symbols[i] = (char *)malloc( sizeof(char) * 20 );
	}
	
	strcpy(symbols[TK_NE], "TK_NE");
	strcpy(symbols[TK_COMMA], "TK_COMMA");
	strcpy(symbols[TK_EPS], "TK_EPS");
	strcpy(symbols[TK_DOLLAR], "TK_DOLLAR");
	strcpy(symbols[TK_AND], "TK_AND");
	strcpy(symbols[TK_OR], "TK_OR");
	strcpy(symbols[TK_NOT], "TK_NOT");
	strcpy(symbols[TK_LT], "TK_LT");
	strcpy(symbols[TK_LE], "TK_LE");
	strcpy(symbols[TK_EQ], "TK_EQ");
	strcpy(symbols[TK_GT], "TK_GT");
	strcpy(symbols[TK_GE], "TK_GE");	
	strcpy(symbols[TK_ENDIF], "TK_ENDIF");
	strcpy(symbols[TK_READ], "TK_READ");
	strcpy(symbols[TK_WRITE], "TK_WRITE");
	strcpy(symbols[TK_DIV], "TK_DIV");
	strcpy(symbols[TK_CALL], "TK_CALL");
	strcpy(symbols[TK_RECORD], "TK_RECORD");
	strcpy(symbols[TK_ENDRECORD], "TK_ENDRECORD");
	strcpy(symbols[TK_ELSE], "TK_ELSE");	
	strcpy(symbols[TK_RETURN], "TK_RETURN");
	strcpy(symbols[TK_PLUS], "TK_PLUS");
	strcpy(symbols[TK_MINUS], "TK_MINUS");
	strcpy(symbols[TK_MUL], "TK_MUL");
	strcpy(symbols[TK_OP], "TK_OP");
	strcpy(symbols[TK_CL], "TK_CL");
	strcpy(symbols[TK_IF], "TK_IF");
	strcpy(symbols[TK_THEN], "TK_THEN");	
	strcpy(symbols[TK_SQL], "TK_SQL");
	strcpy(symbols[TK_SQR], "TK_SQR");
	strcpy(symbols[TK_INPUT], "TK_INPUT");
	strcpy(symbols[TK_OUTPUT], "TK_OUPUT");
	strcpy(symbols[TK_SEM], "TK_SEM");
	strcpy(symbols[TK_COLON], "TK_COLON");
	strcpy(symbols[TK_DOT], "TK_DOT");
	strcpy(symbols[TK_ENDWHILE], "TK_ENDWHILE");
	strcpy(symbols[TK_WHILE], "TK_WHILE");
	strcpy(symbols[TK_INT], "TK_INT");
	strcpy(symbols[TK_REAL], "TK_REAL");
	strcpy(symbols[TK_TYPE], "TK_TYPE");
	strcpy(symbols[TK_MAIN], "TK_MAIN");
	strcpy(symbols[TK_GLOBAL], "TK_GLOBAL");
	strcpy(symbols[TK_PARAMETER], "TK_PARAMETER");
	strcpy(symbols[TK_LIST], "TK_LIST");	
	strcpy(symbols[TK_NUM], "TK_NUM");
	strcpy(symbols[TK_RNUM], "TK_RNUM");
	strcpy(symbols[TK_FUNID], "TK_FUNID");
	strcpy(symbols[TK_RECORDID], "TK_RECORDID");
	strcpy(symbols[TK_WITH], "TK_WITH");
	strcpy(symbols[TK_PARAMETERS], "TK_PARAMETERS");
	strcpy(symbols[TK_END], "TK_END");
	strcpy(symbols[TK_ASSIGNOP], "TK_ASSIGNOP");
	strcpy(symbols[TK_FIELDID], "TK_FIELDID");
	strcpy(symbols[TK_ID], "TK_ID");	
	strcpy(symbols[otherstmts], "otherstmts");
	strcpy(symbols[singleorrecid_], "singleorrecid_");
	strcpy(symbols[funcallstmt], "funcallstmt");
	strcpy(symbols[outputparameters], "outputparameters");
	strcpy(symbols[inputparameters], "inputparameters");
	strcpy(symbols[iterativestmt], "iterativestmt");
	strcpy(symbols[conditionalstmt], "conditionalstmt");
	strcpy(symbols[elsepart], "elsepart");	
	strcpy(symbols[returnstmt], "returnstmt");
	strcpy(symbols[optionalreturn], "optionalreturn");
	strcpy(symbols[idlist], "idlist");
	strcpy(symbols[more_ids], "more_ids");	
	strcpy(symbols[plusminus], "plusminus");
	strcpy(symbols[all], "all");
	strcpy(symbols[booleanexpression], "booleanexpression");
	strcpy(symbols[var], "var");
	strcpy(symbols[logicalop], "logicalop");
	strcpy(symbols[relationalop], "relationalop");	
	strcpy(symbols[iostmt], "iostmt");
	strcpy(symbols[allvar], "allvar");
	strcpy(symbols[arithmeticexpression], "arithmeticexpression");
	strcpy(symbols[innerterm], "innerterm");
	strcpy(symbols[term], "term");
	strcpy(symbols[termprime], "termprime");
	strcpy(symbols[factor], "factor");
	strcpy(symbols[muldiv], "muldiv");	
	strcpy(symbols[morefields], "morefields");
	strcpy(symbols[declarations], "declarations");
	strcpy(symbols[declaration], "declaration");
	strcpy(symbols[global_or_not], "global_or_not");	
	strcpy(symbols[typedefinitions], "typedefinitions");
	strcpy(symbols[typedefinition], "typedefinition");
	strcpy(symbols[fielddefinitions], "fielddefinitions");
	strcpy(symbols[fielddefinition], "fielddefinition");	
	strcpy(symbols[program], "program");
	strcpy(symbols[mainfunction],"mainfunction");
	strcpy(symbols[otherfunctions],"otherfunctions");
	strcpy(symbols[function],"function");
	strcpy(symbols[input_par],"input_par");
	strcpy(symbols[output_par], "output_par");
	strcpy(symbols[parameter_list], "parameter_list");
	strcpy(symbols[datatype], "datatype");
	strcpy(symbols[primitivedatatype], "primitivedatatype");
	strcpy(symbols[constructeddatatype], "constructeddatatype");
	strcpy(symbols[remaining_list], "remaining_list");
	strcpy(symbols[stmts], "stmts");
	strcpy(symbols[stmt], "stmt");
	strcpy(symbols[assignmentstmt], "assignmentstmt");
	strcpy(symbols[singleorrecid], "singleorrecid");
	return symbols[s];
}
	
	
