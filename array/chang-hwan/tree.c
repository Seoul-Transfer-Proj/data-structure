#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
}
node;

node* createNewNode(int data);
void insertNode(node **root, int data);
void printBinaryTree(node *root, int level);
void searchNode(node **root, int number);
void inOrder(node *root);
node* deleteNode(node *root, int number);
void print_tree(node *root);
void free_tree(node *root);

int main(void)
{
    node *root = NULL;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 20);
    insertNode(&root, 40);
    insertNode(&root, 70);
    insertNode(&root, 60);
    insertNode(&root, 80);

    printf("원래 Binary Search Tree: ");
    inOrder(root);
    print_tree(root);
    
    searchNode(&root, 20);
    searchNode(&root, 15);
  
    printf("\n\nDelete a Leaf Node: 20\n");
    root = deleteNode(root, 20);
    printf("Modified BST tree after deleting Leaf Node:\n");
    inOrder(root);

    printf("\n\nDelete Node with single child: 70\n");
    root = deleteNode(root, 70);
    printf("Modified BST tree after deleting single child Node:\n");
    inOrder(root);

    printf("\n\nDelete Node with both child: 50\n");
    root = deleteNode(root, 50);
    printf("Modified BST tree after deleting both child Node:\n");
    inOrder(root);

    free_tree(root);

    return 0;
}

void insertNode(node **root, int data)
{
    node *new_node = createNewNode(data);
    if ((*root) == NULL)
    {
        (*root) = new_node;
    }
    else
    {
        node *tmp = (*root);
        while (tmp != NULL)
        {
            if (new_node->data < tmp->data) 
            {
                if (tmp->left == NULL)
                {
                    tmp->left = new_node;
                    break;
                } else 
                {
                    tmp= tmp->left;
                }
            } 
            // new node의 숫자가 tmp의 숫자보다 크다면
            else if (new_node->data > tmp->data)
            {
                if (tmp->right == NULL)
                {
                    tmp->right = new_node;
                    break;
                }
                else
                {
                     tmp = tmp->right;
                }
            }
            else 
            {
                return;
            }
        }
    }
}

void searchNode(node **root, int number)
{
    if ((*root) == NULL)
    {
        printf("tree가 형성되지 않았어요\n");
    } else {
        node *tmp = (*root);
        while (tmp != NULL)
        {
            if (number < tmp->data) 
            {
                if (tmp->left == NULL)
                {
                    printf("No Node in current tree\n");
                    break;
                } else 
                {
                    tmp= tmp->left;
                }
            } 
            // new node의 숫자가 tmp의 숫자보다 크다면
            else if ( number > tmp->data)
            {
                if (tmp->right == NULL)
                {
                    printf("No Node in current tree\n");
                    break;
                }
                else
                {
                     tmp = tmp->right;
                }
            }
            else 
            {
                node *searchedNode = malloc(sizeof(node));
                searchedNode->data = tmp->data;
                searchedNode->left = tmp->left;
                searchedNode->right = tmp->right;
                printf("찾은 tree의 값: %d\n", searchedNode->data);
                if (searchedNode->left != NULL)
                {
                    printf("찾은 node->left->data의 값: %d\n", searchedNode->left->data);
                }
                if (searchedNode->right != NULL)
                {
                    printf("찾은 node->right->data의 값: %d\n", searchedNode->right->data);
                }
                free(searchedNode);
                break;
            }
        }
    }
}

node* deleteNode(node *root, int number)
{
    //root가 NULL인 경우에는 그대로 반환
    if (root == NULL)
        return root;
    
    // 삭제하려는 숫자가 root -> data보다 작다면
    if (number < root->data)
    {
    // 삭제하려는 숫자가 sub tree의 왼쪽 자식 node의 값과 같아질 때 까지 재귀적으로 호출
        root->left = deleteNode(root->left, number);
        return root;
    } 
    // 삭제하려는 숫자가 root -> data보다 크다면
    else if ( number > root->data)
    {
    // 삭제하려는 숫자가 sub tree의 오른쪽 자식 node의 값과 같아질 때 까지 재귀적으로 호출
        root->right = deleteNode(root->right, number);
        return root;
    }
    
    //삭제하려는 숫자가 sub tree의 자식 node의 값과 같아진 경우
    // 삭제하려는 노드의 자식은 자식 노드가 1개이거나 없거나
    if (root->left == NULL) 
    {
        node *temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        node *temp = root->left;
        free(root);
        return temp;
    }

    // 삭제하려는 노드의 자식이 2개인 경우
    // inorder Successor(오른쪽 subtree 중 가장 작은 값)을 get
    node *succParent = root;
    node *succ = root->right;
    while (succ->left != NULL)
    {
        succParent = succ;
        succ = succ->left;
    }
    
    // inorder successor의 값을 해당 node에 복사.
    root->data = succ->data;

    // inorder successor를 삭제.
    if (succParent->left == succ)
        succParent->left = succ->right;
    else 
        succParent->right = succ->right;

    free(succ);
    return root;
}

node* createNewNode(int data)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return new_node;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void inOrder(node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d", root->data);
        inOrder(root->right);
    }
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->data);
    print_tree(root->right);
}