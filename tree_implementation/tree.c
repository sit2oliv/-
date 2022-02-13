#include "tree.h"
#include <stdlib.h>
#include "file_io.h"

DSJSetNode MakeSet(int k)
{
    DSJSetNode res = (DSJSetNode)calloc(sizeof(struct DSJSetNodeInner), 1);
    res->rank = 0;
    res->p = 0;
    res->p = res;
    return res;
}

DSJSetNode FindSet(DSJSetNode x)
{
    if(!x) return NULL;
    if (x != x->p)
        x->p = FindSet(x->p);
    return x->p;
}

static void Link(DSJSetNode x, DSJSetNode y)
{
    if (x->rank > y->rank)
        y->p = x;
    else
    {
        x->p = y;
        if (x->rank == y->rank)
            y->rank = y->rank + 1;
    }
}

static void SetUnionInner(DSJSetNode x, DSJSetNode y)
{
    Link(FindSet(x), FindSet(y));
}

void Union(int index1, int index2, DSJSetNode* nodeArr)
{
    if(!nodeArr[index1] || !nodeArr[index2])
        return;
    SetUnionInner(nodeArr[index1], nodeArr[index2]);
}

void analyzeImage(Matrix mat, DSJSetNode **pnodeArr)
{
    *pnodeArr = (DSJSetNode *)calloc(sizeof(DSJSetNode) * mat->height * mat->width, 1);
    FALSE_ERROR(*pnodeArr, "memory alloc failed!\n");
    DSJSetNode *arr = *pnodeArr;
    {
        for (int row = 0; row < mat->height; row++)
        {
            for (int col = 0; col < mat->width; col++)
            {
                int i = row * mat->width + col;
                if (mat->content[i] == WHITE)
                {
                    arr[i] = MakeSet(i);
                }
				else
				{
					arr[i] = 0;
				}
            }
        }
    }

    for (int row = 0; row < mat->height; row++)
    {
        for (int col = 0; col < mat->width; col++)
        {
            int neighborrs[] = {row - 1, row, row, row + 1};
            int neighborcs[] = {col, col - 1, col + 1, col};
            int i = row * mat->width + col;
            for (int k = 0; k < 4; k++)
            {
                int nr = neighborrs[k];
                int nc = neighborcs[k];
                if (nr < 0 || nr >= mat->height)
                    continue;
                if (nc < 0 || nc >= mat->width)
                    continue;
                int ni = nr * mat->width + nc;
                if (mat->content[i] == WHITE && mat->content[ni] == mat->content[i])
                {
                    Union(i, ni, arr);
                }
            }
        }
    }
}

void cleanNodeArr(DSJSetNode* nodeArr, int width, int height)
{
    int total = width * height;
    for(int i=0; i<total; i++)
    {
		if (!nodeArr[i]) continue;
        free(nodeArr[i]->color);
        free(nodeArr[i]);
    }
    free(nodeArr);
}