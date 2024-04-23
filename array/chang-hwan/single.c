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
void sort(node *head);


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
    printf("6가 삽입된 연결 리스트 출력\n");
    printLinkedList(head);

    sort(head);
    printf("6이 정렬된 연결 리스트 출력\n");
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

void sort(node *head)
{
    for (node *tmp = head; tmp->next != NULL; tmp = tmp->next)
    {
        for (node *tmp1 = head; tmp1->next != NULL; tmp1 = tmp1->next)
        {
            // 다음 노드의 숫자가 특정 노드의 숫자보다 작다면 
            if (tmp->next->number < tmp1->next->number)
            {
                // 1) 삽입할 노드를 임시 변수에 복사
                node *sorted = malloc(sizeof(node));
                if (sorted != NULL)
                {
                    sorted->number = tmp->next->number;
                // 2) 임시 노드를 next node(특정 노드의 숫자를 가진)에 연결
                    sorted->next = tmp1->next;
                }
                 // 3) 들어갈 자리 이전(특정 노드의 숫자를 가진 노드에 연결되어 있던)노드를 임시 노드에 연결
                tmp1->next = sorted;
                 // 4) 원래 노드의 이전 노드를 원래 노드의 다음 노드로 연결
                tmp->next = tmp->next->next;
                 // 5) 원래 노드를 free 해버림.
                free(tmp->next);
            }
        }
    }
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