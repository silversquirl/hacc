#include <stdio.h>
#include "iter.h"

iterator(range, int, start, int start, int end) {
	++*value;
	if (*value >= end) return 1;
	return 0;
}

int main() {
	fori (i, range, 1, 10) {
		printf("%d\n", i);
	}
	return 0;
}
