#include "add.h"

// Add a new data structure at the end of the array
int add_last(void **arr, int *len, data_structure *data) {
    char *curr_elem, *new_elem;
    char *add_data = data->data;

    // If the array is empty, allocate memory for the first data structure
    if (!*arr)
        *arr = malloc((data->header->len + HEAD_SIZE) * sizeof(char));

    int total_bytes = getTotalBytes(arr, *len);
    curr_elem = *arr;

    // Move to the end of the array
    for (int elem = 0; elem < *len; elem++) {
        curr_elem++;
        curr_elem += (*((ui *)curr_elem) + sizeof(ui));
    }

    // Reallocate memory for the new data structure
    void *new_array;
    new_array = realloc(*arr, (total_bytes + data->header->len + HEAD_SIZE) * sizeof(char));
    *arr = new_array;

    new_elem = *arr;

    // Move to the end of the array after reallocation
    for (int elem = 0; elem < *len; elem++) {
        new_elem++;
        new_elem += (*((ui *)new_elem) + sizeof(ui));
    }

    // Copy the new data structure into the array
    memcpy(new_elem, &data->header->type, sizeof(uc));
    new_elem++;
    *(ui *)new_elem = data->header->len;
    new_elem += sizeof(ui);

    memcpy(new_elem, add_data, (strlen(data->data) + 1) * sizeof(char));
    new_elem += (strlen(data->data) + 1) * sizeof(char);
    add_data += (strlen(data->data) + 1) * sizeof(char);

    copy_paste_ptr(data, &new_elem, &add_data);

    memcpy(new_elem, add_data, (strlen(add_data) + 1) * sizeof(char));

    *len = *len + 1;
    return SUCCED;
}

// Add a new data structure at a specific index in the array
int add_at(void **arr, int *len, data_structure *data, int index) {
    int total_bytes = getTotalBytes(arr, *len);
    int total_bytes_till_index = 0;
    char *byte_ptr = *arr;

    // If the index is within the current length of the array
    if (index < *len) {
        for (int elem = 0; elem < index; elem++) {
            byte_ptr++;
            total_bytes_till_index += (HEAD_SIZE + *(ui *)byte_ptr);
            byte_ptr += (sizeof(ui) + *(ui *)byte_ptr);
        }

        // Move the elements after the index to create space for the new data structure
        for (int elem = index; elem < *len; elem++) {
            byte_ptr++;
            total_bytes += (HEAD_SIZE + *(ui *)byte_ptr);
            byte_ptr += (sizeof(ui) + *(ui *)byte_ptr);
        }
    } else if (*len <= index) {
        // Move to the end of the array if the index is beyond the current length
        for (int elem = 0; elem < *len; elem++) {
            byte_ptr++;
            total_bytes += (HEAD_SIZE + *(ui *)byte_ptr);
            byte_ptr += (sizeof(ui) + *(ui *)byte_ptr);
        }
    }

    // Reallocate memory for the new data structure
    *arr = realloc(*arr, (total_bytes + data->header->len + HEAD_SIZE) * sizeof(char));
    char *elem_ptr = *arr, *data_ptr = data->data, *data_ptr1;

    if (*len <= index) {
        // If the index is beyond the current length, move to the end of the array
        for (int elem = 0; elem < *len; elem++) {
            elem_ptr++;
            elem_ptr += (sizeof(ui) + *(ui *)(elem_ptr));
        }
    } else if (index < *len) {
        // Move to the index where the new data structure needs to be added
        for (int elem = 0; elem < index; elem++) {
            elem_ptr++;
            elem_ptr += (sizeof(ui) + *(ui *)(elem_ptr));
        }

        // Move the elements after the index to create space for the new data structure
        data_ptr1 = elem_ptr;
        data_ptr1 += (HEAD_SIZE + data->header->len);
        memmove(data_ptr1, elem_ptr, (total_bytes - total_bytes_till_index) * sizeof(char));
    }

    // Copy the new data structure into the array
    memcpy(elem_ptr, &data->header->type, sizeof(uc));
    elem_ptr++;
    *(ui *)elem_ptr = data->header->len;
    elem_ptr += sizeof(ui);

    memcpy(elem_ptr, data_ptr, (strlen(data->data) + 1) * sizeof(char));
    elem_ptr += (strlen(data->data) + 1) * sizeof(char);
    data_ptr += (strlen(data->data) + 1) * sizeof(char);

    copy_paste_ptr(data, &elem_ptr, &data_ptr);

    memcpy(elem_ptr, data_ptr, (strlen(data_ptr) + 1) * sizeof(char));

    *len = *len + 1;
    return SUCCED;
}
