#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

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

tokenInfo  getNextToken( FILE *fp)
{

	int k = 40;
	buffer B;
	int i = 0;

	/*providing memory to the buffer*/
	B = malloc( sizeof(char) * k );

	/*static lineNum = 0; /*line num info to be updated*/ 
	fp = getStream(fp, B, k);

	/*keeping the buffer length*/
	int buffLen = 0;
	while( B[i] != '\0')
	{
		buffLen++;
		i++;
	}
	
	/*analyse the stream in the buffer*/

	/*this will create symbol table everytime this function is called. FInd solution for only once!*/
	struct node * STroot = NULL;
	STroot = populateSymbolTable(STroot);

	i = 0;
	while( B[i] != '\0' )	/*do i put <k condition?*/
	{
		
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
			/*go back to the start of the buffer*/
			fseek(fp,-buffLen, SEEK_CUR); 

			/*go to the end of the comment*/
			fseek(fp,i, SEEK_CUR);

			/*move one step ahead*/
			fseek(fp,1, SEEK_CUR);

			fp = getStream(fp, B, k);		
			i = 0;
		}

		/*ignore whitespaces*/
		else if( isWhiteSpace(B[i]) )
		{
			while( B[i] != '\0' && isWhiteSpace(B[i]) )
				i++;

			/*update file pointer and get another batch of stream*/

			/*buffer full of only whitespaces*/
			if( B[i] == '\0' )	
			{
				fp = getStream(fp, B, k);
				i = 0;
				continue;
			}

			/*go back to the start of the buffer*/
			fseek(fp,-buffLen, SEEK_CUR); 

			/*go to the end of the comment*/
			fseek(fp,i, SEEK_CUR);

			fp = getStream(fp, B, k);		
			i = 0;
		}

		else
		{
			int n = 1;
			char temp[45];
			char lexeme[45] = "";

			strncpy( temp, B, n );
			strcpy( lexeme, temp );	

			int ifALexeme = checkForLexeme(temp, STroot);
			
			while( i+n < minimum(30,buffLen) )	/*since maximum length of an identifier is 30*/
			{
				n++;
				/*whitespace issue?*/

				strncpy( temp, B, n );	
				/*lookahead*/
				if( !checkForLexeme(temp, STroot) && checkForLexeme(lexeme, STroot) )
				{
					break;	
				}
				else
				{
					strcpy( lexeme, temp );	
				}

				/* buffer overflow to check for lexeme should not occur, cause we are updating the filepointer too*/
			}

			if( i+n == minimum(30,buffLen) )
			{
				/*unidentified lexeme. ERROR!! */
			}

			/*collect lexeme info*/
			/*break the loop*/
		}
	}

	tokenInfo t;
	return t;
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
int checkForLexeme( char temp[45], struct node * STRoot )
{
	if( search(STRoot, temp ) == 1 )
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
	
/*---------------------------BST - Symbol Table---------------------------*/

struct node * insert(struct node * x, char * value, symbol s)
{
	if( x == NULL )
	{	
		x = (struct node *)malloc(sizeof(struct node));
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
int search(struct node * root, char * value)
{
	if( root == NULL )
	{	
		return 0;
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
void inorder(struct node * root )
{
	if( root == NULL )
		return;

	inorder(root->left);
	//cout << root->value << " ";
	printf("%s ",root->value);
	inorder(root->right);
}
struct node * min(struct node * x) 
{ 
        if (x->left == NULL) 
		return x; 
        else                
		return min(x->left); 
} 
struct node * deleteMin(struct node * x) 
{
        if (x->left == NULL) 
		return x->right;
        x->left = deleteMin(x->left);
        return x;
}
struct node * del(struct node * x, char * key) 
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
            	struct node * t = x;
            	x = min(t->right);
            	x->right = deleteMin(t->right);
            	x->left = t->left;
        } 
        return x;
} 	
int height(struct node* node)
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
void printGivenLevel(struct node* root, int level)
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
void printLevelOrder(struct node* root)
{
  	int h = height(root);
  	int i;
  	for(i=1; i<=h; i++)
    	{
		printGivenLevel(root, i);
		printf("\n");
	}
}     

struct node * populateSymbolTable(struct node * root)
{
	root = insert(root, "<--",TK_ASSIGNOP);
	root = insert(root, "%",TK_COMMENT);
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
