#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node{
	
    char key[50];
    struct Node* next;
}Node;

char hashTable[TABLE_SIZE][50];
Node* chain[TABLE_SIZE];

void initTable(){
    for(int i=0; i<TABLE_SIZE; i++) 
	{
        strcpy(hashTable[i], "");
        chain[i] = NULL;
    }
}

int hashMidSquare(const char* key){
	
    int hash = 0;
    for(int i=0; key[i] != '\0'; i++) 
	{
        hash += key[i] * key[i];
    }
    return (hash / 10) % TABLE_SIZE;
}

int hashDivision(const char* key){
	
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
	{
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

int hashFolding(const char* key){
	
    int hash = 0;
    for(int i=0; key[i] != '\0'; i++) 
	{
        hash = (hash << 3) + key[i];
    }
    return hash % TABLE_SIZE;
}

int hashDigitExtraction(const char* key){
	
    return (key[0] + key[strlen(key) - 1]) % TABLE_SIZE;
}

int hashRotation(const char* key){
	
    int hash = 0;
    for(int i = 0; key[i] != '\0'; i++) 
	{
        hash = (hash << 5) | (hash >> 27);
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

int (*selectedHashFunction)(const char* key);

void insertLinearProbing(const char* key){
	
    int index = selectedHashFunction(key);
    
    while(strcmp(hashTable[index], "") != 0) 
	{
        index = (index + 1) % TABLE_SIZE;
    }
    strcpy(hashTable[index], key);
}

void insertChaining(const char* key){
	
    int index = selectedHashFunction(key);
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->next = chain[index];
    chain[index] = newNode;
}

void insertRehashing(const char* key){
	
    int index = selectedHashFunction(key);
    
    if(strcmp(hashTable[index], "") == 0) 
	{
        strcpy(hashTable[index], key);
    }
	else 
	{
        int newIndex = (index + 1) % TABLE_SIZE;
        while(strcmp(hashTable[newIndex], "") != 0) 
		{
            newIndex = (newIndex + 1) % TABLE_SIZE;
        }
        strcpy(hashTable[newIndex], key);
    }
}

void displayTable(){
	
    printf("Index\tValue\n");
    for(int i = 0; i < TABLE_SIZE; i++)
	{
        printf("%d\t%s\n", i, hashTable[i]);
        Node* temp = chain[i];
        while(temp)
		{
            printf(" -> %s", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Menu untuk memilih metode hashing
void menu(){
    int choice, method;
    char key[50];
    
    printf("Pilih fungsi hash:\n");
    printf("1. Mid Square\n");
    printf("2. Division\n");
    printf("3. Folding\n");
    printf("4. Digit Extraction\n");
    printf("5. Rotation\n");
    printf("Pilihan: ");
    scanf("%d", &method); getchar();
    
    switch(method)
	{
        case 1: selectedHashFunction = hashMidSquare; break;
        case 2: selectedHashFunction = hashDivision; break;
        case 3: selectedHashFunction = hashFolding; break;
        case 4: selectedHashFunction = hashDigitExtraction; break;
        case 5: selectedHashFunction = hashRotation; break;
    }
    
    while(1) 
	{
        printf("\nMenu:\n");
        printf("1. Insert dengan Linear Probing\n");
        printf("2. Insert dengan Chaining\n");
        printf("3. Insert dengan Rehashing\n");
        printf("4. Tampilkan Hash Table\n");
        printf("5. Exit\n");
        printf("Pilihan: ");
        scanf("%d", &choice); getchar();

        switch(choice) 
		{
            case 1:
                printf("Masukkan string: ");
                fgets(key, 50, stdin);
                key[strcspn(key, "\n")] = 0;
                insertLinearProbing(key);
                break;
                
            case 2:
                printf("Masukkan string: ");
                fgets(key, 50, stdin);
                key[strcspn(key, "\n")] = 0;
                insertChaining(key);
                break;
                
            case 3:
                printf("Masukkan string: ");
                fgets(key, 50, stdin);
                key[strcspn(key, "\n")] = 0;
                insertRehashing(key);
                break;
                
            case 4:
                displayTable();
                break;
                
            case 5:
                return;
        }
    }
}

int main(){
	
    initTable();
    menu();
    
    return 0;
}
