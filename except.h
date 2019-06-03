#ifndef EXCEPT_H
#define EXCEPT_H

#include <setjmp.h>

#if __STDC_VERSION__ >= 201112L
#define EXCEPT_NORETURN _Noreturn
#else
#define EXCEPT_NORETURN
#endif

struct exception {
	const char *name;
	const char *msg;
	void *data;
};

jmp_buf *_cexcept_push(struct exception *e);
void _cexcept_done(void);
#define _cexcept_checkpoint(e) (!!setjmp(*_cexcept_push(e)))

#define try \
	for (_Bool _cexcept_flag = 1; _cexcept_flag;) \
		for (struct exception captured_exception; _cexcept_flag; _cexcept_flag = 0, _cexcept_done()) \
			if (!_cexcept_checkpoint(&captured_exception))
#define except(exception_name) else if (!strcmp(captured_exception.name, exception_name))

EXCEPT_NORETURN void throw(const char *name, const char *msg, void *data);

#endif
