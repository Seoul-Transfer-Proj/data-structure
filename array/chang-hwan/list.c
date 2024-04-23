#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{
    // 1. 배열 A: 길이가 3인 int형 배열(포인터) 생성.
    int *arrayA = malloc(3 * sizeof(int));

    // 메모리가 할당되지 않았다면 프로그램 종료.
    if (arrayA == NULL) 
    {
        return 1;
    }

    arrayA[0] = 1;
    arrayA[1] = 2;
    arrayA[2] = 3;
    // 해당 포인터(배열)의 주소에 직접 접근해 값을 할당하는 방법
        // *arrayA = 1;
        // *(arrayA + 1) = 2;
        // *(arrayA + 2) = 3;

    arrayA = realloc(arrayA, 4 * sizeof(int));
    arrayA[3] = 4;

    for (int i = 0; i < 4; i++)
    {
         printf("배열 A의 %i번째 값: %i\n", i, *(arrayA + i));
    }

    free(arrayA);
}