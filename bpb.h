#include <stdio.h>
#include <stdlib.h>
#include "./doubly_ll.h"
#include "./btb.h"

int update_hist(int hist, int taken) {
    /*
    taken ->
             0 -> not taken
             1 -> taken
    hist  -> 
             0 -> strongly not taken
             1 -> weakly not taken
             2 -> weakly taken
             3 -> strongly taken
    */

	if((hist == 0 && taken == 0) || 
		(hist == 3 && taken == 1))
		return taken;

	else if((taken == 1) && 
			(hist == 0 || hist == 1 || hist == 2))
		hist += 1;

	else if((taken == 0) && 
			(hist == 1 || hist == 2 || hist == 3))
		hist -= 1;

	return hist >> 1;
}

void update_hist_tag(struct Node **head, int search_tag, int taken) {
	struct Node *frame = (*head);
	while(frame -> next != NULL && frame -> tag != search_tag)
		frame = frame -> next;

	if(frame -> next != NULL && frame -> tag == search_tag)
		frame -> hist = update_hist(frame -> hist, taken);
}

struct Node *search_bpb(struct Node *head, int tag) {
	struct Node *frame = search(&head, tag);
	if(frame == NULL)
		return 0;
	return frame;
}

void flush_bpb(struct Node **head) {
	struct Node *frame = (*head);
	while(frame != NULL) {
		frame -> valid = 0;
		frame = frame -> next;
	}
}

void check_hit_bpb(struct Node *head, int search_tag) {
	struct Node *frame = search_bpb(&head, search_tag);
	if(frame != NULL && frame -> valid != 0) {
		if(frame -> hist >> 1) {
			move_to_head(&head, frame -> tag);
			return check_hit_target_addr(frame -> tag); /* yet to be implemented */
		}

		else
			return 0;
	}

	return 0;
}