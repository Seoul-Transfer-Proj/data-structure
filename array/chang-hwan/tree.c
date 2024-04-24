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

int main(void)
{
    node *tree = NULL;
    insertNode(&tree, 7);
    insertNode(&tree, 6);
    insertNode(&tree, 15);
    insertNode(&tree, 76);
    insertNode(&tree, 9);
    insertNode(&tree, 5);
    insertNode(&tree, 7);
    insertNode(&tree, 4);
    insertNode(&tree, 177);
    insertNode(&tree, 46);
    printBinaryTree(tree, 0);
    searchNode(&tree, 4);
    searchNode(&tree, 15);
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
        printf("tree가 형성되지 않았어요");
    } else {
        node *tmp = (*root);
        while (tmp != NULL)
        {
            if (number < tmp->data) 
            {
                if (tmp->left == NULL)
                {
                    printf("No Node in current tree");
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
                    printf("No Node in current tree");
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

void printBinaryTree(node *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < level; i++)
    {
        printf("   ");
    }
    printf("%d\n", root->data);

    printBinaryTree(root->left, level + 1);
    printBinaryTree(root->right, level + 1);
}