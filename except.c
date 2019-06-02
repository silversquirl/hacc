#include <stdlib.h>
#include "except.h"

struct _ce {
	struct exception *e;
	jmp_buf jb;
};

size_t stack_alloc = 8;
struct _ce *stack, *stack_bottom = NULL;

jmp_buf *_cexcept_push(struct exception *e) {
	if (!stack_bottom) {
		stack = stack_bottom = malloc(sizeof *stack_bottom * stack_alloc);
	} else if (stack_alloc <= stack - stack_bottom) {
		size_t len = stack - stack_bottom;
		stack_alloc *= 2;
		stack_bottom = realloc(stack_bottom, sizeof *stack_bottom * stack_alloc);
		stack = stack_bottom + len;
	}
	if (!stack_bottom) abort();

	*stack = (struct _ce){e};
	return &(stack++)->jb;
}

void _cexcept_done(void) {
	stack--;
}

EXCEPT_NORETURN void throw(const char *name, const char *msg, void *data) {
	struct _ce ce = stack[-1];
	ce.e->name = name;
	ce.e->msg = msg;
	ce.e->data = data;
	longjmp(ce.jb, 1);
}
