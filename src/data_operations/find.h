#ifndef _FIND_H_
#define _FIND_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/structs.h"

/**
 * @brief Finds and prints the data at the specified index in the data block.
 * 
 * Finds and prints the data at the specified index in the data block.
 * The data block is expected to be an array of bytes containing multiple data structures.
 * Interpret the data and print the values based on the data structure's type.
 * 
 * @param data_block The data block containing multiple data structures.
 * @param len The number of data structures in the data block.
 * @param index The index of the data structure to find and print.
 */
void find(void *data_block, int len, int index);

#endif /* _FIND_H_ */
