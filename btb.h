#include <stdio.h>
#include <stdlib.h>
#include "./target_doubly_ll.h"

struct Target_Node *head = NULL;

void target_to_head(int);

int check_hit_target_addr(int search_tag) {
	/*
        Returns target address if hit, else return 0
	*/
	struct Target_Node *frame = search_target(&head, search_tag);
	target_to_head(search_tag);
	if(frame != NULL) 
		return frame -> target;
	return 0;
}

void add_target(int tag, int target) {
	/*
        Adds new entry in BTB
	*/
	push_target_tag(&head, tag, target);
}

void target_to_head(int tag) {
	/*
        Moves the recently used page at top, in sync with BPB
	*/
	move_to_head_tag(&head, tag);
}

void target_delete(void) {
	delete_last_tag(&head);
}

void flush_btb(void) {
	struct Target_Node *temp = head;
	if(temp == NULL) {
		return;
	}

	while(temp -> next != NULL) {
		temp = temp -> next;
		free(temp -> prev);
	}
	free(temp);
}