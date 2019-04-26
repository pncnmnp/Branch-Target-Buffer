#include<stdio.h>
#include<stdlib.h>

struct Node {
	int data;
	struct Node *next, *prev;
};

struct Node *createNode(int data) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;

	return node; // M1 Forgot to write
}

void push(struct Node **head, int data) {
	// M4 Not Mentioned this condition
	if(*head == NULL) {
		struct Node *temp = createNode(data);
		temp->next = (*head);
		(*head) = temp;
		return;
	}

	struct Node *temp = createNode(data);
	temp->next = (*head);
	
	struct Node *prevHead = temp->next;

	prevHead->prev = temp;

	(*head) = temp;
}

int deleteNode(struct Node **head, int data) {
	struct Node *temp = (*head);

	if(temp->data == data) {
		(*head) = temp->next;
		temp->prev = NULL;
		free(temp);
		return 0;
	}

	while(temp->next != NULL && temp->next->data != data)
		temp = temp->next;

	if(temp->next != NULL && temp->next->data == data) {
		struct Node *after = temp->next->next;
		free(temp->next);
		temp->next = after;
		after->prev = temp;
	}
}

void insertAfter(struct Node **head, int data, int after) {
	struct Node *node = createNode(data);

	struct Node *temp = *head;

	// M2 Wrote || instead of &&
	while(temp != NULL && temp->data != after)
		temp = temp->next;

	// M3 Not written temp != NULL
	if(temp != NULL && temp->data == after) {
		struct Node *inter = temp->next;
		temp->next = node;
		node->prev = temp;

		node->next = inter;
		inter->prev = node;
	}
}

void append(struct Node **head, int data) {
	struct Node *node = createNode(data);

	struct Node *temp = (*head);

	while(temp->next != NULL)
		temp = temp->next;

	temp->next = node;
	node->prev = temp;
}

void printList(struct Node *node) {
	while(node != NULL) {
		printf("%d ",node->data);
		node = node->next;
	}
}

void printListReverse(struct Node *node) {
	while(node->next != NULL)
		node = node->next;

	while(node->prev != NULL) {
		printf("%d ",node->data);
		node = node->prev;
	}
	printf("%d ",node->data);	
}

void choice() {
	int choice = 0;

	struct Node *head = NULL;

	while(1) {
		printf("1.Push\n2.InsertAfter\n3.Append\n4.PrintList\n5.DeleteNode\n6.printListReverse\n7.Exit\nChoose: ");
		scanf("%d", &choice);

		if(choice == 1) {
			int val = 0;
			printf("Enter Value: ");
			scanf("%d", &val);
			push(&head, val);
		}

		else if(choice == 2) {
			int val = 0, after = 0;
			printf("Enter Value: ");
			scanf("%d", &val);
			printf("Enter After Value: ");
			scanf("%d", &after);
			insertAfter(&head, val, after);			
		}

		else if(choice == 3) {
			int val = 0;
			printf("Enter Value: ");
			scanf("%d", &val);
			append(&head, val);			
		}

		else if(choice == 4) {
			printList(head);
		}

		else if(choice == 5) {
			int val = 0;
			printf("Enter Value to be Deleted: ");
			scanf("%d", &val);
			deleteNode(&head, val);						
		}

		else if(choice == 6) {
			printListReverse(head);			
		}

		else if(choice == 7)
			exit(0);
	}
}

int main(void) {
	choice();

	return 0;
}