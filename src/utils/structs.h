#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/**
 typedef signed char   int8_t hhu
 typedef signed short  int16_t hd
 typedef signed int    int32_t  d
*/

#include <inttypes.h>

#define ERROR -1
#define SUCCED 0
#define FAILED 1

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef unsigned int ui;
typedef unsigned char uc;

#define HEAD_SIZE sizeof(uc) + sizeof(ui)

typedef struct {
    uc type;	// type of data - sizeof
    ui len;		// length of data
} head;

typedef struct {
    head *header;	// simple linked list
    void *data;		// data of variable length
} data_structure;

#endif /* _STRUCTS_H_ */
