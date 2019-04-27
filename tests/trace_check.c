#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bpb.h"
#define size_bpb 256

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

	fp = fopen("./traces/trace_2", "r");
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
		int validity = check_hit_bpb(head, itag);
		struct Node *search_validity = search_bpb(head, itag);
		if (search_validity != 0)
			s_hist = search_validity->hist;
		else
			s_hist = -1;

		// printf("%d, %d, %d, %d, %d\n", itag, itarget, validity, last_bit, s_hist);

		if(validity == 0 && s_hist == -1) {
			head = add_entry(head, itag, itarget, size_bpb);
			miss_count += 1;
		}
		if(s_hist >> 1 != last_bit)
			update_hist_tag(&head, itag, last_bit);
		count += 1;
	}

	printf("%ld, %ld, %f\n", miss_count, count, 1-(float)miss_count/count);

	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}