#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdlib.h>
#include <malloc.h>

#include <err.h>
#include <list.h>
#include <macro.h>

#define USE(fcn)\
	size_t _arg_l = 0;\
	lua_getglobal(L, fcn)

#define ARG(x, type)\
	_arg_l++;\
	lua_push##type(L, x)

#define CALL_S()\
	lua_call(L, _arg_l, 0)

#define CALL_R(out, type, l_type)\
	lua_call(L, _arg_l, 1);\
	out = (type) lua_to##l_type(L, -1);\
	lua_pop(L, 1)

/* lua library */
static lua_State *L;

REGISTRY(new, List)(const char *name, enum DTA_TYPE type){
	USE("new");
	ARG(name, string);
	CALL_S();

	List l = malloc(sizeof(struct __list__));
	l->name = name;
	l->type = type;

	return l;
}

REGISTRY(insert, void)(List lst, void *dta, unsigned int index){
	USE("insert");
	ARG(lst->name, string);
	switch (lst->type){
		case DTA_CHAR:
			ARG(dta, string);
			break;
		case DTA_INT:
			ARG(dta, integer);
			break;
/*		case DTA_FLOAT:
			ARG(()dta, number);
			break;*/
		case DTA_POINTER:
			ARG(dta, string);
			break;
		default:
			break;
	}
	ARG(index, number);
	CALL_S();
}

REGISTRY(remove, void)(List lst, unsigned int index){
	USE("remove");
	ARG(lst->name, string);
	ARG(index, number);
	CALL_S();
}

REGISTRY(get, void*)(List lst, unsigned int index){
	void *res = 0;

	USE("get");
	ARG(lst->name, string);
	ARG(index, number);
	switch (lst->type){
		case DTA_CHAR:
			CALL_R(res, void *, string);
			break;
		case DTA_INT:
			CALL_R(res, void *, integer);
			break;
		case DTA_POINTER:
			CALL_R(res, void *, userdata);
			break;
	}

	return res;
}

REGISTRY(set, void)(List lst, void *dta, unsigned int index){
	USE("set");
	ARG(lst->name, string);
	switch (lst->type){
		case DTA_CHAR:
			ARG(dta, string);
			break;
		case DTA_INT:
			ARG(dta, integer);
			break;
/*		case DTA_FLOAT:
			ARG(dta, number);
			break;*/
		case DTA_POINTER:
			ARG(dta, string);
			break;
		default:
			break;
	}
	ARG(index, number);
	CALL_S();
}

REGISTRY(size, size_t)(List lst){
	size_t size = 0;

	USE("size");
	ARG(lst->name, string);
	CALL_R(size, size_t, integer);

	return size;
}

/* list functions in lua */
static const char *lua_string = "\
_LIST = {}\n\
function new(lst)\n\
	 _LIST[lst] = {}\n\
end\n\
function insert(lst, dta, index) table.insert(_LIST[lst], index+1, dta) end\n\
function remove(lst, index) table.remove(_LIST[lst], index+1) end\n\
function get(lst, index) return _LIST[lst][index+1] end\n\
function set(lst, dta, index) _LIST[lst][index+1] = dta end\n\
function size(lst)\n\
	count = 0\n\
	for x in pairs(_LIST[lst]) do\n\
		count = count + 1\n\
	end\n\
	return count\n\
end\n";

/* run on system initialize */
static void ON_SYS_INIT(list){
	L = luaL_newstate();
	luaL_openlibs(L);
	if(luaL_dostring(L, lua_string)){
		exit(ERR_LIST_INIT);
	}
}

/* run on system exit */
static void ON_SYS_EXIT(list){
	lua_close(L);
}
