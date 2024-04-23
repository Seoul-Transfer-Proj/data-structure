#include <stdio.h>
#include <stdlib.h>

// 1. node 구조체 생성
  typedef struct  node
  {
    int number;
    struct node *next;
  }
  node;

int main(void) 
{
    // 2. head node 생성
    node *head = NULL;

    // 3. Node 크기 만큼의 메모리 덩어리를 할당하고 해당 주소를 가지는 포인터 n 생성.
    node *n = malloc(sizeof(node));

    // 4. 메모리를 할당 받았는지 확인 후 숫자 1과 다음을 가리키는 포인터는 없으므로 NULL 할당.
    if (n == NULL)
    {
        return 1;
    }
    (*n).number = 1;
    (*n).next = NULL;

    // 5. head node가 숫자 1을 가진 node를 가리키도록 함.
    head = n;

    // head는 1을 가진 node에 연결되어 있으므로 node1은 유실되지 않으므로 n에 새로운 node만큼의 메모리 덩어리를 할당하고 해당 주소를 반환.
    // 2를 가질 node 생성
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->next = NULL;

    // node1과 node2 연결
    head->next = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 3;
    n->next = NULL;

    //node2와 node3연결
    head->next->next = n;


    for (node *tmp = head; tmp != NULL; tmp = (*tmp).next)
    {
        printf("%i\n", (*tmp).number);
    }  
}