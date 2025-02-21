#include <stdio.h>
#include<stdlib.h>

struct tnode{
	
	int x;
	tnode *next;
	tnode *prev;
}*head, *tail, *curr; 
//buat nama lokalnya bisa di sini

void pushFront(int value){
	
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
}

void pushBack(int value){
	
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = node;
		tail->next = NULL;
	}
}

void pushMid(int value, int searchKey){
	
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else
	{
		curr = head;
		struct tnode *currBack;
		
		while(curr != NULL)
		{
			if(curr->x == searchKey)
			{
				if(curr == tail)
				{
					pushBack(value);
				}
				else
				{
					currBack = curr->next;
					node->next = currBack;
					node->prev = curr;
					currBack->prev = node;
					curr->next = node;
				}
				break;
			}
			curr = curr->next;
		}
		
		if(curr == NULL)
		{
			printf("Data %d is not found.\n", searchKey);
		}
	}
}

void deleteDataHead(){
	
	if(head == NULL)
	{
		printf("There's no data to be deleted (head).\n'");
	}
	else
	{
		if(head == tail)
		{
			free(head);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = head;
			head = head->next;
			free(del);
			head->prev = NULL;
		}
	}
}

void deleteDataMid(int dataYgDihapus){
	
	if(head == NULL)
	{
		printf("There's no data to be deleted (mid).\n'");
	}
	else
	{
		curr = head;
		struct tnode *kiri, *kanan;
		
		while(curr != NULL)
		{
			if(curr->x == dataYgDihapus)
			{
				if(curr == tail)
				{
					struct tnode *del = tail;
					tail = tail->prev;
					free(del);
					tail->next = NULL;
				}
				else
				{
					struct tnode *del = curr;
					kiri = curr->prev;
					kanan = curr->next;
					kiri->next = kanan;
					kanan->prev = kiri;
					free(curr);
				}
				break;
			}
			curr = curr->next;
		}
	}
}

void deleteDataTail(){
	
	if(head == NULL)
	{
		printf("There's no data to be deleted (tail).\n'");
	}
	else
	{
		if(head == tail)
		{
			free(tail);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = tail;
			tail = tail->prev;
			free(del);
			tail->next = NULL;
		}
	}
}

void printData(){
	
	printf("Data dari depan ke belakang:\n");
	curr = head;
	while(curr != NULL)
	{
		printf("%d ", curr->x);
		curr = curr->next;
	}
	printf("\n");
}

void printDataReverse(){
	
	printf("Data dari belakang ke depan:\n");
	curr = tail;
	while(curr != NULL)
	{
		printf("%d ", curr->x);
		curr = curr->prev;
	}
	printf("\n");
}

int main(){
	
	printf("Double Linked list\n");
	//masukkan fungsi dan data yang diinginkan
	pushFront(13);
	pushFront(9);
	pushFront(5);
	pushMid(21, 9);
	pushBack(15);
	deleteDataHead();
	pushMid(33, 15);
	deleteDataTail();
	pushFront(11);
	pushBack(2);
	
	printData();
	printDataReverse();
}
