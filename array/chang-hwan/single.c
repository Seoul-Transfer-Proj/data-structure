#include <stdio.h>
#include <stdlib.h>

//node 구조체 생성
  typedef struct node
  {
    int number;
    struct node *next;
  }
  node;

void createSingleLinkedList(node **head, int i);
void insertAtBeginningOfList(node **head, node *insertNode);
void insertMiddleOfList(node *head, node *insertNode);
void insertEndOfList(node *head, node *insertNode);
void freeOfMemoryAlloc(node *head);
void printLinkedList (node *head);
void removeNode(node *head, int number);
void bubbleSort(node *head);


int main(void) 
{
    node *head = NULL;
    createSingleLinkedList(&head, 7);
    printf("생성된 연결 리스트 출력\n");
    printLinkedList(head);
    node *n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->number = 10;
        n->next = NULL;
    }
    insertEndOfList(head, n);
    printf("10이 삽입된 생성된 연결 리스트 출력\n");
    printLinkedList(head);
    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->number = 9;
        n->next = NULL;
    }
    insertMiddleOfList(head, n);
    printf("9가 삽입된 생성된 연결 리스트 출력\n");
    printLinkedList(head);

    removeNode(head, 6);
    printf("6이 삭제된 연결 리스트 출력\n");
    printLinkedList(head);

    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->number = 6;
        n->next = NULL;
    }
    insertAtBeginningOfList(&head, n);

    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->number = 4;
        n->next = NULL;
    }
    insertAtBeginningOfList(&head, n);
    printf("6, 4가 삽입된 연결 리스트 출력\n");
    printLinkedList(head);

    bubbleSort(head);
    printf("정렬된 연결 리스트 출력\n");
    printLinkedList(head);
   
    freeOfMemoryAlloc(head);
}

void createSingleLinkedList(node **head, int k)
{  
    for (int i= 1; i <= k; i++)
    {
        node *n = malloc(sizeof(node));
        if (n != NULL)
        {
            n->number = i;
            n->next = NULL;
        }

        if(*head == NULL) {
            *head = n;
        } else {
            node *tmp = *head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = n;
        }
    }
}

void insertAtBeginningOfList(node **head, node *insertNode){
    if (*head == NULL) 
    {
        *head = insertNode;
    }
    else
    {
        insertNode->next = *head;
        *head = insertNode;
    }
}

void insertMiddleOfList(node *head, node *insertNode) 
{
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if (insertNode->number < tmp->next->number)
        {
            insertNode->next = tmp->next;
            tmp->next = insertNode;
            break;
        }
    }
}

void insertEndOfList(node *head, node *insertNode)
{
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if ((*tmp).next == NULL) 
        {
            (*tmp).next = insertNode;
            break;
        }
    }
}

void removeNode(node *head, int number)
{
    for (node *tmp = head; tmp != NULL; tmp = (*tmp).next )
    {
         // 현재 노드의 next에 할당된 주소에 접근해 삭제하려는 숫자(number)와 next.number가 같은지 확인.
        if(tmp->next->number == number)
        {
            node* toDelete = tmp->next;
            (*tmp).next = tmp->next->next;
            free(toDelete);
            break;
        }
    }
}

void bubbleSort(node *head)
{
    // List를 순회하며 교환이 됐는지 추적
    int swapped;
    // 현재 노드를 가리키는 pointer
    node *ptr1;
    // 정렬 과정에서 이미 정렬된 리스트의 끝을 가리키는 포인터. 교환이 없으면 정렬이 된 것으로 간주.
    node *lptr = NULL;

    //리스트가 비어있으면 반환 
    if (head == NULL)
        return;
    
    // 교환이 발생(swapped = 1)할 때까지 반복.
    do
    {
        swapped = 0;
        ptr1 = head;

    // ptr1의 다음 노드가 lptr(이미 정렬된 리스트의 끝)와 같지 않을 때까지 반복.
        while (ptr1->next != lptr)
        {
    // ptr1의 다음 노드의 숫자가 ptr1의 숫자보다 작다면
            if (ptr1->next->number < ptr1->number)
            {
                // 값 교환
                int temp = ptr1->number;
                ptr1->number = ptr1->next->number;
                ptr1->next->number = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } 
    while 
    (swapped);
}

void freeOfMemoryAlloc(node *head)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

void printLinkedList (node *head)
{
    for (node *tmp = head; tmp != NULL; tmp = (*tmp).next)
    {
        printf("%i\n", (*tmp).number);
    }  
}