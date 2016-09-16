#include <stdio.h>
#define mininum(a,b) (a<b? a:b)

typedef enum
{
	bali = 20, kali
} names;

int main()
{
	FILE * fp = fopen("input1.txt","r");

	int c;
	char B[1000];
	int index = 0;
	int k = 4;
	while (((c = fgetc(fp)) != EOF) && index < k)
    	{
		B[index++] = (char) c;	
		//printf("\n%c ", (char)c);
		
    	}

	B[index] = '\0';
	printf("%s\n", B);

	//fp = fp - 4;
 	fseek(fp,-index-1, SEEK_CUR); 
	c = fgetc(fp);
	printf("%c ", (char)c);
 	fseek(fp,3, SEEK_CUR); 
	c = fgetc(fp);
	printf("%c ", (char)c);
	return 0;
}
