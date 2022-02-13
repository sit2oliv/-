#ifndef __TREE_H_
#define __TREE_H_
#include "file_io.h"
/*
    a disjoint tree node
*/
typedef struct DSJSetNodeInner
{
    int rank;
    // parent node
    struct DSJSetNodeInner *p;
    Color color;
} * DSJSetNode;
/*
    make a disjoint tree node
    k = row * width + column
*/
DSJSetNode MakeSet(int k);
/*
    find the kind set of x
*/
DSJSetNode FindSet(DSJSetNode x);
/*
    union index1 and index2, with a node array.
*/
void Union(int index1, int index2, DSJSetNode* nodeArr);
/*
    analyze all neighbour relationship 
*/
void analyzeImage(Matrix mat, DSJSetNode **pnodeArr);
/*
    write the image matrix to the file
*/
void Write(const char *file_name, Matrix mat, DSJSetNode *nodeArr);
/*
    clean all tree node.
*/
void cleanNodeArr(DSJSetNode* nodeArr, int width, int height);

#endif //__TREE_H_