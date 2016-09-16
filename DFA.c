
#include <stdio.h>
#include "lexer.h"

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
		}
		else if( ps == 1 )	
		{
			if( c >= 'a' && c <= 'z' )
				ps = 1;/*check value of i*/
		}
		else if( ps == 2 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 1;
			
			else if( c >= '2' && c <= '7')
				ps = 3;
		}
		else if( ps == 3 )
		{
			if( c >= 'b' && c <= 'd' )
				ps = 4;
			
			else if( c >= '2' && c <= '7')
				ps = 5;
		}
		else if( ps == 4 )
		{
			if( c >= 'b' && c <= 'd' )
				ps = 4;	/*check value of i here to confirm length of the identifier*/
			
			else if( c >= '2' && c <= '7')
				ps = 5;/*check value of i*/
		}
		else if( ps == 5 )
		{
			if( c >= '2' && c <= '7')
				ps = 5;/*check value of i*/
		}
		else if( ps == 6 )
		{
			if( c >= '0' && c <= '9')
				ps = 6;/*check value of i*/

			else if( c == '.' )
				ps = 7;
		}
		else if( ps == 7 )
		{
			if( c >= '0' && c <= '9')
				ps = 8;
		}
		else if( ps == 8 )
		{
			if( c >= '0' && c <= '9')
				ps = 9;
		}
		else if( ps == 9 )
		{
			/*accept state*/
		}
		else if( ps == 10 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 11;
		}
		else if( ps == 11 )
		{
			if( c >= 'a' && c <= 'z' )
				ps = 11;/*check value of i*/
		}
		else if( ps == 12 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 13;
		}
		else if( ps == 13 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 14;/*check value of i*/

			else if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
		}
		else if( ps == 14 )
		{
			if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
				ps = 14;/*check value of i*/

			else if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
		}
		else if( ps == 15 )
		{
			if( c >= '0' && c <= '9')
				ps = 15;/*check value of i*/
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
		
	return 0;
}
int main()
{
	
	printf("Valid identifier d2bbbb54 : %d\n",DFA("d2bbbb54"));
	printf("Valid identifier d2bdcbdcb5c : %d\n",DFA("d2bdcbdcb5c"));
	printf("Valid identifier 2cdc765 : %d\n",DFA("2cdc765"));
		
	return 0;
}
	
