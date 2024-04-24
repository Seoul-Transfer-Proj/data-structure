#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   struct node *previous;
   int number;
   struct node *next;
}
node;

void createDoubleLinkedList(node **head, int number);
void printDoubleLinkedList(node *head);
node* createNode(int data);
void insertOfBeginning(node** head_ref, int data);
void insertOfEnd(node** head_ref, int data);
void insertMiddleOfDDL(node **head_ref, int data);

int main(void)
{
    node *head = NULL;
    createDoubleLinkedList(&head, 3);
    insertOfBeginning(&head, 6);
    insertOfEnd(&head, 19);
    insertMiddleOfDDL(&head, 15);
    printDoubleLinkedList(head);
}

void createDoubleLinkedList(node **head, int number)
{
    // number만큼의 Loop를 돈다.
    for (int i = 1; i <= number; i++)
    {
        // 새로운 node를 생성한다
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return;
        }
        n->number = i;

        if (*head == NULL)
        {
            n->previous = NULL;
            n->next = NULL;
            *head = n;
        } 
        else 
        {
            node *tmp = *head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = n;
            n->previous = tmp;
            n->next = NULL;
            if (tmp->next == NULL)
            {
                
            }
        }
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
    newNode->number = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
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

void insertOfEnd(node** head_ref, int data)
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