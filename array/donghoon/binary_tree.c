#include <stdio.h>
#include <stdlib.h>

// treenode 구조체
typedef struct Treenode
{
    int data;
    struct Treenode *left;
    struct Treenode *right; 
} tree;
tree *root;

// 트리노드 삽입
//1. 삽입할 값을 루트 노드와 비교해 같다면 오류( 중복 값 허용 X )
//2. 삽입할 값이 루트 노드의 키보다 작다면 왼쪽 서브 트리를 탐색해서 비어있다면 추가하고,
//    비어있지 않다면 다시 값을 비교.
//3. 삽입할 값이 루트노드의 키보다 크다면 오른쪽 서브트리를 탐색해서 비어있다면 추가하고, 
//    비어있지 않다면 다시 값을 비교.

// void insert_t(tree *root, const int data) {
//     tree *insert = (tree*)malloc(sizeof(tree)); // 새로운 노드 생성
//     insert->data = data;
//     insert->left = NULL;
//     insert->right = NULL;
//     if (root->data > insert->data) { // 만약 루트의 노드값이 새 노드값보다 크면
//         if (root->left != NULL) // 왼쪽으로 가는데 왼쪽이 이미 존재한다면
//             insert_t(root->left, data); // 해당 왼쪽값을 다시 새 노드와 비교 -> 재귀적으로
//         else    
//             root->left = insert; // 왼쪽이 비어있다면 해당 노드에 새노드 추가
//     }
//     else if (root->data < insert->data) { // 루트의 노드값이 새 노드값보다 작을때는 오른쪽으로
//         if (root->right != NULL)
//             insert_t(root->right, data);
//         else    
//             root->right = insert;
//     }
//     // 메모리 누수가 대체 어디서 발생하는거야
//     // free(insert);
// }

// -> 위에처럼 하면 재귀가 돌때마다 계속 새로운 insert를 할당해서 메모리 누수가 발생해서 고쳐주기
void insert_t(tree *root, const int data) {
    if (root->data > data) {
        if (root->left != NULL)
            insert_t(root->left, data);
        else {
            tree *insert = (tree*)malloc(sizeof(tree)); // 새로운 노드 생성
            insert->data = data;
            insert->left = NULL;
            insert->right = NULL;
            root->left = insert; // 부모 노드의 왼쪽에 새 노드를 연결
        }
    } else if (root->data < data) {
        if (root->right != NULL)
            insert_t(root->right, data);
         else {
            tree *insert = (tree*)malloc(sizeof(tree)); // 새로운 노드 생성
            insert->data = data;
            insert->left = NULL;
            insert->right = NULL;
            root->right = insert; // 부모 노드의 오른쪽에 새 노드를 연결
        }
    } else {
        printf("%d 와 중복된 값이 존재합니다.\n", data);
    }
}

// 오른쪽 서브트리의 가장 왼쪽노드를 찾기    만약 15를 삭제하고 싶다면?
tree *find_r_l(tree *parent, tree *node) { // 여기서 node는 삭제하려는 오른쪽 서브트리의 시작 노드를 받는다 (15,18)
    tree *temp = node; //(18)
    while (temp->left) { // 왼쪽 노드가 있는 경우 
        parent = temp; 
        temp = temp->left; 
    } // (parent: 18, temp: 17)
    if (temp == node) { // 찾고자 하는 노드(오른쪽 서브트리에서 가장 왼쪽 노드)가 입력한 노드(오른쪽 서브트리의 시작 노드)인 경우 
        parent->right = NULL; // 삭제하려는 노드의 부모와 오르쪽으로 연결되어있으니 그걸 끊어주기
    } else {
        parent->left = NULL; // 찾고자하는 노드가 입력한 노드의 왼쪽에 존재하면 parent는 temp이므로 왼쪽 연결 끊어주기 (18-17 끊어주기)
    }
    return temp;
}

// 트리 노드 삭제 - 탐섹 후 삭제하고 싶은 노드의 자식들은 어떻게 삭제할 것인가..? 노드들의 왼,오 포인트를 다시 NULL로..?
// 1. 삭제할 노드의 자식이 없는 경우
//   -> 해당 노드만 삭제
// 2. 삭제할 노드의 자식이 하나 있는 경우
//   -> 해당 노드 삭제 후 자식 반환
// 3. 삭제할 노드의 자식이 둘인 경우
//   -> ???
void delete_t(tree *node, tree *parent, const int data) {
    // 해당 데이터의 노드를 찾아 떠나기
    if (node->data > data) {
        if(node->left) 
            delete_t(node->left, node, data);
    }
    else if (node->data < data) {
        if (node->right)
            delete_t(node->right, node, data);
    }
    // 삭제할 노드를 찾으면
    else {
        // 1. 삭제할 노드에게 자식이 없는 경우
        if (node->left == NULL && node->right == NULL) {
            if (parent->left == node) { // 삭제할 노드가 부모의 왼쪽 자식이라면 
                parent->left = NULL;
            } else { // 오른쪽 자식이라면
                parent->right = NULL; 
            }
            free(node);
        }
        // 2. 삭제할 노드에게 자식이 하나 존재할 경우
        else if (node->left == NULL || node->right == NULL) {
            tree *nullnode = NULL; // 자식과 연결된 포인터로 바꿔주기
            if (node->left) { // 자식이 왼쪽이면
                nullnode = node->left;
            } else { // 오른쪽이면
                nullnode = node->right;
            }
            // 자식을 가리키는 포인터를 지정해 줬으면
            if (root == node) {
                root = nullnode;
            } else {
                if (parent->left == node) { // 삭제할 노드가 부모의 왼쪽 자식이면
                    parent->left = nullnode; // 삭제할 노드의 자식을 할아버지의 왼쪽에 연결
                } else {
                    parent->right = nullnode;
                }
            }
            free(node);
        }
        // 3. 삭제할 노드에게 두개의 자식이 다 있는 경우..
        // 삭제하려는 노드의 오른쪽 서브트리의 가장 왼쪽 노드와의 포인터를 끊고 (NULL)로 만등고
        // 삭제하려는 노드의 양쪽 자식들을 삭제하려는 노드의 오른쪽 서브트리의 가장 왼쪽노드에 연결시킨다
        // 그러기위해서는 오른쪽 서브트리의 가장 왼쪽노드 or 왼쪽 서브트리의 가장 오른쪽 노드를 찾는 함수가 필요! -> 삭제된 노드의 오른쪽 서브트리에 속한  모든 노드가 새롭게 대체될 노드보다 큰 값임을 보장하기 위해
        else if (node->left && node->right) {
            // 오른쪽 서브트리의 가장 왼쪽노드 찾기
            tree *rminnode = find_r_l(node, node->right); //17
            // 삭제하려는 노드가 부모의 왼쪽에 존재하면
            if (parent->left == node) {
                parent->left = rminnode; // 삭제하려는 노드 대신 위에서 찾은 min노드를 붙인다.
            } else {
                parent->right = rminnode;
            }
            // 새롭게 붙인 노드에 기존 삭제한 노드의 자식들 붙여주기
            rminnode->left = node->left;
            rminnode->right = node->right;
            free(node); // 노드 삭제
            // 3번에서 메모리 누수가 발생한다 왜지
        }        
    }
}

// 출력하기 (전위순회) : 현재노드 -> 왼쪽노드 -> 오른쪽노드 순으로 탐색
void DLR(tree *root) {
    tree *temp = root;
    printf("%d ", temp->data);
    if (temp->left != NULL)
        DLR(temp->left);
    if (temp->right != NULL)
        DLR(temp->right);
}

// 출력하기 (중위순회) : 왼쪽노드 -> 현재노드 -> 오른쪽노드 순으로 탐색
void LDR(tree *root) {
    tree *temp = root;
    if (temp->left != NULL)
        LDR(temp->left);
    printf("%d ", temp->data);
    if (temp->right != NULL)
        LDR(temp->right);
}

// 출력하기 (후위순회) : 왼쪽노드 -> 오른쪽노드 -> 현재노드 순으로 탐색
void LRD(tree *root) {
    tree *temp = root;
    if (temp->left != NULL)
        LRD(temp->left);
    if (temp->right != NULL)
        LRD(temp->right);
    printf("%d ", temp->data);
}

// 원하는 값을 가지고 있는 노드의 자식 출력하기 (전위순회 방식으로)
void search(tree *root, tree *parent, const int data) {
    tree *temp = root;
    // parent = temp;
    if (temp->data == data) {
        if (temp->left == NULL && temp->right == NULL) {
            printf("\n%d에게는 자식 노드가 없습니다 , 부모는 %d 입니다", data, parent->data);
        } 
        else if (temp->left == NULL || temp->right == NULL) {
            if (temp->left) {
                printf("\n %d에게는 하나의 자식노드 존재 : %d 부모는 %d 입니다", data, temp->left->data, parent->data);
            } else {
                printf("\n %d에게는 하나의 자식노드 존재 : %d 부모는 %d 입니다", data, temp->right->data, parent->data);
            }
            
        } else {
            printf("\n %d의 부모는 %d이고 \n 완쪽 자식은 : %d ", data, parent->data, temp->left->data);
            printf("\n 오른쪽 자식은 : %d ", temp->right->data);
        }
    } else {
    if (temp->left != NULL)
        search(temp->left, temp, data);
    if (temp->right != NULL)
        search(temp->right, temp, data);
    }
}

// 노드 전체 해제
void free_tree(tree *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    tree *root = (tree*)malloc(sizeof(tree)); // root생성
    root->data = 20;
    root->left = NULL;
    root->right = NULL;

    insert_t(root, 15);
    insert_t(root, 6);
    insert_t(root, 1);
    insert_t(root, 11);
    insert_t(root, 47);
    insert_t(root, 25);
    insert_t(root, 76);
    insert_t(root, 18);
    insert_t(root, 17);
    insert_t(root, 19);

    printf("전위순회 : ");
    DLR(root);
    printf("\n중위순회 : ");
    LDR(root);
    printf("\n후위순회 : ");
    LRD(root);

    delete_t(root, root, 15);
    printf("\n삭제 후 전위순회 : ");
    DLR(root);

    search(root, root, 1);

    // free(root);
    free_tree(root);
    return 0;
}
// 14ce055e0
// 1592040e0
// 159204200