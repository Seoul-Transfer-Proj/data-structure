#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{
    // 1. 배열 A: 길이가 3인 int형 배열 생성.(값은 1, 2, 3)
    int *arrayA = malloc(3 * sizeof(int));
    // *arrayA = 1;
    // *(arrayA + 1) = 2;
    // *(arrayA + 2) = 3;
    arrayA[0] = 1;
    arrayA[1] = 2;
    arrayA[2] = 3;

    // 2. 배열 B: 길이가 4인 int형 배열을 생성할 메모리 공간 할당.
    int *arrayB = malloc(4 * sizeof(int));

    // 3. 배열 A의 값들을 배열 B에 복사.
    for (int i = 0; i < 3; i++)
    {
        arrayB[i] = arrayA[i];
    }
    // 4. 배열 B의 4번째 location에 value 4 insert.
    arrayB[3] = 4;

    arrayA = arrayB;

    for (int i = 0; i < 4; i++)
    {
         printf("배열 A의 %i번째 값: %i\n", i, *(arrayA + i));
    }
}