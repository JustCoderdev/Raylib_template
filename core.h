#ifndef CORE_TYPES_
#define CORE_TYPES_


typedef unsigned char      n8;
typedef unsigned short int n16;
typedef unsigned int       n32;
typedef unsigned long int  n64;

typedef signed char      i8;
typedef signed short int i16;
typedef signed int       i32;
typedef signed long int  i64;

#define RL_BOOL_TYPE
typedef enum bool {
	true = (1 == 1),
	false = (1 != 1)
} bool;

typedef enum error {
	success = false,
	failure = true
} error;

#endif /* CORE_TYPES_ */
