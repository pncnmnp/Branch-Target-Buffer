#include <stdio.h>
#include <stdlib.h>

struct Target_Node {
	int tag;
	int target;
	struct Target_Node *next, *prev;
};

struct Target_Node *createTargetNode(int tag, int target) {
	struct Target_Node *node = (struct Target_Node*) malloc(sizeof(struct Target_Node));
	node -> tag 	= tag;
	node -> target  = target;
	node -> prev 	= NULL;
	node -> next 	= NULL;

	return node;
}

void push_target_tag(struct Target_Node **head, int tag, int target) {
	if(*head == NULL) {
		struct Target_Node *temp = createTargetNode(tag, target);
		temp -> next = (*head);
		(*head) = temp;
		return;
	}

	struct Target_Node *temp = createTargetNode(tag, target);
	temp -> next = (*head);

	struct Target_Node *prevHead = temp -> next;
	prevHead -> prev = temp;

	(*head) = temp;	
}

void move_to_head_tag(struct Target_Node **head, int search_tag) {
	struct Target_Node *temp = (*head);

	if(temp -> tag == search_tag) {
		return;
	}

	while(temp -> next != NULL && temp -> next -> tag != search_tag)
		temp = temp -> next;

	if(temp -> next != NULL && temp -> next -> tag == search_tag) {
		struct Target_Node *tag_frame = temp -> next;
		if(tag_frame -> next != NULL) {
			temp -> next = tag_frame -> next;
			temp -> next -> prev = temp;
		}

		else {
			temp -> next = NULL;
		}

		tag_frame -> prev = NULL;

		struct Target_Node *prevHead = (*head);
		tag_frame -> next = prevHead;
		prevHead -> prev = tag_frame;

		(*head) = tag_frame;
	}
}

void delete_last_tag(struct Target_Node **head) {
	struct Target_Node *temp = (*head);

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

struct Target_Node *search_target(struct Target_Node **head, int search_tag) {
	struct Target_Node *temp = (*head);

	while(temp != NULL && temp -> tag != search_tag)
		temp = temp -> next;

	if(temp != NULL && temp -> tag == search_tag) {
		return temp;
	}

	return NULL;
}