#ifndef  __MACRO_H__
#define  __MACRO_H__

#define pack(p_name) typedef struct __attribute__((__packed__)) p_name

#define ON_SYS_INIT(alias) __attribute__((__constructor__)) alias##_init(void)
#define ON_SYS_EXIT(alias) __attribute__((__destructor__)) alias##_exit(void)

#endif  /*MACRO_H*/
