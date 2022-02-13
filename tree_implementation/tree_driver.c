#include "tree.h"
#include <string.h>

/*
    test dirver file
*/

void test(const char *input_file, const char *output_file)
{
    Matrix mat = Read(input_file);
    {
        DSJSetNode *nodeArr = 0;
        analyzeImage(mat, &nodeArr);
        Write(output_file, mat, nodeArr);
        cleanNodeArr(nodeArr, mat->width, mat->height);
    }
    cleanMatrix(mat);
}

void test_random(int width, int height)
{
    Matrix mat = Generate(width, height);
    {
        DSJSetNode *nodeArr = 0;
        analyzeImage(mat, &nodeArr);
        cleanNodeArr(nodeArr, mat->width, mat->height);
    }
    cleanMatrix(mat);
}

int main(int argc, char **argv)
{
    int sepcify_test = 0;
    int generate_test = 0;
    const char *input_path = 0;
    const char *output_path = 0;
    int input_width = 0;
    int input_height = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-specify") == 0)
        {
            sepcify_test = 1;
        }
        else if (strcmp(argv[i], "-generate") == 0)
        {
            generate_test = 1;
        }
        else if (strcmp(argv[i], "-input") == 0 && (i + 1) < argc)
        {
            input_path = argv[i + 1];
        }
        else if (strcmp(argv[i], "-output") == 0 && (i + 1) < argc)
        {
            output_path = argv[i + 1];
        }
        else if (strcmp(argv[i], "-width") == 0 && (i + 1) < argc)
        {
            input_width = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-height") == 0 && (i + 1) < argc)
        {
            input_height = atoi(argv[i + 1]);
        }
    }
    if (sepcify_test && input_path && output_path)
    {
        test(input_path, output_path);
    }
    else if (generate_test && input_width>0 && input_height>0)
    {
        test_random(input_width, input_height);
    }
}