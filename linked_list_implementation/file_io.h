#ifndef __FILE_IO_H_
#define __FILE_IO_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_BYTES 1024

typedef struct ColorInner
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}*Color;
enum 
{
    ZERO = '0',
    ONE = '1',
    WHITE = ZERO,
    BLACK = ONE
};
/*
    use one-dimension array to represent a matrix
*/
typedef struct MatrixInner
{
    char* content;
    int width;
    int height;
}* Matrix;
/*
    useful macro to print error log and exit
*/
#define FALSE_ERROR(expr, error_message) \
{ \
    if(!expr) \
    { \
        char buffer[2048] = {0}; \
        snprintf(buffer, 2048, "%s %d %s\n", __FILE__, __LINE__, error_message); \
        exit(1); \
    } \
}
/*
    return a matrix from file_name
*/
Matrix Read(const char *file_name);
/*
    return a height * width matrix
*/
Matrix Generate(int width, int height);
/*
    clean the matrix
*/
void cleanMatrix(Matrix mat);

#endif//__FILE_IO_H_