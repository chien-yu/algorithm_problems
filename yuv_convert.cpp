#include <stdlib.h> 
#include <stdio.h>

int interleaveToLinear(int* pIn, int w, int h, int* pOut)
{
    int* pOutToV = pOut + w*h;
    int* pOutToU = pOut;
    int* ptr = pIn;

    for (int i = 0; i < w*h*2; i++)
    {
        int d = ptr - pIn;
        if (d%2 == 0)
        {
            *pOutToU = *ptr;
            pOutToU++;
        }
        else
        {
            *pOutToV = *ptr;
            pOutToV++;
        }
        ptr++;
    }

    return 0;
}

int main()
{
    int w = 4;
    int h = 6;
    int* pInterleaved = static_cast<void*>(malloc(w*h*2*sizeof(int)));
    // printf("hello\n");
    for (int i = 0; i < w*h*2; i++)
    {
        pInterleaved[i] = i;
    }


    int* pLinear = (int*)malloc(w*h*2*sizeof(int));
    interleaveToLinear(pInterleaved, w, h, pLinear);

    for (int i = 0; i < w*h*2; i++)
    {
        printf("%d ", pLinear[i]);
    }
    printf("\n");

    //testing
    for (int i = 0; i < w*h; i++)
    {
        if (pLinear[i] != i*2)
            printf("wrong index %d ", i);
    }
    for (int i = 0; i < w*h; i++)
    {
        if ((pLinear[i+w*h]) != (i*2 + 1))
            printf("wrong index %d ", i);
    }

    return 0;
}