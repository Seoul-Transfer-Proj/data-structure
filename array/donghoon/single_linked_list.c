#include <stdio.h>
#include <stdlib.h> // malloc과 free를 위해

// head 포인터부터 순차적으로 탐섹하는 single linked list
// 배엻과 다르게 중간에 데이터를 추가하거나 삭제하는 경우 뒤의 데이터들을 전부 움직이거나 주소가 달라지는 deepcopy를 할 필요가 없다,,

// strcuture 생성
typedef struct Node {
    int data;
    struct Node *next;
} node;

// 노드 삽입
void insert_n(node *head, const int index, const int data) {
    int n = index; // 어느 위치에서 삽입할지 정하기
    node *prenode = head; // 삽입할 노드 위치 전 노드 지정
    node *insert = (node *)malloc(sizeof(node)); // 추가할 노드 생성
    insert->data = data; // 화살표 연산자 : 포인터이름->멤버변수이름 = 값

    while (n-- && prenode != NULL) // prenode로 이동해서 
        prenode = prenode->next;
    if (prenode == NULL) {
        free(insert); // 메모리 누수 방지
        return;
    }
    insert->next = prenode->next; // 새로운 노드의 next는 prenode의 next로 바꿔주기
    prenode->next = insert; // 추가한 노드 전의 노드의 next는 추가한 노드의 주소로
}

// head부터 노드 탐색하면서 추가할 노드값이 해당 인덱스의 노드값보다 크면 넘어가고 작으면 앞에 추가하기 -> 정렬
void insert_n_order(node *head, const int data) {
    int i = 0;
    node *prenode = head;
    node *insert = (node *)malloc(sizeof(node));
    insert->data = data;

    while (prenode->next != NULL && prenode->next->data < data) {
        prenode = prenode->next;
    }
    insert->next = prenode->next;
    prenode->next = insert;
}

// 노드 삭제
void delete_n(node *head, const int index) {
    int n = index; // 어느 위치 삭제할건지
    node *prenode = head; // 삭제하고 싶은 노드 전 노드 저장
    node *del = NULL; // 삭제하고 싶은 노드 

    while (n-- && prenode != NULL)
        prenode = prenode->next;
    if (prenode == NULL || prenode->next == NULL) //
        return;
    del = prenode->next;
    prenode->next = del->next; // 삭제할 노드가 가리키는 주소를 전 노드가 가리키는 주소로 변경하기..
    free(del);// 삭제한 노드 비우기
}

// 노드 인덱스 뽑기
int get_n(node *head, const int n) {
    if (head->next == NULL)
        return -1;
    int index = 0;
    node *current = head->next;

    while (current->data != n) {
        ++index;
        current = current->next;
        if (current == NULL) 
            return -1;
    }
    return index;
}

// 원하는 인덱스의 노드값 찾기
int get_v(node *head, const int index) {
    if (head->next == NULL)
        return -1;
    int i = index;
    node *current = head->next;

    while(i--) current = current->next;
    return current->data;
}

// 리스트 순서대로 출력
void print_single(node *head) {
    if (head->next == NULL) return;

    node *temp = head->next;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    node *head = (node*)malloc(sizeof(node)); // heap 영역에 할당
    // head->data = 0; // 뭐가 들어가도 상관 없나..? head 노드는 데이터가 없는 노드인데
    head->next = NULL; // 아직 아무 노드도 들어가지 않았기 때문에 next값은 없다.
    print_single(head);

    // 노드 추가
    insert_n(head,0,5);
    insert_n(head,1,12);
    insert_n(head,2,78);
    insert_n(head,3,3);
    insert_n(head,1,26); // 리스트 중간에도 하나 넣어보기
    print_single(head);

    // 값에 따라 순차적으로 노드 추가
    insert_n_order(head, 49);
    print_single(head);

    // 노드 삭제
    delete_n(head,0);
    print_single(head);

    // 원하는 노드값의 인덱스 찾기
    printf("78의 인덱스 : %d\n", get_n(head, 78)); // 만약 원하는 노드 값이 같은게 두개라면...? -> 알아보기

    // 인덱스 값으로 해당 노드값 구하기
    printf("인덱스 2의 값 : %d\n", get_v(head, 2));

    printf("%p\n", head->next);
    printf("%d\n", head->data);

    // 메모리 누수 방지를 위한 head free..?? -> free 이후로는 주소들이 안찍힌다
    free(head);
    
    printf("%p\n", head->next);
    printf("%d\n", head->data);

    print_single(head);
}
