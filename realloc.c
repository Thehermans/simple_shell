#include "shell.h"

/**
 * fillMemory - Fills memory with a constant byte
 * @memory: Pointer to the memory area
 * @byte: The byte to fill @memory with
 * @size: The number of bytes to be filled
 * Return: A pointer to the filled memory area
 */
char *fillMemory(char *memory, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
    {
        memory[i] = byte;
    }
    return memory;
}

/**
 * freeStringArray - Frees an array of strings
 * @stringArray: Array of strings
 */
void freeStringArray(char **stringArray)
{
    char **currentPointer = stringArray;

    if (!stringArray)
    {
        return;
    }
    while (*stringArray)
    {
        free(*stringArray++);
    }
    free(currentPointer);
}

/**
 * reallocateMemory - Reallocates a block of memory
 * @previousPointer: Pointer to the previous malloc'ed block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the old block if reallocation fails, else pointer to the new block
 */
void *reallocateMemory(void *previousPointer, unsigned int oldSize, unsigned int newSize)
{
    char *newPointer;

    if (!previousPointer)
    {
        return malloc(newSize);
    }
    if (!newSize)
    {
        free(previousPointer);
        return NULL;
    }
    if (newSize == oldSize)
    {
        return previousPointer;
    }

    newPointer = malloc(newSize);
    if (!newPointer)
    {
        return NULL;
    }

    oldSize = oldSize < newSize ? oldSize : newSize;
    while (oldSize--)
    {
        newPointer[oldSize] = ((char *)previousPointer)[oldSize];
    }
    free(previousPointer);
    return newPointer;
}

