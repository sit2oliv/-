#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_
#include "file_io.h"

typedef struct PixelInfoInner* PixelInfo;
/*
    a pixel linked list node 
*/
typedef struct KindSetInner
{
    PixelInfo head;
    PixelInfo tail;
    Color color;
    int pixel_count;
}*KindSet;
/*
    a pixel kind node
*/
struct PixelInfoInner
{
    struct KindSetInner* head;
    struct PixelInfoInner* next;
}; 

/*
    x_idx = row_idx * height + column_idx
*/
PixelInfo MakeSet(int x_idx);
/*
    get the kind node with x_idx
*/    
KindSet FindSet(int x_idx, PixelInfo* arr);
/*
    union x_idx and y_idx with arr
*/
void Union(int x_idx,int y_idx, PixelInfo* arr);
/*
    analyze all neighbour relationship 
*/
void analyzeImage(Matrix mat, PixelInfo **parr);
/*
    write the image matrix to the file
*/
void Write(const char *file_name, Matrix mat, PixelInfo *arr);
/*
    clean all pixel node.
*/
void cleanPixelArr(PixelInfo* pixelArr, int width, int height);
#endif//__LINKED_LIST_H_