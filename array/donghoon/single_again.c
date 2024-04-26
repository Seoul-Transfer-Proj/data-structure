#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 리스트 구조체 
typedef struct List {
    Node *head;
    int size;
} List;

// 리스트 초기화 
void init_list(List *list) {
    list->head = NULL;
    list->size = 0;
}

// 노드 추가 
void insert_node(List *list, int index, int data) {
    // 새로운 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // 리스트가 비어있다면?
    if (list->head == NULL) {
        list->head = new_node;
    }
    else {
        // 삽입할 위치를 찾아주기
        Node *temp = list->head;
        int i = 0;
        while (temp->next != NULL && i < index-1) {
            temp = temp->next;
            i++;
        }
        // 노드 삽입
        printf("%d\n", i);
        new_node->next = temp->next;
        temp->next = new_node;
    }
    list->size++;
}

// 리스트 출력 
void print_list(List *list) {
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 메모리 해제 
void free_list(List *list) {
    Node *temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

int main() {
    List list, size;
    init_list(&list);

    // 노드 추가
    insert_node(&list, 0, 5);
    insert_node(&list, 1, 12);
    insert_node(&list, 2, 78);
    insert_node(&list, 3, 3);
    print_list(&list);
    printf("리스트 사이즈: %d\n", list.size);
    insert_node(&list, 2, 26);

    // 리스트 출력
    print_list(&list);

    //메모리 해제
    free_list(&list);
    printf("리스트 사이즈: %d\n", list.size);
    return 0;
}
