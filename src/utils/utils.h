#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../utils/structs.h"

/**
 * @brief Advances the byte stream pointer 'ptr' and its length 'len' times.
 * 
 * @param ptr Pointer to the byte stream.
 * @param len Pointer to the length of the byte stream.
 */
void pass_bytes(char **ptr, int *len);

/**
 * @brief Calculate the total number of bytes occupied by all data structures in the array.
 *
 * @param arr Pointer to the array of data structures.
 * @param len Current length of the array, i.e., the number of data structures present.
 * 
 * @return Total number of bytes occupied by all data structures in the array.
 *
 * @note The array is assumed to contain data structures represented as a sequence of bytes,
 *       with each data structure prefixed by a header consisting of:
 *       - 1 byte indicating the type of the data structure ('1', '2', '3').
 *       - 4 bytes indicating the length of the data structure (excluding the header).
 */
int getTotalBytes(void **arr, int len);

/**
 * @brief Copies data from 'ptr1' to 'ptr' based on the data type stored in 'data->header->type'.
 * 
 * Used to copy and paste data from one location to another based on the data type
 * stored in the 'data_structure' pointed by 'data'. It is used for specific types ('1', '2', or '3')
 * and handles different sizes of data (int8_t, int16_t, int32_t).
 * 
 * @param data Pointer to the data_structure that contains the data type information.
 * @param ptr  Pointer to the destination location.
 * @param ptr1 Pointer to the source location.
 */
void copy_paste_ptr(data_structure *data, char** ptr, char** ptr1);

/**
 * @brief Parses the input token to extract an integer index value.
 * 
 * Extracts an integer index value from the input token and stores it in the variable 'index'.
 * It handles negative indices as well.
 * 
 * @param token Pointer to the input token containing the index value as a string.
 * @param index Pointer to the variable where the parsed index will be stored.
 */
void create_index(char *token, int* index);

/**
 * @brief Extracts and calculates the sum values based on the data type.
 * 
 * Processes the input token and calculates the sum values 
 * based on the data type specified in the data_structure.
 * 
 * @param data The data_structure containing the header and data type information.
 * @param token The input token to extract integer values from.
 * @param total_bytes A pointer to an unsigned integer to store the total number of bytes.
 * @param s1_8 A pointer to an int8_t variable to store the first sum value (for type 1).
 * @param s2_8 A pointer to an int8_t variable to store the second sum value (for type 1).
 * @param s1_32 A pointer to an int32_t variable to store the first sum value (for type 2 and 3).
 * @param s2_32 A pointer to an int32_t variable to store the second sum value (for type 2 and 3).
 * @param s1_16 A pointer to an int16_t variable to store the first sum value (for type 2).
 */
void create_sums(data_structure *data, char *token, ui *total_bytes,
    int8_t *s1_8, int8_t *s2_8,int32_t *s1_32, int32_t *s2_32, int16_t *s1_16);

#endif /* _UTILS_H_ */
