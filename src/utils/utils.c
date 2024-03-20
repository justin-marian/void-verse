#include "utils.h"

// Passes the byte stream pointed by 'ptrTo', advancing the pointer 'len' times,
// Also advances the pointer to the next byte block after each iteration.
void pass_bytes(char **ptrTo, int *len) {
    for (int i = 0; i < *len; i++) {
        (*ptrTo)++;
        *ptrTo += sizeof(ui) + *(ui *)(*ptrTo);
    }
}

// Get the total size of data structures in the array
int getTotalBytes(void **arr, int len) {
    int total_bytes = 0;
    char *byte_ptr = *arr;

    for (int elem = 0; elem < len; elem++) {
        byte_ptr++;
        total_bytes += (HEAD_SIZE + *(ui *)byte_ptr);
        byte_ptr += (sizeof(ui) + *(ui *)byte_ptr);
    }

    return total_bytes;
}

// Copies data from 'ptrFrom' to 'ptrTo' based on the data type stored in 'data->header->type'.
void copy_paste_ptr(data_structure *data, char **ptrTo, char **ptrFrom) {
    if (data->header->type == '1') {
        int8_t value1, value2;
        // Copy int8_t from ptrFrom to ptrTo
        memcpy(&value1, *ptrFrom, sizeof(int8_t));
        *ptrFrom += sizeof(int8_t);
        memcpy(*ptrTo, &value1, sizeof(int8_t));
        *ptrTo += sizeof(int8_t);
        // Copy int8_t from ptrFrom to ptrTo
        memcpy(&value2, *ptrFrom, sizeof(int8_t));
        *ptrFrom += sizeof(int8_t);
        memcpy(*ptrTo, &value2, sizeof(int8_t));
        *ptrTo += sizeof(int8_t);
    } else if (data->header->type == '2') {
        int16_t value1;
        int32_t value2;
        // Copy int16_t from ptrFrom to ptrTo
        memcpy(&value1, *ptrFrom, sizeof(int16_t));
        *ptrFrom += sizeof(int16_t);
        memcpy(*ptrTo, &value1, sizeof(int16_t));
        *ptrTo += sizeof(int16_t);
        // Copy int32_t from ptrFrom to ptrTo
        memcpy(&value2, *ptrFrom, sizeof(int32_t));
        *ptrFrom += sizeof(int32_t);
        memcpy(*ptrTo, &value2, sizeof(int32_t));
        *ptrTo += sizeof(int32_t);
    } else if (data->header->type == '3') {
        int32_t value1, value2;
        // Copy int32_t from ptrFrom to ptrTo
        memcpy(&value1, *ptrFrom, sizeof(int32_t));
        *ptrFrom += sizeof(int32_t);
        memcpy(*ptrTo, &value1, sizeof(int32_t));
        *ptrTo += sizeof(int32_t);
        // Copy int32_t from ptrFrom to ptrTo
        memcpy(&value2, *ptrFrom, sizeof(int32_t));
        *ptrFrom += sizeof(int32_t);
        memcpy(*ptrTo, &value2, sizeof(int32_t));
        *ptrTo += sizeof(int32_t);
    }
}

// Parses the input token to extract an integer index value.
// Token contains non-numeric characters or is not well-formed, it exits with an error.
void create_index(char *token, int *index) {
    token = strtok(NULL, " ");
    int negative = 1;

    if (token[0] == '-') {
        negative = -1;
        token++;
    }

    *index = 0;
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] >= '0' && token[i] <= '9') {
            *index = *index * 10 + (token[i] - '0');
        } else { // Handle error : invalid token, non-numeric characters found.
            fprintf(stderr, "Error: Index must contain only numeric characters.\n");
            exit(1);
        }
        *index *= negative;
    }
}

// Calculates the sum values based on the data type specified in the data_structure.
void create_sums(data_structure *data, char *token, ui *total_bytes,
    int8_t *s1_8, int8_t *s2_8, int32_t *s1_32, int32_t *s2_32, int16_t *s1_16) {

    // Process data type '1'
    if (data->header->type == '1') {
        // Increment the total number of bytes for this data type
        *total_bytes += 2;
        // Extract and calculate the first integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s1_8 = *s1_8 * 10 + (token[elem] - '0');
            *s1_8 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s1_8 = *s1_8 * 10 + (token[elem] - '0');
        }

        // Extract and calculate the second integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s2_8 = *s2_8 * 10 + (token[elem] - '0');
            *s2_8 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s2_8 = *s2_8 * 10 + (token[elem] - '0');
        }

    }

    // Process data type '2'
    if (data->header->type == '2') {
        // Increment the total number of bytes for this data type
        *total_bytes += 6;
        // Extract and calculate the first integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s1_16 = *s1_16 * 10 + (token[elem] - '0');
            *s1_16 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s1_16 = *s1_16 * 10 + (token[elem] - '0');
        }

        // Extract and calculate the second integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s2_32 = *s2_32 * 10 + (token[elem] - '0');
            *s2_32 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s2_32 = *s2_32 * 10 + (token[elem] - '0');
        }

    }

    // Process data type '3'
    if (data->header->type == '3') {
        // Increment the total number of bytes for this data type
        *total_bytes += 8;
        // Extract and calculate the first integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s1_32 = *s1_32 * 10 + (token[elem] - '0');
            *s1_32 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s1_32 = *s1_32 * 10 + (token[elem] - '0');
        }

        // Extract and calculate the second integer value
        token = strtok(NULL, " ");
        if (token[0] == '-') {
            for (int elem = 1; elem < strlen(token); elem++)
                *s2_32 = *s2_32 * 10 + (token[elem] - '0');
            *s2_32 *= -1;
        } else {
            for (int elem = 0; elem < strlen(token); elem++)
                *s2_32 = *s2_32 * 10 + (token[elem] - '0');
        }
    }
}
