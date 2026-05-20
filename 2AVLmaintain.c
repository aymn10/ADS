/*
Design and implement an AVL Tree supporting insertion, display, and search operations while maintaining tree balance using rotations.
• Insert nodes into the AVL Tree
• Display the tree using inorder traversal
• Search for a given key in the tree
• Perform required balancing rotations
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

int height(struct Node *node)
{
    if(node==NULL)
    {
        return 0;
    }

    return node->height;
}

int max(int a,int b)
{
    return(a>b)?a:b;
}

struct Node *createNode(int data)
{
    struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));

    newnode->data=data;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->height=1;

    return newnode;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x=y->left;
    struct Node *t2=x->right;

    x->right=y;
    y->left=t2;

    y->height=
    max(height(y->left),
        height(y->right))+1;

    x->height=
    max(height(x->left),
        height(x->right))+1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y=x->right;
    struct Node *t2=y->left;

    y->left=x;
    x->right=t2;

    x->height=
    max(height(x->left),
        height(x->right))+1;

    y->height=
    max(height(y->left),
        height(y->right))+1;

    return y;
}

struct Node *leftRightRotate(struct Node *node)
{
    node->left=
    leftRotate(node->left);

    return rightRotate(node);
}

struct Node *rightLeftRotate(struct Node *node)
{
    node->right=
    rightRotate(node->right);

    return leftRotate(node);
}

int getBalance(struct Node *node)
{
    if(node==NULL)
    {
        return 0;
    }

    return height(node->left)-
           height(node->right);
}

struct Node *insert(struct Node *root,int data)
{
    if(root==NULL)
    {
        return createNode(data);
    }

    if(data<root->data)
    {
        root->left=
        insert(root->left,data);
    }

    else if(data>root->data)
    {
        root->right=
        insert(root->right,data);
    }

    else
    {
        return root;
    }

    root->height=
    max(height(root->left),
        height(root->right))+1;

    int balance=getBalance(root);

    if(balance>1 &&
       data<root->left->data)
    {
        return rightRotate(root);
    }

    if(balance<-1 &&
       data>root->right->data)
    {
        return leftRotate(root);
    }

    if(balance>1 &&
       data>root->left->data)
    {
        return leftRightRotate(root);
    }

    if(balance<-1 &&
       data<root->right->data)
    {
        return rightLeftRotate(root);
    }

    return root;
}

void inorder(struct Node *root)
{
    if(root==NULL)
    {
        return;
    }

    inorder(root->left);

    printf("%d ",root->data);

    inorder(root->right);
}

struct Node *search(struct Node *root,int key)
{
    if(root==NULL ||
       root->data==key)
    {
        return root;
    }

    if(key<root->data)
    {
        return search(root->left,key);
    }

    return search(root->right,key);
}

int main()
{
    struct Node *root=NULL;

    int choice,data;

    while(1)
    {
        printf("\n===== AVL TREE =====\n");

        printf("1. Insert Node\n");
        printf("2. Display Inorder\n");
        printf("3. Search Node\n");
        printf("4. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter Data: ");
                scanf("%d",&data);

                root=insert(root,data);

                printf("Node Inserted\n");
                break;

            case 2:
                printf("Inorder Traversal:\n");

                inorder(root);

                printf("\n");
                break;

            case 3:
                printf("Enter Key to Search: ");
                scanf("%d",&data);

                if(search(root,data))
                {
                    printf("Node Found\n");
                }

                else
                {
                    printf("Node Not Found\n");
                }

                break;

            case 4:
                printf("Program Exited\n");

                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}

