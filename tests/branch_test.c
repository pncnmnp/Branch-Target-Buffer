#include <stdio.h>
#include <stdlib.h>
#include "../bpb.h"
#define size 3

int main(void) {
	struct Node *head = NULL;
	head = add_entry(head, 2, 40, size);
	head = add_entry(head, 1, 30, size);
	// flush_bpb(&head);
	head = add_entry(head, 5, 44, size);
	update_hist_tag(&head, 5, 1);
	update_hist_tag(&head, 5, 1);
	update_hist_tag(&head, 5, 0);
	update_hist_tag(&head, 5, 0);
	update_hist_tag(&head, 5, 0);
	update_hist_tag(&head, 5, 1);
	update_hist_tag(&head, 5, 1);
	head = add_entry(head, 0, 20, size);
	head = add_entry(head, 30, 60, size);

	printf("for: %d, check_hit val: %d\n", 2, check_hit_bpb(head, 2));
	printf("for: %d, check_hit val: %d\n", 5, check_hit_bpb(head, 5));
	printf("for: %d, check_hit val: %d\n", 0, check_hit_bpb(head, 0));
	printf("for: %d, check_hit val: %d\n", 30, check_hit_bpb(head, 30));

	head = add_entry(head, 6, 9, size);
	head = add_entry(head, 7, 8, size);
	printf("for: %d, check_hit val: %d\n", 5, check_hit_bpb(head, 5));
	printf("for: %d, check_hit val: %d\n", 50, check_hit_bpb(head, 50));

	return 0;
}