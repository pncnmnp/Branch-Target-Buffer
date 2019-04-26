#include "../doubly_ll.h"
#include <stdio.h>
#include <stdlib.h>

void print(struct Node *node) {
	while(node != NULL) {
		printf("%d ",node->tag);
		node = node->next;
	}
	printf("\n");
}

void choice() {
	int choice = 0;
	struct Node *head = NULL;

	while(1) {
		printf("1.push\n2.move to head\n3.delete last\n4.print\nchoose: ");
		scanf("%d", &choice);

		if(choice == 1) {
			int tag = 0, history = 0, valid = 0;
			printf("enter tag, history and valid: ");
			scanf("%d%d%d", &tag, &history, &valid);
			push(&head, tag, history, valid);
		}

		else if(choice == 2) {
			int search_tag = 0;
			printf("enter search_tag: ");
			scanf("%d", &search_tag);
			move_to_head(&head, search_tag);			
		}

		else if(choice == 3) {
			delete_last(&head);
		}

		else if(choice == 4) {
			print(head);
		}
	}
}

int main(void) {
	choice();
	return 0;
}