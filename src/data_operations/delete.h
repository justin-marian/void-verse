#ifndef _DELETE_H_
#define _DELETE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/structs.h"

/**
 * @brief Deletes the data structure at the specified index from the array.
 * 
 * Deletes the data structure at the specified index from the array.
 * It shifts the subsequent data structures to fill the gap left by the deleted one.
 * Updates the length of the array accordingly.
 * 
 * @param arr A pointer to the pointer to the array containing data structures.
 * @param len A pointer to the current length of the array.
 * @param index The index of the data structure to be deleted.
 * @return An integer representing the status of the operation (SUCCED or FAILED).
 */
int delete_at(void **arr, int *len, int index);

#endif /* _DELETE_H_ */
