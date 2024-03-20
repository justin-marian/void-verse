#include "delete.h"

// Delete data structure at index from the array
int delete_at(void **arr, int *len, int index) {
    // Check if the index is within the valid range
    if (*len <= index || index < 0) return FAILED;

    // Initialize pointers to the element to be deleted, the next element, and the elements to move
    char *del_elem = *arr;
    for (int elem = 0; elem < index; elem++) {
        del_elem++;
        del_elem += (*((ui *)del_elem) + sizeof(ui));
    }

    char *next_element = del_elem;
    next_element++;
    next_element += (*((ui *)next_element) + sizeof(ui));

    char *mov_elem = del_elem;
    mov_elem++;
    mov_elem += (*((ui *)mov_elem) + sizeof(ui));

    int mov_bytes = 0;

    // Calculate the total number of bytes to move after the deleted element
    for (int elem = index + 1; elem < *len; elem++) {
        mov_elem++;
        mov_bytes += (HEAD_SIZE + *((ui *)mov_elem));
        mov_elem += (*((ui *)mov_elem) + sizeof(ui));
    }

    // Move the elements after the deleted element to fill the gap
    memmove(del_elem, next_element, mov_bytes * sizeof(char));

    *len = *len - 1;
    return SUCCED;
}
