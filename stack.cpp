#include <iostream>
#include <cstdlib>
using namespace std;

struct node
{
	int val;
	struct node * next;
};

class stack
{
private:
	struct node * head;
	int size;

public:
	
	stack()
	{
		head = NULL;
		size = 0;
	}

	stack(int k)
	{
		head = NULL;
		size = 0;
	}

	void push(int item)
	{
		if( head == NULL )
		{
			head = (struct node*)malloc(sizeof(struct node));
			head->val = item;
			head->next = NULL;
		}
		else
		{
			struct node * temp = (struct node*)malloc(sizeof(struct node));
			temp->val = item;
			temp->next = head;
			head = temp;
		}
		size++;
	}

	int pop()
	{
		if( head == NULL )
			exit(0);

		
		int item = head->val;
		head = head->next;

		//if( head == NULL )
		//	tail = NULL;

		size--;
		return item;
	}

	int getSize()
	{
		return size;
	}

	bool empty()
	{
		return size == 0;
	}

	void print()
	{
		struct node * temp = head;
		while( temp )
		{
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main()
{
	stack s(2);

	s.push(23);
	s.push(41);
	s.push(82);
	s.push(2);


	s.print();

	cout << "Pop : " << s.pop() << endl;
	
	s.print();
	cout << "Size : " << s.getSize() << endl;

	cout << "Pop : " << s.pop() << endl;
	
	s.print();

	s.push(81);
	s.push(93);

	s.print();
	cout << "Size : " << s.getSize() << endl;
	cout << "Pop : " << s.pop() << endl;
	
	s.print();
}

	
