#ifndef  __LIST_H__
#define  __LIST_H__

#include "macro.h"

#ifndef size_t
#	define size_t unsigned long long int
#endif

#define REGISTRY(func, type) type _list_##func
#define CALL(func) _list_##func
#define CALL_R(func, type) (type) _list_##func

/* value type to insert in list*/
enum DTA_TYPE{
	DTA_NULL,
	DTA_CHAR,
	DTA_INT,
	DTA_FLOAT,
	DTA_POINTER
};

pack(__list__){
	const char *name;
	enum DTA_TYPE type;
}*List;

/* define list functions */
REGISTRY(new, List)	(const char *, enum DTA_TYPE);
REGISTRY(insert, void)	(List, void *, unsigned int);
REGISTRY(remove, void)	(List, unsigned int);
REGISTRY(get, void *)	(List, unsigned int);
REGISTRY(set, void)	(List, void *, unsigned int);
REGISTRY(size, size_t)	(List);

#define list_new(t_name, type) CALL_R(new, List)(t_name, type)

#define list_push(lst, dta) CALL(insert)(lst, dta, 0)
//#define list_pushi(lst, dta) list_push(lst, dta)
//#define list_pushs(lst, dta) list_push(lst, dta)
//#define list_pushp(lst, dta) list_push(lst, dta)

#define list_append(lst, dta) CALL(insert)(lst, dta, list_size(lst))
//#define list_appendi(lst, dta) list_append(lst, dta, DTA_INT)
//#define list_appends(lst, dta) list_append(lst, dta, DTA_CHAR)
//#define list_appendp(lst, dta) list_append(lst, dta, DTA_POINTER)

#define list_insert(lst, dta, index) CALL(insert)(lst, dta, index)
//#define list_inserti(lst, dta, index) list_insert(lst, dta, index)
//#define list_inserts(lst, dta, index) list_insert(lst, dta, index)
//#define list_insertp(lst, dta, index) list_insert(lst, dta, index)

#define list_set(lst, dta, index) CALL(set)(lst, dta, index)
//#define list_seti(lst, dta, index) list_set(lst, dta, index)
//#define list_sets(lst, dta, index) list_set(lst, dta, index)
//#define list_setp(lst, dta, index) list_set(lst, dta, index)

#define list_get(lst, index, type) (type) CALL_R(get, type)(lst, index)
#define list_remove(lst, index) CALL(remove)(lst, index)
#define list_pop(lst) CALL(remove)(lst, 0)
#define list_size(lst) CALL_R(size, size_t)(lst)

#endif  /*LIST_H*/
