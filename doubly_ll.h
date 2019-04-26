#include <stdio.h>
#include <stdlib.h>

struct Node {
	int tag;
	int hist;
	int valid;
	struct Node *next, *prev;
};

struct Node *createNode(int tag, int hist, int valid) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node -> tag 	= tag;
	node -> hist 	= hist;
	node -> valid	= valid;
	node -> next 	= NULL;
	node -> prev 	= NULL;

	return node;
}

void push(struct Node **head, int tag, int hist, int valid) {
	if(*head == NULL) {
		struct Node *temp = createNode(tag, hist, valid);
		temp -> next = (*head);
		(*head) = temp;
		return;
	}

	struct Node *temp = createNode(tag, hist, valid);
	temp -> next = (*head);

	struct Node *prevHead = temp -> next;
	prevHead -> prev = temp;

	(*head) = temp;
}

void move_to_head(struct Node **head, int search_tag) {
	struct Node *temp = (*head);

	if(temp -> tag == search_tag) {
		return;
	}

	while(temp -> next != NULL && temp -> next -> tag != search_tag)
		temp = temp -> next;

	if(temp -> next != NULL && temp -> next -> tag == search_tag) {
		struct Node *tag_frame = temp -> next;
		if(tag_frame -> next != NULL) {
			temp -> next = tag_frame -> next;
			temp -> next -> prev = temp;
		}

		else {
			temp -> next = NULL;
		}

		tag_frame -> prev = NULL;

		struct Node *prevHead = (*head);
		tag_frame -> next = prevHead;
		prevHead -> prev = tag_frame;

		(*head) = tag_frame;
	}
}

void delete_last(struct Node **head) {
	struct Node *temp = (*head);

	if(temp == NULL) {
		return;
	}

	else if(temp -> next == NULL) {
		(*head) == NULL;
		return;
	}

	while(temp -> next -> next != NULL)
		temp = temp -> next;

	if(temp -> next -> next == NULL) {
		free(temp -> next);
		temp -> next = NULL;
	}
}