#include "find.h"

// Find the index of a data structure with the given dedicator string
void find(void *data_block, int len, int index) {
    char* find = data_block;

    // Check if the index is within the valid range
    if (len < index || 0 > index) return;

    // Move to the specified index in the data_block
    for (int elem = 0; elem < index; elem++) {
        find++;
        find += (*((ui*)find) + sizeof(ui));
    }

    // Print data based on the type indicated by the first byte (*find)
    printf("Tipul %c\n", *find);

    if (*find == '1') {
        // Read and print data for type 1
        find += (1 + sizeof(ui));
        printf("%s pentru %s\n", \
            (char*)find, (char*)(find + strlen(find) + 2 * sizeof(i8) + 1));
        find += (strlen(find) + 1);

        printf("%"PRId8"\n", *(i8*)find);
        find += sizeof(i8);

        printf("%"PRId8"\n", *(i8*)find);
        find += sizeof(i8);
    } else if (*find == '2') {
        // Read and print data for type 2
        find += (1 + sizeof(ui));
        printf("%s pentru %s\n", \
            (char*)find, (char*)(find + strlen(find) + sizeof(i16) + sizeof(i32) + 1));
        find += (strlen(find) + 1);

        printf("%"PRId16"\n", *(i16*)find);
        find += sizeof(i16);

        printf("%"PRId32"\n", *(i32*)find);
        find += sizeof(i32);
    } else if (*find == '3') {
        // Read and print data for type 3
        find += (1 + sizeof(ui));
        printf("%s pentru %s\n", \
            (char*)find, (char*)(find + strlen(find) + 2 * sizeof(i32) + 1));
        find += (strlen(find) + 1);

        printf("%"PRId32"\n", *(i32*)find);
        find += sizeof(i32);

        printf("%"PRId32"\n", *(i32*)find);
        find += sizeof(i32);
    }

    printf("\n");
}
