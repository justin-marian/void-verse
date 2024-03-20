#include "utils/structs.h"
#include "data_operations/add.h"
#include "data_operations/delete.h"
#include "data_operations/find.h"

int main(void) {
    // Initialize variables
    void* arr = NULL;
    int len = 0;

    ui total_bytes;
    int index;
    i16 s1_16;
    i8 s1_8, s2_8;
    i32 s1_32, s2_32;

    // Allocate memory for the command buffer
    char* cmd = malloc(256 * sizeof(char));

    // Read the first command from stdin
    fgets(cmd, 256, stdin);
    cmd[strlen(cmd) - 1] = '\0';

    // Main loop to process commands until "exit" is entered
    while (strcmp(cmd, "exit")) {
        // Tokenize the command
        char* token = strtok(cmd, " ");
        char* dedicator;
        char* dedicat;

        // Check the command type
        if (!strcmp(token, "insert")) {
            // Handle "insert" command

            // Initialize variables for data insertion
            total_bytes = 0;
            s1_8 = s2_8 = s1_16 = s1_32 = s2_32 = 0;

            // Allocate memory for the data structure and its header
            data_structure* data = malloc(sizeof(data_structure));
            data->header = malloc(sizeof(head));

            // Parse and store data type in the header
            token = strtok(NULL, " ");
            data->header->type = *token;

            // Parse and store dedicator string
            token = strtok(NULL, " ");
            dedicator = malloc((strlen(token) + 1) * sizeof(char));
            memcpy(dedicator, token, strlen(token) + 1);
            total_bytes += strlen(token) + 1;

            // Calculate sums based on the data type
            create_sums(data, token, &total_bytes, &s1_8, &s2_8, &s1_32, &s2_32, &s1_16);

            // Parse and store dedicat string
            token = strtok(NULL, " ");
            dedicat = malloc((strlen(token) + 1) * sizeof(char));
            memcpy(dedicat, token, strlen(token) + 1);
            total_bytes += strlen(token) + 1;

            // Set the length of the data and allocate memory for data content
            data->header->len = total_bytes;
            data->data = malloc(total_bytes * sizeof(char));
            uc* ptr_elem_data = data->data;

            // Copy dedicator string to data content
            memcpy(ptr_elem_data, dedicator, strlen(dedicator) + 1);
            ptr_elem_data += strlen(dedicator) + 1;

            // Based on the data type, copy additional elements to data content
            if (data->header->type == '1') {
                *(i8*)ptr_elem_data = s1_8;
                ptr_elem_data += sizeof(i8);
                *(i8*)ptr_elem_data = s2_8;
                ptr_elem_data += sizeof(i8);
            }

            if (data->header->type == '2') {
                *(i16*)ptr_elem_data = s1_16;
                ptr_elem_data += sizeof(i16);
                *(i32*)ptr_elem_data = s2_32;
                ptr_elem_data += sizeof(i32);
            }

            if (data->header->type == '3') {
                *(i32*)ptr_elem_data = s1_32;
                ptr_elem_data += sizeof(i32);
                *(i32*)ptr_elem_data = s2_32;
                ptr_elem_data += sizeof(i32);
            }

            // Copy dedicat string to data content
            memcpy(ptr_elem_data, dedicat, strlen(dedicat) + 1);

            // Add the data to the array
            add_last(&arr, &len, data);

            // Free allocated memory for data structure and strings
            free(data->header);
            free(data->data);
            free(data);
            free(dedicator);
            free(dedicat);
        }

        if (!strcmp(token, "insert_at")) {
            // Handle "insert_at" command

            // Initialize variables for data insertion
            total_bytes = 0, index = 0;
            s1_8 = s2_8 = s1_16 = s1_32 = s2_32 = 0;

            // Allocate memory for the data structure and its header
            data_structure* data = malloc(sizeof(data_structure));
            data->header = malloc(sizeof(head));

            // Parse and store the index where data should be inserted
            create_index(token, &index);

            // Parse and store data type in the header
            token = strtok(NULL, " ");
            data->header->type = *token;

            // Parse and store dedicator string
            token = strtok(NULL, " ");
            dedicator = malloc((strlen(token) + 1) * sizeof(char));
            memcpy(dedicator, token, strlen(token) + 1);
            total_bytes += strlen(token) + 1;

            // Calculate sums based on the data type
            create_sums(data, token, &total_bytes, &s1_8, &s2_8, &s1_32, &s2_32, &s1_16);

            // Parse and store dedicat string
            token = strtok(NULL, " ");
            dedicat = malloc((strlen(token) + 1) * sizeof(char));
            memcpy(dedicat, token, strlen(token) + 1);
            total_bytes += strlen(token) + 1;

            // Set the length of the data and allocate memory for data content
            data->header->len = total_bytes;
            data->data = malloc(total_bytes * sizeof(char));
            uc* ptr_elem_data = data->data;

            // Copy dedicator string to data content
            memcpy(ptr_elem_data, dedicator, strlen(dedicator) + 1);
            ptr_elem_data += strlen(dedicator) + 1;

            // Based on the data type, copy additional elements to data content
            if (data->header->type == '1') {
                *(i8*)ptr_elem_data = s1_8;
                ptr_elem_data += sizeof(i8);
                *(i8*)ptr_elem_data = s2_8;
                ptr_elem_data += sizeof(i8);
            }

            if (data->header->type == '2') {
                *(i16*)ptr_elem_data = s1_16;
                ptr_elem_data += sizeof(i16);
                *(i32*)ptr_elem_data = s2_32;
                ptr_elem_data += sizeof(i32);
            }

            if (data->header->type == '3') {
                *(i32*)ptr_elem_data = s1_32;
                ptr_elem_data += sizeof(i32);
                *(i32*)ptr_elem_data = s2_32;
                ptr_elem_data += sizeof(i32);
            }

            // Copy dedicat string to data content
            memcpy(ptr_elem_data, dedicat, strlen(dedicat) + 1);

            // Add the data to the array at the specified index
            add_at(&arr, &len, data, index);

            // Free allocated memory for data structure and strings
            free(data->header);
            free(data->data);
            free(data);
            free(dedicator);
            free(dedicat);
        }

        if (!strcmp(token, "delete_at")) {
            // Handle "delete_at" command

            // Parse and store the index to delete data at
            index = 0;
            create_index(token, &index);

            // Delete data at the specified index
            delete_at(&arr, &len, index);
        }

        if (!strcmp(token, "find")) {
            // Handle "find" command

            // Parse and store the index to find data at
            index = 0;
            create_index(token, &index);

            // Find and print data at the specified index
            find(arr, len, index);
        }

        if (!strcmp(token, "print")) {
            // Handle "print" command

            // Initialize a pointer to traverse the array
            char* pointer_elem = arr;

            // Loop through the array and print data
            for (int elem = 0; elem < len; elem++) {
                printf("Tipul %c\n", *pointer_elem);

                if (*pointer_elem == '1') {
                    pointer_elem += (1 + sizeof(ui));
                    printf("%s pentru %s\n", (char*)pointer_elem, (char*)(pointer_elem + strlen(pointer_elem) + 1 + 2 * sizeof(i8)));
                    pointer_elem += (strlen(pointer_elem) + 1);

                    printf("%" PRId8 "\n", *(i8*)pointer_elem);
                    pointer_elem += sizeof(i8);
                    printf("%" PRId8 "\n", *(i8*)pointer_elem);
                    pointer_elem += sizeof(i8);
                }

                if (*pointer_elem == '2') {
                    pointer_elem += (1 + sizeof(ui));
                    printf("%s pentru %s\n", (char*)pointer_elem, (char*)(pointer_elem + strlen(pointer_elem) + 1 + sizeof(i16) + sizeof(i32)));
                    pointer_elem += (strlen(pointer_elem) + 1);

                    printf("%" PRId16 "\n", *(i16*)pointer_elem);
                    pointer_elem += sizeof(i16);
                    printf("%" PRId32 "\n", *(i32*)pointer_elem);
                    pointer_elem += sizeof(i32);
                }

                if (*pointer_elem == '3') {
                    pointer_elem += (1 + sizeof(ui));
                    printf("%s pentru %s\n", (char*)pointer_elem, (char*)(pointer_elem + strlen(pointer_elem) + 1 + 2 * sizeof(i32)));
                    pointer_elem += (strlen(pointer_elem) + 1);

                    printf("%" PRId32 "\n", *(i32*)pointer_elem);
                    pointer_elem += sizeof(i32);
                    printf("%" PRId32 "\n", *(i32*)pointer_elem);
                    pointer_elem += sizeof(i32);
                }

                pointer_elem += (strlen(pointer_elem) + 1);
                printf("\n");
            }
        }

        // Read the next command from stdin
        fgets(cmd, 256, stdin);
        cmd[strlen(cmd) - 1] = '\0';
    }

    // Free allocated memory for the array and the command buffer
    free(arr);
    free(cmd);

    // Return success status
    return EXIT_SUCCESS;
}
