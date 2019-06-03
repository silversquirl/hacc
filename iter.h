#ifndef CITER_H
#define CITER_H

#define _citer_strip1(first, ...) __VA_ARGS__

#define _citer_fori(varname, initargs, iter, ...) \
	for (_Bool _citer_done = 0; !_citer_done;) \
		for (iter##_iter_type varname = iter##_iter_init initargs; !_citer_done; _citer_done = iter##_iter_step(__VA_ARGS__))

// fori (varname, iter[, args]) stmt;
#define fori(varname, ...) _citer_fori(varname, (_citer_strip1(__VA_ARGS__)), __VA_ARGS__, &varname)

#define _citer_iterator(name, itertype, initparams, iterinit, ...) \
	typedef itertype name##_iter_type; \
	name##_iter_type name##_iter_init initparams { return iterinit; } \
	_Bool name##_iter_step(__VA_ARGS__)

// iterator(name, itertype, iterinit[, extraargs])
#define iterator(name, itertype, ...) _citer_iterator(name, itertype, (_citer_strip1(__VA_ARGS__)), __VA_ARGS__, name##_iter_type *value)

#endif
