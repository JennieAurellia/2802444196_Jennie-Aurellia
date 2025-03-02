#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Data{
	
	char operasi;
	struct Data *next;
}*head, *tail;

void pushBack(char operasi){
	
	struct Data *node = (struct Data*) malloc(sizeof(Data));
	node->operasi = operasi;
	
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
	}
	else
	{
		tail->next = node;
		tail = node;
		tail->next = NULL;
	}
}

void deleteTail(){
	
	if(head == NULL)
	{
		printf("There's no operator to be deleted.\n");
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
			struct Data *temp = head;
            while (temp->next != tail)
			{
                temp = temp->next;
            }
            free(tail);
            tail = temp;
            tail->next = NULL;
		}
	}
}

void transferOperator(char postfix[], int *j){
	
	while(head != NULL) 
	{
        if(tail->operasi == '(') 
		{
            deleteTail();
            postfix[(*j)++] = tail->operasi;
        	deleteTail();
            break;
        }
        postfix[(*j)++] = tail->operasi;
        deleteTail();
    }
}

int main(){
	
	char infix[100];
	char postfix[100];
	scanf("%[^\n]", &infix); getchar();
//	printf("%s", infix);
	
	int i = 0;
	int j = 0;
	
	while(infix[i] != '\0')
	{
		if(infix[i] >= '0' && infix[i] <= '9')
		{
			postfix[j++] = infix[i];
//			printf("%c ", postfix[j]);
		}
		else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(')
		{
			pushBack(infix[i]);
		}
		else if(infix[i] == ')')
		{
			transferOperator(postfix, &j);
		}
		
		i++;
	}
	
	transferOperator(postfix, &j);
	
	postfix[j] = '\0';
	int k = 0;
	while(postfix[k] != '\0')
	{
		printf("%c ", postfix[k]);
		k++;
	}
	printf("\n");
	
	return 0;
}
