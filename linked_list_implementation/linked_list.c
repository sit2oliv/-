#include "linked_list.h"

PixelInfo MakeSet(int x_idx)
{
    PixelInfo res = (PixelInfo)calloc(sizeof(struct PixelInfoInner), 1);
    FALSE_ERROR(res, "memory alloc failed!\n");
    return res;
}
KindSet FindSet(int x_idx, PixelInfo *arr)
{
    if (!arr[x_idx])
        return 0;
    return arr[x_idx]->head;
}
KindSet makeKindSet()
{
    KindSet res = (KindSet)calloc(sizeof(struct KindSetInner), 1);
    FALSE_ERROR(res, "memory alloc failed!\n");
    return res;
}
void Union(int x_idx, int y_idx, PixelInfo *arr)
{
    KindSet kind_x = FindSet(x_idx, arr);
    KindSet kind_y = FindSet(y_idx, arr);
    PixelInfo pixel_x = arr[x_idx];
    PixelInfo pixel_y = arr[y_idx];

    if (!kind_x)
    {
        assert(!pixel_x->next);
    }
    if (!kind_y)
    {
        assert(!pixel_y->next);
    }

    if (kind_x == NULL && kind_y == NULL)
    {
        KindSet kind_set = makeKindSet();
        pixel_x->head = kind_set;
        pixel_y->head = kind_set;
        pixel_x->next = pixel_y;

        kind_set->head = pixel_x;
        kind_set->tail = pixel_y;
        kind_set->pixel_count = 2;
    }
    else if (kind_x && kind_y == NULL)
    {
        assert(pixel_y->next == 0);
        kind_x->tail->next = pixel_y;
        kind_x->tail = pixel_y;

        pixel_y->head = kind_x;
        kind_x->pixel_count++;
    }
    else if (kind_x == NULL && kind_y)
    {
        assert(pixel_x->next == 0);
        kind_y->tail->next = pixel_x;
        kind_y->tail = pixel_x;
        pixel_x->head = kind_y;
        kind_y->pixel_count++;
    }
    else
    {
        if (kind_x == kind_y)
            return;
        if (kind_y->pixel_count <= kind_x->pixel_count)
        {
        }
        else
        {
            //swap kind_x and kind_y
            KindSet tmp = kind_x;
            kind_x = kind_y;
            kind_y = tmp;
        }
        kind_x->tail->next = kind_y->head;
        kind_x->tail = kind_y->tail;
        PixelInfo cur = kind_y->head;
        while (cur)
        {
            cur->head = kind_x;
            cur = cur->next;
        }
        kind_x->pixel_count += kind_y->pixel_count;
        free(kind_y);
    }
}

void analyzeImage(Matrix mat, PixelInfo **parr)
{
    *parr = (PixelInfo *)calloc(sizeof(PixelInfo) * mat->height * mat->width, 1);
    FALSE_ERROR(*parr, "memory alloc failed!\n");
    PixelInfo *arr = *parr;
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

    //free(arr);
}

void cleanKindSet(KindSet ks)
{
    if (ks)
    {
        free(ks->color);
        free(ks);
    }
}

void cleanPixelArr(PixelInfo *pixelArr, int width, int height)
{
    int total = width * height;
    for (int i = 0; i < total; i++)
    {
        if (!pixelArr[i])
            continue;
        KindSet x = pixelArr[i]->head;
        if (x)
        {
            PixelInfo cur = x->head;
            while (cur)
            {
                cur->head = 0;
                cur = cur->next;
            }
        }
        cleanKindSet(x);
    }
}