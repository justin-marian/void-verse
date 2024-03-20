#ifndef _ADD_H_
#define _ADD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/structs.h"
#include "../utils/utils.h"

/**
 * @brief Add a new data_structure to the end of the array.
 *
 * Adds a new data_structure 'data' to the end of the array 'arr'.
 * If 'arr' is NULL, it allocates memory to hold the new data. The total size of
 * the new array will be 'data->header->len + HEAD_SIZE' bytes.
 *
 * @param arr Pointer to the array of data_structures.
 * @param len Pointer to the current number of elements in the array.
 * @param data Pointer to the data_structure to be added.
 * @return Returns SUCCED (0) if successful, or an error code if memory allocation fails.
 */
int add_last(void **arr, int *len, data_structure *data);

/**
 * @brief Add a new data_structure at a specific index in the array.
 *
 * Adds a new data_structure 'data' at the specified index 'index' in the array 'arr'.
 * If 'index' is less than the current number of elements in the array, the new data will be inserted
 * at the specified index. If 'index' is equal to or greater than the current number of elements,
 * the new data will be added to the end of the array.
 *
 * @param arr Pointer to the array of data_structures.
 * @param len Pointer to the current number of elements in the array.
 * @param data Pointer to the data_structure to be added.
 * @param index Index where the new data_structure will be inserted.
 * @return Returns SUCCED (0) if successful, or an error code if memory allocation fails.
 */
int add_at(void **arr, int *len, data_structure *data, int index);

#endif /* _ADD_H_ */
