#include "linked_list.h"
#include <string.h>
/*
    test dirver file
*/
void test(const char *input_file, const char *output_file)
{
    Matrix mat = Read(input_file);
    {
        PixelInfo *pixelArr = 0;
        analyzeImage(mat, &pixelArr);
        Write(output_file, mat, pixelArr);
        cleanPixelArr(pixelArr, mat->width, mat->height);
    }
    cleanMatrix(mat);
}

void test_random(int width, int height)
{
    Matrix mat = Generate(width, height);
    {
        PixelInfo *pixelArr = 0;
        analyzeImage(mat, &pixelArr);
        cleanPixelArr(pixelArr, mat->width, mat->height);
    }
    cleanMatrix(mat);
}

int main(int argc, char **argv)
{
    int default_test = 0;
    int sepcify_test = 0;
    int generate_test = 0;
    const char *input_path = 0;
    const char *output_path = 0;
    int input_width = 0;
    int input_height = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-default") == 0)
        {
            default_test = 1;
        }
        else if (strcmp(argv[i], "-specify") == 0)
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
    // printf("default_test:%d\n", default_test);
    // printf("sepcify_test:%d\n", sepcify_test);
    // printf("generate_test:%d\n", generate_test);
    // printf("input_path:%s\n", input_path?input_path:"");
    // printf("output_path:%s\n", output_path?output_path:"");
    // printf("input_width:%d\n", input_width);
    // printf("input_height:%d\n", input_height);
    if (default_test)
    {
        const char *fileNames[] = {
            "biang.pbm",
            "carte_monde.pbm",
            "celtique.pbm",
            "celtique.pbm",
            "vigne.pbm"};
        const char *outfileNames[] = {
            "biang_linked_list.ppm",
            "carte_monde_linked_list.ppm",
            "celtique_linked_list.ppm",
            "celtique_linked_list.ppm",
            "vigne_linked_list.ppm"};
        const int fileCount = sizeof(fileNames) / sizeof(fileNames[0]);

        for (int i = 0; i < fileCount; i++)
        {
            test(fileNames[i], outfileNames[i]);
        }
    }
    else if (sepcify_test && input_path && output_path)
    {
        test(input_path, output_path);
    }
    else if (generate_test && input_width>0 && input_height>0)
    {
        test_random(input_width, input_height);
    }
}