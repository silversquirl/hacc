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
	for ( \
		struct { _Bool flag; struct exception e; } _cexcept_try = {0}; \
		!_cexcept_try.flag; \
		_cexcept_try.flag = 1, _cexcept_done() \
	) \
		if (!_cexcept_checkpoint(&_cexcept_try.e))
#define except(exception_name) else if (!strcmp(_cexcept_try.e.name, exception_name))
#define captured_exception (_cexcept_try.e)

EXCEPT_NORETURN void throw(const char *name, const char *msg, void *data);

#endif
