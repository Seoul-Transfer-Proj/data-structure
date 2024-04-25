#include <stdio.h>
#include <stdlib.h>

// 이중연결리스트의 구조체는 단일과 다르게 좌우(앞뒤)에 연결 필드를 가진다 -> 역방향 순회가 가능해짐

// 구조체 생성
// head와 tail을 전역변수로 설정 해주는 것이 편한가..?
typedef struct Node {
    int data;
    struct Node *left; // 역방향
    struct Node *right; // 정방향
} node;
node *head, *tail;

// 노드 삽입 (haed에서 순차적으로밖에 삽입 못하나?)
void insert_n(node *prenode, const int data) {
    node *insert = (node*)malloc(sizeof(node));
    insert->data = data;
    insert->right = prenode->right; // 삽입 노드의 오른쪽에는 전 노드의 오른next값
    insert->left = prenode; // 삽입 노드의 왼쪽에는 전노드 값

    if (prenode->right != tail) {
        prenode->right->left = insert;
    }
    prenode->right = insert;
}

// 원하는 인덱스에 넣고싶다면
// 헤드 노드부터 시작하여 원하는 위치까지 반복문을 통해 이동한 후에 삽입
void put_n(node *head, int position, const int data) {
    // 새로운 노드 생성
    node *insert = (node*)malloc(sizeof(node));
    insert->data = data;

    // 원하는 인덱스까지 이동
    node *current = head;
    int cnt = 0;
    while (current->right != tail && cnt < position) {
        current = current->right;
        cnt++;
    }
    // 새로운 노드
    insert->right = current->right; //새로운 노드의 오른쪽은 전 노드의 오른쪽 주소로
    insert->left = current; //새로운 노드의 왼쪽은 전 노드를
    // printf("1.이전 %p\n", current->right);
    // printf("1.다음 %p\n", insert->left);
    current->right->left = insert; // 전 노드의 오른쪽 포인트의 왼쪽을 새로운 노드로 : tail부터 역순 조회를 위해?
    current->right = insert; //전노드의 오른쪽을 새로운 노드로
    // printf("2.이전 %p\n", current->right);
    // printf("2.이전 %p\n", current->right->left);
    // printf("2.다음 %p\n", insert->left);
    // printf("\n");
}

// 원하는 값이 들어있는 노드 삭제
void delete_v(node *head, const int value) {
    int v = value;
    node *prenode = head;

    while(prenode->right != tail) {
        prenode = prenode->right;
        if(prenode->data == v) { // 지우고싶은 값이 prenode에 있으면
            prenode->right->left = prenode->left; // 삭제할 노드의 다음의 왼쪽 포인트를 삭제할 노드의 왼쪽 포인트로 변경
            prenode->left->right = prenode->right; // 삭제할 노드의 다음의 오른쪽 포인트를 삭제할 노드의 오른쪽 포인트로 변경
            free(prenode);
            return;
        }
    }
}

// 순서대로 조회하기
void print_double(node *head) {
    if (head->right == NULL) return;

    node *temp = head->right; //head의 오른쪽 부터
    while (temp->right != tail)
    {
        printf("%d ", temp->data);
        temp = temp->right;
    }
    printf("\n");
}

// 역순으로 조회하기
void print_rev(node *tail) {
    if (tail == NULL) return;

    node *temp = tail->left; // tail의 왼쪽부터
    while (temp->left != head)
    {
        printf("%d ", temp->data);
        temp = temp->left;
    }
    printf("\n");
}

// 노드 전부 해제 
void free_n(node *head) {
    node *temp;
    while (head->right != tail) {
        temp = head->right;
        head->right = temp->right;
        free(temp);
    }
    free(head);
    free(tail);
}

int main() {
    node *head = (node*)malloc(sizeof(node));
    node *tail = (node*)malloc(sizeof(node));

    head->left = NULL;
    head->right = tail;
    tail->left = head;
    tail->right = NULL;
    printf("%p\n", head);
    printf("%p\n", tail);

    // insert_n(head, 1);
    // insert_n(head, 8);
    // insert_n(head, 35);
    // insert_n(head->right, 100); // 두번째에 삽입

    put_n(head, 0, 1);
    put_n(head, 1, 8);
    put_n(head, 2, 35);
    put_n(head, 1, 50); // 원하는 인덱스에 삽입

    print_double(head); // 순차적으로 조회 
    print_rev(tail); // 역순으로 조회

    delete_v(head, 8);
    print_double(head);
    // 리스트에 왜 head 데이터인 0값이 같이 출력되는걸까...-> 출력 함수에서 temo != tail이 아닌 temp->right != tail로 해주어야해

    // printf("%d\n", head->data);
    // printf("%d\n", head->right->data);
    // printf("%d\n", tail->data);
    // printf("%d\n", tail->left->data);
    
    // printf("%p\n", head->right);
    // printf("%p\n", head->right);
    free_n(head);
    // free(head);
    // free(tail);

}