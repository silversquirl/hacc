#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "except.h"

void do_error(void) {
	throw("myException", "Hi! I'm an exception!", NULL);
}

int main() {
	for (int i = 0; i < 4; i++) {
		try {
			if (i % 2) do_error();
			puts("No error occurred!");
		} except ("myException") {
			printf("There was a myException: %s %p\n", captured_exception.msg, captured_exception.data);
		} else {
			puts("An error occurred");
			printf("%s: %s %p\n", captured_exception.name, captured_exception.msg, captured_exception.data);
		}
	}
	return 0;
}
