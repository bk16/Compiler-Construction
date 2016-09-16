//#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <fstream>
//#include <queue>
//using namespace std;
/*works fine. root is returned with every insert*/
struct node
{
	/*int value;*/
	char value[15];
	struct node * left;
	struct node * right;
};

struct node * insert(struct node * x, char * value)
{
	if( x == NULL )
	{	
		x = (struct node *)malloc(sizeof(struct node));
		strcpy(x->value, value);
		x->right = NULL;
		x->left = NULL;
	}
	else
	{
		//printf("I am here 1 + %d\n",value);
		//if( x->value > value )
		if( strcmp(x->value, value) > 0 )
		{
			x->left = insert(x->left,value);
		}
		else
		{
			x->right = insert(x->right,value);
		}
	}
	return x;
}
/*int search(struct node * root, int value)*/
int search(struct node * root, char * value)
{
	if( root == NULL )
	{	
		return 0;
		//printf("I am here\n + %d\n",value);
	}
	else
	{
		//printf("I am here 1 + %d\n",value);
		//if( root->value > value )
		if( strcmp(root->value, value) > 0 )
		{
			return search(root->left,value);
		}
		//else if( root->value < value )
		else if(  strcmp(root->value, value) < 0 )
		{
			return search(root->right,value);
		}
		else
		{
			return 1;
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

        //if (key < x->value)
	if( strcmp(key,x->value) < 0 )
		x->left  = del(x->left,  key);
        //else if (key > x->value)
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
		//cout << endl;	
		printf("\n");
	}
}     
 

 
int main()
{
	struct node * root = NULL;
	
	/*ifstream infile;
	infile.open("input.txt");

	string option;
	int value;

	while( infile >> option >> value )
	{
		if( option.compare("insert") == 0 )
			root = insert( root, value);
		else	
			root = del( root, value );
	}*/

	root = insert(root,"Mai");
	root = insert(root,"Hoon");
	root = insert(root,"Don");
	root = insert(root,"Tum");
	root = insert(root,"Bhi");


	inorder(root);	
	return 0;
}
