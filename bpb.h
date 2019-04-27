#include <stdio.h>
#include <stdlib.h>
#include "./doubly_ll.h"
#include "./btb.h"

/*
    For LRU page replacement implementation details refer:
    Silberschatz, Avi; Galvin, Peter; Gagne, Greg (2008). Operating Systems Concepts. John Wiley & Sons. ISBN 0-470-12872-0.
*/

size_t curr_size = 0; /* Implementation is such that this is in sync with BTB*/

int update_hist_2_bit(int hist, int taken) {
    /*
    2 bit saturating counter
    taken ->
             0 -> not taken
             1 -> taken
    hist  -> 
             0 -> strongly not taken
             1 -> weakly not taken
             2 -> weakly taken
             3 -> strongly taken
    For visualization see : ./schematics/2bit_saturating_counter.svg ( courtesy : Wikipedia )
    */
	if((hist == 0 && taken == 0) || 
		(hist == 3 && taken == 1))
		return hist;

	else if((taken == 1) && 
			(hist == 0 || hist == 1 || hist == 2))
		hist += 1;

	else if((taken == 0) && 
			(hist == 1 || hist == 2 || hist == 3))
		hist -= 1;

	return hist;
}

void update_hist_tag(struct Node **head, int search_tag, int taken) {
	/*
        When the pipeline has to be flushed because of wrong prediction,
        this function will update the hist bit
	*/
	struct Node *frame = (*head);
	while(frame -> next != NULL && frame -> tag != search_tag)
		frame = frame -> next;

	if(frame -> next != NULL && frame -> tag == search_tag)
		frame -> hist = update_hist_2_bit(frame -> hist, taken);
}

struct Node *search_bpb(struct Node *head, int tag) {
	/*
        Returns 0 if no frame found, else returns frame struct
	*/
	struct Node *frame = search(&head, tag);
	if(frame == NULL)
		return 0;
	return frame;
}

void flush_bpb(struct Node **head) {
	/*
        The bpb and btb gets cleared with size being reset to 0
	*/
	struct Node *frame = (*head);
	while(frame != NULL) {
		frame -> valid = 0;
		frame = frame -> next;
	}

	flush_btb();

	curr_size = 0;	/* size of the doubly_ll changed */
}

int check_hit_bpb(struct Node *head, int search_tag) {
	/*
        Returns the target address if hit, 
        returns 0 if not taken,
	*/
	struct Node *frame = search_bpb(head, search_tag);
	if(frame != 0 && frame -> valid != 0) {
		/* Checking the MSB bit */
		if(frame -> hist >> 1) {
			/* Recently used frame moved to top, 
			adhering to LRU replacement policy 
			*/
			move_to_head(&head, frame -> tag);
			return check_hit_target_addr(frame -> tag);
		}
	}

	return 0;
}

struct Node *add_entry(struct Node *head, int tag, int target, size_t size) {
	/*
        Adds new entry in btb and bpb,
        returns the updated head_pointer
	*/
	int hist = 2; /* we start with 'weakly taken' */
	int valid = 1;
	if(curr_size < size) {
		push(&head, tag, hist, valid);
		add_target(tag, target);
		curr_size += 1;
	}

	else {
		/* replace the last page */
		delete_last(&head);
		target_delete();

		push(&head, tag, hist, valid);
		add_target(tag, target);
	}

	return head;
}