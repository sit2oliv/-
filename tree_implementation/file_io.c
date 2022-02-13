#include "file_io.h"
#include "tree.h"

Color makeRandomColor()
{
    Color col = (Color)calloc(sizeof(struct ColorInner), 1);
    FALSE_ERROR(col, "memory alloc failed!\n");
    col->R = rand() % 255;
    col->G = rand() % 255;
    col->B = rand() % 255;
    return col;
};

Matrix makeMatrix(int width, int height)
{
    Matrix mat = (Matrix)calloc(sizeof(struct MatrixInner), 1);
    FALSE_ERROR(mat, "memory alloc failed!\n");
    mat->width = width;
    mat->height = height;
    int total = width * height;
    mat->content = (char *)calloc(sizeof(char) * total, 1);
    FALSE_ERROR(mat->content, "memory alloc failed!\n");
    return mat;
}

void cleanMatrix(Matrix mat)
{
    free(mat->content);
    free(mat);
}

Matrix Read(const char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        printf("can not open %s\n", file_name);
        exit(1);
    }
    char buffer[MAX_BYTES] = {0};
    if (!fgets(buffer, MAX_BYTES, fp))
    {
        printf("read error 1!\n");
        exit(1);
    }
    if (strncmp(buffer, "P1", 2) != 0)
    {
        printf("read error 2!\n");
        exit(1);
    }
    int width = 0;
    int height = 0;
    fscanf(fp, "%d %d", &width, &height);
    if (width <= 0 || height <= 0)
    {
        printf("read error 3!\n");
        exit(1);
    }
    int total = width * height;
    Matrix mat = makeMatrix(width, height);
    char chr = 0;
    int count = 0;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int i = r * width + c;
            while ((chr = fgetc(fp)) != EOF)
            {
                if (chr == ZERO || chr == ONE)
                {
                    mat->content[i] = chr;
                    count++;
                    break;
                }
            }
        }
    }
    if (count != total)
    {
        printf("read error 4!\n");
        exit(1);
    }
    return mat;
}

Matrix Generate(int width, int height)
{
    assert(width >= 0 && height >= 0);
    Matrix mat = makeMatrix(width, height);
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int i = r * width + c;
            mat->content[i] = rand() % 2 == 0 ? ZERO : ONE;
        }
    }
    return mat;
}

void Write(const char *file_name, Matrix mat, DSJSetNode *arr)
{
    FILE *fp = fopen(file_name, "w");
    if (!fp)
    {
        printf("can not open %s\n", file_name);
        exit(1);
    }
    fprintf(fp, "%s\n", "P3");
    fprintf(fp, "%d %d\n", mat->width, mat->height);
    fprintf(fp, "%d\n", 255);
    int i_count = 0;
    for (int row = 0; row < mat->height; row++)
    {
        for (int col = 0; col < mat->width; col++)
        {
            i_count++;
            if (i_count % 70 == 0)
            {
                fprintf(fp, "\n");
            }
            int i = row * mat->width + col;
            DSJSetNode kind = FindSet(arr[i]);
            if (!kind)
            {
                fprintf(fp, "0 0 0 ");
            }
            else
            {
                if (!kind->color)
                {
                    kind->color = makeRandomColor();
                }
                fprintf(fp, "%d %d %d ", (int)kind->color->R, (int)kind->color->G, (int)kind->color->B);
            }
        }
    }
    fclose(fp);
}



