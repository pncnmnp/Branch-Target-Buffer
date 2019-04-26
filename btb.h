#include <stdio.h>
#include <stdlib.h>
#include "./target_doubly_ll.h"

struct Target_Node *head = NULL;

int check_hit_target_addr(int search_tag) {
	struct Target_Node *frame = search_target(&head, search_tag);
	if(frame != NULL)
		return frame -> target;
	return 0;
}

void add_target(int tag, int target) {
	push_target_tag(&head, tag, target);
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