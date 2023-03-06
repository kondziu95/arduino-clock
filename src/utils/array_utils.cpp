#include "array_utils.h"

void splitArray(char *source, int sourceLength, char *first, char *second, int middleIndex)
{
    // Copy the second half of the source array to the second output array
    memcpy(second, &source[middleIndex], sourceLength - middleIndex);

    // Add a null terminator to the end of the second output array
    second[sourceLength - middleIndex] = '\0';

    // Copy the first half of the source array to the first output array
    memcpy(first, source, middleIndex);

    // Add a null terminator to the end of the first output array
    first[middleIndex] = '\0';
}
