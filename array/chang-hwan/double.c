#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   struct node *previous;
   int number;
   struct node *next;
}
node;

typedef struct
{ 
    node *head;
    node *tail;
    int size;
}
LinkedList;

LinkedList createLinkedList();
void createDoubleLinkedList(LinkedList *list, int number);
void printDoubleLinkedList(LinkedList *list);
node* createNode(int data);
void insertNode(LinkedList *list, int number);
void insertOfEnd(LinkedList *list, int number);
void insertMiddleOfDDL(LinkedList *list, int data);
void reversePrintDDL(LinkedList *list);
void searchNodeIndex(LinkedList *list, int data);
void removeNode(LinkedList *list);
void freeOfMemoryAlloc(LinkedList *list);

int main(void)
{
    LinkedList list = createLinkedList();

    createDoubleLinkedList(&list, 3);
    printf("DDL 1st create 출력\n");
    printDoubleLinkedList(&list);

    insertNode(&list, 6);
    insertNode(&list, 119);
    printf("DDL 6이 삽입된 출력\n");
    printDoubleLinkedList(&list);

    insertOfEnd(&list, 19);
    printf("DDL 19가 삽입된 출력\n");
    printDoubleLinkedList(&list);

    insertMiddleOfDDL(&list, 15);
    printf("DDL 15가 삽입된 출력\n");
    printDoubleLinkedList(&list);

    printf("DDL 역방향 출력\n");
    reversePrintDDL(&list);

    printf("찾는 노드의 index 출력\n");
    searchNodeIndex(&list, 3);

    printf("index로 삭제한 DDL 출력\n");
    removeNode(&list);
    printDoubleLinkedList(&list);

    //사용한 메모리 해제
    freeOfMemoryAlloc(&list);
    printDoubleLinkedList(&list);
}

LinkedList createLinkedList(){
    LinkedList list;
    list.head = NULL;
    list.size = 0;

    return list;
}

void createDoubleLinkedList(LinkedList *list, int number)
{
    // number만큼의 Loop를 돈다.
    for (int i = 1; i <= number; i++)
    {
        // 새로운 node를 생성한다
        node *new_node = createNode(i);

        if (list->head == NULL)
        {
            list->head = new_node;
            list->tail = new_node;
            list->size++;
        }
        else
        {
            node *tmp = list->head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new_node;
            tmp->next->previous = tmp;
            list->tail = tmp->next;
            list->size++;
        }
    }
}

void insertNode(LinkedList *list, int number)
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
        list->head->previous  = new_node;
        list->head = new_node;
        list->size++;
    }
}

void insertOfEnd(LinkedList *list, int number)
{
    node *new_node = createNode(number);

    if (list->head == NULL)
    {
        list->head = new_node;
    }

    node *tmp = list->head;
    while(tmp->next != NULL)
    {
    // tmp->next가 NULL이 아닐 때
        tmp = tmp->next;
    }
    // tmp->next가 NULL일 때
    new_node->previous = tmp;
    tmp->next = new_node;
    list->tail = new_node;
    list->size++;
}

// 숫자 정렬 기능이 있는 삽입 함수
void insertMiddleOfDDL(LinkedList *list, int data)
{
    node *new_node = createNode(data);

    // loop를 돌면서 해당 객체가 가리키고 있는 노드의 숫자와 insert한 숫자와 비교
    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next )
    {
        // insert한 숫자가 작으면
        if (new_node->number < tmp->next->number)
        {
        // new_node의 prev를 tmp를 가리키고
            new_node->previous = tmp;
        // new_node의 next를 tmp->next를 가리킨다. 
            new_node->next = tmp->next;
        // tmp->next->prev는 new_node를 가리킨다.
            tmp->next->previous = new_node;
        // tmp는->next 는 new_node를 가리킨다. 
            tmp->next = new_node;

            list->size++;
            break;
        }
    }
}

void searchNodeIndex(LinkedList *list, int data)
{
    int index = 0;
    printf("찾는 노드의 index는 %i\n", data);
    printf("head Node 기준으로 찾으시겠습니까?(y/Y or n/N 입력 후 엔터): ");
    char answer;
    scanf("%c", &answer);

    if (answer == 'y' || answer == 'Y')
    {
        // Loop를 돌며 입력한 숫자를 가지고 있는 노드를 찾음.
        for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
        {
            index ++;
            if (tmp->number == data)
            {
                printf("찾으시는 %i를 가진 노드는 head 기준 %i번째 노드입니다.\n", data, index);
                break;
            }
        }
    }
    else
    {
        for (node *tmp = list->tail; tmp != NULL; tmp = tmp->previous)
        {
            index ++;
            if (tmp->number == data)
            {
                printf("찾으시는 %i를 가진 노드는 tail 기준 %i번째 노드입니다.\n", data, index);
                break;
            }
        }
    }
}

void removeNode(LinkedList *list)
{
    int removedIndex= 7;
    // printf("몇번째 node를 삭제하시겠습니까?: ");
    // scanf("%d", &removedIndex);
    
    if (removedIndex < 1 || removedIndex > list->size )
    {
        printf("현재 List길이보다 더 긴 값을 입력했어요.\n현재 List의 길이: %i\n", list->size);
        printf("다시 삭제할 노드의 index를 입력해주세요: ");
        scanf("%i", &removedIndex);
    }
    
    int listIndex = 1;

    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
        if (listIndex == removedIndex)
        {
            if (listIndex != list->size)
            {
                tmp->previous->next = tmp->next;
                tmp->next->previous = tmp->previous;
                free(tmp);
                list->size--;
                break;
            }
            else
            {
                list->tail = tmp->previous;
                tmp->previous->next = NULL;
                free(tmp);
                list->size--;
                break;
            }
        }
        else
        {
            listIndex++;
        }
    }
}

void reversePrintDDL(LinkedList *list)
{
    for (node *tmp = list->tail; tmp != NULL; tmp = tmp->previous)
    {
        printf("%i\n", tmp->number);
    }
     printf("현재 list의 길이는: %i\n", list->size);
}

void printDoubleLinkedList(LinkedList *list)
{
    for (node *tmp = list->head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    printf("현재 list의 길이는: %i\n", list->size);
}

node* createNode(int data)
{
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode != NULL)
    {
        newNode->number = data;
        newNode->previous = NULL;
        newNode->next = NULL;
        return newNode;
    }
    else 
    {
        return newNode;
    }
}

void freeOfMemoryAlloc(LinkedList *list)
{
    node *current = list->tail;
    while (current != NULL)
    {
        node *temp = current;
        current = current->previous;
        free(temp);
    }
}