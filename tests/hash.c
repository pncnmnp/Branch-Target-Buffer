#include<stdio.h>
#include <stdlib.h>
#include<time.h>

unsigned int hash(unsigned int x, size_t size) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % size;
}

int main(void) {
	size_t size = 1000, count = 0;
	int hash_tb[size];
	srand(time(NULL));

	for(int i = 0; i < size; i++) {
		int h = hash(rand()%size, size);
		if(hash_tb[h] == 1)
			count += 1;
		else
			hash_tb[h] = 1;
	}
	printf("%lf\n", (float)count/size);
	return 0;
}