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

    // 2. 배열 B: 길이가 4인 int형 배열을 생성할 임시 메모리 공간 할당.
    int *arrayB = malloc(4 * sizeof(int));

    // 메모리가 할당되지 않았다면 프로그램 종료
    if (arrayB == NULL)
    {
        return 1;
    }

    // 3. 배열 A의 값들을 배열 B에 복사.
    for (int i = 0; i < 3; i++)
    {
        arrayB[i] = arrayA[i];
    }
    arrayB[3] = 4;

    // 배열 A에 길이가 4인 int 배열 할당.
    arrayA = arrayB;

    free(arrayB);

    for (int i = 0; i < 4; i++)
    {
         printf("배열 A의 %i번째 값: %i\n", i, *(arrayA + i));
    }

    free(arrayA);
}