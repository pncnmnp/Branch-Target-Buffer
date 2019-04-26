#include<stdio.h>
#include<stdlib.h>

typedef struct bpb {
	int tag;
	int hist;
	int valid;
} BPB;

void init(BPB bpb_table[], size_t size) {
	for(int i = 0; i < size; i++) {
		bpb_table[i].tag 	= 0;
		bpb_table[i].hist 	= 0;
		bpb_table[i].valid 	= 0;
	}
}

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
		(hist == 3 && taken == 1)) {
		return taken;
	}

	else if((taken == 1) && 
			(hist == 0 || hist == 1 || hist == 2)) {
		hist += 1;
	}

	else if((taken == 0) && 
			(hist == 1 || hist == 2 || hist == 3)) {
		hist -= 1;
	}

	return hist >> 1;
}

int search_bpb(int tag, size_t size) {

}