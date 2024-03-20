# Void Verse

This project is a simple void data pointers manager designed to streamline the process of commands. It allows to categorize dedications based on the value amount in the ***dedication***, recording both the name of the dedicator and the dedicatee. The program handles `insertion`, `deletion`, `finding`, and `printing` of dedications.

## Structures and Storage

### `head`

- `type`: The type of data stored.
- `len`: Total length of the data.

### `data_structure`

- `header`: Pointer to the header of the data.
- `data`: Pointer to the actual data.

Data will be stored diversely using types from the `<inttypes.h>` header. The format for storing data depends on the type specified in the header:

For printing various integer types, **special macros** need to be used:

```c
    printf("%"PRId8"\n", val) // where val is an int8_t
    printf("%"PRId16"\n", val) // where val is an int16_t
    printf("%"PRId32"\n", val) // where val is an int32_t
```

## Usage

The program reads commands from the standard input until the `"exit"` command is received.

Below are the supported commands:

`exit`: Terminates the program after deallocating memory.

- The program cleans up allocated memory and gracefully exits.

`add_last`: Adds a dedication to the end of the vector.

- Appends a **new dedication** to the end of the vector and increases length.

`add_at`: Inserts a dedication at a specified `index` in the vector.

- It inserts a **dedication** at a specified index in the vector, ensuring that the index is not out of bounds.

`find`: Retrieves and displays the **dedication** at a specified `index`.

- Displays the dedication at the specified index in the vector.

`delete_at`: Deletes the **dedication** at a specified `index` from the vector.

- Removes the dedication at the specified index from the vector and the remaining elements are properly shifted.

`print`: Prints **all dedications** in the vector.

- Prints each dedication according to the specified format.

```bash
    Type <type header>
    <First Name> pentru <Second Name>
    <First Banknote Value>
    <Second Banknote Value>
    (space after each printed element)
```

## Memory Management

Memory management is crucial for the project's success. It consists of two main parts:

1) **Correct Memory Allocation**: Memory should be dynamically allocated for all strings and structures used.
   - Static declarations **ARE NOT PERMITED**.
2) **Proper Memory Deallocation**: Memory should be deallocated correctly and completely.
   - It should not display any invalid reads or memory leaks. Errors related to redirection will not be penalized.

To ensure proper memory management, Valgrind will be used for memory leak detection and debugging. The following command can be used to run Valgrind:

```bash
valgrind –leak-check=full –show-leak-kinds=all –track-origins=yes ./main
```

A predefined test command `make check` is available to ease the testing process.
