#include "dr_shell.h"


s#include "my_shell.h"

/**
 * updateLineBuffer - Assigns the line buffer for getLine function.
 * @lineBuffer: Pointer to the buffer storing the input string.
 * @lineSize: Size of the line buffer.
 * @tempBuffer: Temporary buffer containing read characters.
 * @tempSize: Size of the temporary buffer.
 */
void updateLineBuffer(char **lineBuffer, size_t *lineSize, char *tempBuffer, size_t tempSize) {
    if (*lineBuffer == NULL) {
        if (tempSize > BUFFERSIZE)
            *lineSize = tempSize;
        else
            *lineSize = BUFFERSIZE;

        *lineBuffer = tempBuffer;
    } else if (*lineSize < tempSize) {
        if (tempSize > BUFFERSIZE)
            *lineSize = tempSize;
        else
            *lineSize = BUFFERSIZE;

        *lineBuffer = tempBuffer;
    } else {
        stringCopy(*lineBuffer, tempBuffer);
        free(tempBuffer);
    }
}

/**
 * getLine - Read input from a stream.
 * @lineBuffer: Buffer that stores the input.
 * @lineSize: Size of lineBuffer.
 * @stream: Stream to read from.
 * Return: The number of bytes read.
 */
ssize_t getLine(char **lineBuffer, size_t *lineSize, FILE *stream) {
    int bytesRead;
    static ssize_t bytesReadTotal;
    ssize_t returnValue;
    char *tempBuffer;
    char currentChar = 'z';

    if (bytesReadTotal == 0)
        fflush(stream);
    else
        return -1;

    bytesReadTotal = 0;
    tempBuffer = malloc(sizeof(char) * BUFFERSIZE);

    if (tempBuffer == 0)
        return -1;

    while (currentChar != '\n') {
        bytesRead = read(STDIN_FILENO, &currentChar, 1);

        if (bytesRead == -1 || (bytesRead == 0 && bytesReadTotal == 0)) {
            free(tempBuffer);
            return -1;
        }

        if (bytesRead == 0 && bytesReadTotal != 0) {
            bytesReadTotal++;
            break;
        }

        if (bytesReadTotal >= BUFFERSIZE)
            tempBuffer = reallocateMemory(tempBuffer, bytesReadTotal, bytesReadTotal + 1);

        tempBuffer[bytesReadTotal] = currentChar;
        bytesReadTotal++;
    }

    tempBuffer[bytesReadTotal] = '\0';
    updateLineBuffer(lineBuffer, lineSize, tempBuffer, bytesReadTotal);
    returnValue = bytesReadTotal;

    if (bytesRead != 0)
        bytesReadTotal = 0;

    return returnValue;
}
