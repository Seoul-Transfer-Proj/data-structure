#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   struct node *previous;
   int number;
   struct node *next;
}
node;

void createDoubleLinkedList(node **head, node **tail, int number);
void printDoubleLinkedList(node *head);
node* createNode(int data);
void insertOfBeginning(node** head_ref, int data);
void insertOfEnd(node** head_ref, node** tail_ref, int data);
void insertMiddleOfDDL(node **head_ref, int data);
void reversePrintDDL(node *tail);
void searchNodeIndex(node **head, node **tail, int data);
void freeOfMemoryAlloc(node *head);

int main(void)
{
    node *head = NULL;
    node *tail = NULL;
    createDoubleLinkedList(&head, &tail, 3);
    printf("DDL 1st create 출력\n");
    printDoubleLinkedList(head);

    insertOfBeginning(&head, 6);
    printf("DDL 6이 삽입된 출력\n");
    printDoubleLinkedList(head);

    insertOfEnd(&head, &tail, 19);
    printf("DDL 19가 삽입된 출력\n");
    printDoubleLinkedList(head);

    insertMiddleOfDDL(&head, 15);
    printf("DDL 15가 삽입된 출력\n");
    printDoubleLinkedList(head);

    printf("DDL 역방향 출력\n");
    reversePrintDDL(tail);

    printf("찾는 노드의 index 출력\n");
    searchNodeIndex(&head, &tail, 3);

    freeOfMemoryAlloc(head);
}

void createDoubleLinkedList(node **head, node **tail, int number)
{
    // number만큼의 Loop를 돈다.
    for (int i = 1; i <= number; i++)
    {
        // 새로운 node를 생성한다
        node *new_node = createNode(i);

        if (*head == NULL)
        {
            new_node->previous = NULL;
            new_node->next = NULL;
            *head = new_node;
        } 
        else 
        {
            node *tmp = *head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new_node;
            new_node->previous = tmp;
            new_node->next = NULL;
            *tail = new_node;
        }
    }
}

void insertOfBeginning(node** head_ref, int data)
{
    node *new_node = createNode(data);
    new_node->next = (*head_ref);
    new_node->previous = NULL;

    if ((*head_ref) != NULL)
    {
        (*head_ref)->previous = new_node;
    } 

    (*head_ref) = new_node;
}

void insertOfEnd(node** head_ref, node** tail_ref, int data)
{
    node *new_node = createNode(data);

    node *tmp = (*head_ref);
    while(tmp->next != NULL)
    {
    // tmp->next가 NULL이 아닐 때
        tmp = tmp->next;
    }
    // tmp->next가 NULL일 때
    new_node->previous = tmp;
    tmp->next = new_node;
    (*tail_ref) = new_node;
}

// 숫자 정렬 기능이 있는 삽입 함수
void insertMiddleOfDDL(node **head_ref, int data)
{
    node *new_node = createNode(data);

    // loop를 돌면서 해당 객체가 가리키고 있는 노드의 숫자와 insert한 숫자와 비교
    for (node *tmp = (*head_ref); tmp != NULL; tmp = tmp->next )
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
            break;
        }
    }
}

void searchNodeIndex(node **head, node **tail, int data)
{
    int index = 0;
    printf("head Node 기준으로 찾으시겠습니까?(y/Y or n/N 입력 후 엔터): ");
    char answer;
    scanf("%c", &answer);

    if (answer == 'y' || answer == 'Y')
    {
        // Loop를 돌며 입력한 숫자를 가지고 있는 노드를 찾음.
        for (node *tmp = (*head); tmp != NULL; tmp = tmp->next)
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
        for (node *tmp = (*tail); tmp != NULL; tmp = tmp->previous)
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

void reversePrintDDL(node *tail)
{
    for (node *tmp = tail; tmp != NULL; tmp = tmp->previous)
    {
        printf("%i\n", tmp->number);
    }
}

void printDoubleLinkedList(node *head)
{
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
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