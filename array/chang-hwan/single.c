#include <stdio.h>
#include <stdlib.h>

//node 구조체 생성
  typedef struct node
  {
    int number;
    struct node *next;
  }
  node;

typedef struct 
{
    node *head;
    int size;
}
SingleLinkedList;

SingleLinkedList createSLL(void);
node* createNode(int number);
void createSingleLinkedList(SingleLinkedList *SLL, int k);
void insertNode(SingleLinkedList *list, int number);
void insertMiddleOfList(SingleLinkedList *list, int number);
void insertEndOfList(SingleLinkedList *list, int number);
void freeOfMemoryAlloc(SingleLinkedList *list);
void printLinkedList(SingleLinkedList *list);
void removeNodeUsingNumberOfNode(SingleLinkedList *list, int number);
void removeNodeUsingIndex(SingleLinkedList *list, int removedIndex);
void bubbleSort(SingleLinkedList *list);


int main(void) 
{
    SingleLinkedList list = createSLL();
    // createSingleLinkedList(&list, 7);
    // printf("생성된 연결 리스트 출력\n");
    // printLinkedList(&list);

    insertNode(&list, 9);
    insertEndOfList(&list, 70);

    printf("9, 70이 삽입된 생성된 연결 리스트 출력\n");
    printLinkedList(&list);

    insertMiddleOfList(&list, 15);
    printf("15가 삽입된 생성된 연결 리스트 출력\n");
    printLinkedList(&list);

    removeNodeUsingNumberOfNode(&list, 9);
    printf("head가 삭제된 연결 리스트 출력\n");
    printLinkedList(&list);

    removeNodeUsingNumberOfNode(&list, 70);
    printf("리스트의 마지막이 삭제된 연결 리스트 출력\n");
    printLinkedList(&list);

    removeNodeUsingNumberOfNode(&list, 15);
    printf("15가 삭제된 연결 리스트 출력\n");
    printLinkedList(&list);

    insertNode(&list, 19);
    insertNode(&list, 34);
    printf("19, 34가 삽입된 연결 리스트 출력\n");
    printLinkedList(&list);

    removeNodeUsingIndex(&list, 1);
    printf("head가 삭제된 연결 리스트 출력\n");
    printLinkedList(&list);

    removeNodeUsingIndex(&list, list.size);
    printf("list의 마지막 노드가 삭제된 연결 리스트 출력\n");
    printLinkedList(&list);

    insertNode(&list, 45);
    insertNode(&list, 80);
    insertNode(&list, 76);
    insertNode(&list, 90);
    insertNode(&list, 14);
    insertNode(&list, 32);
    insertEndOfList(&list, 56);

    bubbleSort(&list);
    printf("정렬된 연결 리스트 출력\n");
    printLinkedList(&list);
   
    freeOfMemoryAlloc(&list);
    printf("메모리 해제한 연결 리스트 출력\n");
    printLinkedList(&list);
}

SingleLinkedList createSLL(void)
{
    SingleLinkedList list;
    list.head = NULL;
    list.size = 0;
    return list;
}

node* createNode(int number)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->number = number;
    new_node->next = NULL;
    return new_node;
}

void createSingleLinkedList(SingleLinkedList *list, int number)
{  
    for (int i= 1; i <= number; i++)
    {
        node *new_node = createNode(i);

        if(list->head == NULL) {
            list->head = new_node;
            list->size++;
        } else {
            node *tmp = list->head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new_node;
            list->size++;
        }
    }
}

void insertNode(SingleLinkedList *list, int number)
{
    node *new_node = createNode(number);
    if (list->head == NULL)
    {
        list->head = new_node;
        list->size++;
    }
    else
    {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
}

void insertMiddleOfList(SingleLinkedList *list, int number) 
{
    node *new_node = createNode(number);
    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
        if (number < tmp->next->number)
        {
            new_node->next = tmp->next;
            tmp->next = new_node;
            list->size++;
            break;
        }
    }
}

void insertEndOfList(SingleLinkedList *list, int number)
{
    node * new_node = createNode(number);
    
    for (node *tmp =list->head; tmp != NULL; tmp = tmp->next)
    {
        if (list->head == NULL)
        {
        list->head = new_node;
        list->size++;
        break;
        }
        if (tmp->next == NULL) 
        {
            tmp->next = new_node;
            list->size++;
            break;
        }
    }
}

void removeNodeUsingNumberOfNode(SingleLinkedList *list, int number)
{
    // 삭제하려는 노드가 가진 숫자가 list에 있는지 확인
    int found = 0;

    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
    // 현재 노드의 next에 할당된 주소에 접근해 삭제하려는 숫자(number)와 next.number가 같은지 확인.
        // head가 가리키는 노드를 삭제하려는 경우
        if (tmp->number == number)
        {
            node *toDelete = tmp;
            list->head = list->head->next;
            free(toDelete);
            list->size--;
            found = 1;
            break;
        }
        if (tmp->next != NULL)
        {
            if(tmp->next->number == number)
            {
                node *toDelete = tmp->next;
                // 리스트의 마지막 node를 삭제해야 하는 경우
                if (tmp->next->next == NULL)
                {
                    tmp->next = NULL;
                    free(toDelete);
                    list->size--;
                    found = 1;
                    break;
                }
                tmp->next = tmp->next->next;
                free(toDelete);
                found = 1;
                list->size--;
                break;
            }
        }
    }

    // 삭제하려는 숫자가 없을 경우
    if (!found)
    {
        printf("삭제하려는 숫자를 가진 노드가 없어요");
    }
}

void removeNodeUsingIndex(SingleLinkedList *list, int removedIndex)
{
    // 삭제할 노드의 index가 0보다 작거나 list의 길이보다 클 경우
    if(removedIndex < 0 || removedIndex > list->size)
    {
        printf("삭제하려는 노드의 index를 다시 입력해주세요!\n");
        return;
    }

    int index = 1;
    for (node * tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
        int next_node_index = index + 1;

        // 삭제할 index가 1인 경우
        if (removedIndex == 1 || list->size == 1)
        {
            if (tmp->next == NULL)
            {
                list->head = NULL;
                free(tmp);
                list->size = 0;
                break;
            }
            else
            {
                list->head = list->head->next;
                free(tmp);
                list->size--;
                break;
            }
        }
        // 현재 노드의 다음 노드가 삭제할 index와 같다면
        if (next_node_index == removedIndex)
        {
            // 삭제할 index가 list의 size와 같은 경우(끝 인덱스)
            if (removedIndex == list->size)
            {
                tmp->next = NULL;
                free(tmp->next);
                list->size--;
                break;
            }
            else
            {
                tmp->next = tmp->next->next;
                free(tmp->next);
                list->size--;
                break;
            }
        }
        index++;
    }
}

void bubbleSort(SingleLinkedList *list)
{
    // List를 순회하며 교환이 됐는지 추적
    int swapped;
    // 현재 노드를 가리키는 pointer
    node *ptr1;
    // 정렬 과정에서 이미 정렬된 리스트의 끝을 가리키는 포인터. 교환이 없으면 정렬이 된 것으로 간주.
    node *lptr = NULL;

    //리스트가 비어있으면 반환 
    if (list->head == NULL)
        return;
    
    // 교환이 발생(swapped = 1)할 때까지 반복.
    do
    {
        swapped = 0;
        ptr1 = list->head;

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

void freeOfMemoryAlloc(SingleLinkedList *list)
{
    node *ptr = list->head;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    list->head = NULL;
    list->size = 0;
}

void printLinkedList (SingleLinkedList *list)
{
    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }  
}