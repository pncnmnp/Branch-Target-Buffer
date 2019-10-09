#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bpb.h"
#define size_bpb 5000

int str2int(const char *s) {
	int res = 0;
	while (*s) {
		res *= 10;
		res += *s++ - '0';
	}

	return res;
}

int main(void) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	srand(time(NULL));

	size_t miss_count = 0, count = 0;
	struct Node *head = NULL;

	fp = fopen("./traces/trace_4", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		char tag[8];
		int itag, itarget, s_hist;

		strncpy(tag, line, 8);
		tag[8] = 0;

		int last_bit = line[8] - '0';

		itag = str2int(tag);
		itarget = rand()%size_bpb;
		struct Node *search_validity = search_bpb(head, itag); // will provide the BPB's frame
		int validity = check_hit_bpb(head, itag); // will provide BTB's target address
		if (search_validity != 0)
			s_hist = search_validity->hist;
		else
			s_hist = -1;

		if(validity == 0 && s_hist == -1) {
			head = add_entry(head, itag, itarget, size_bpb);
			// miss_count += 1;
		}

		if(s_hist >> 1 != last_bit) {
			// printf("%d, %d, %d, %d, %d\n", itag, itarget, validity, last_bit, s_hist);
			// wrong prediction, pipeline is flushed
			update_hist_tag(&head, itag, last_bit);
			miss_count += 1;
		}

		else
			update_hist_tag(&head, itag, last_bit);
		count += 1;
	}

	printf("Miss \t\t Total \t\t efficiency\n");
	if (count > 100000)
		printf("%ld \t\t %ld \t %f\n", miss_count, count, 1-(float)miss_count/count);
	else
		printf("%ld \t\t %ld \t\t %f\n", miss_count, count, 1-(float)miss_count/count);

	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}