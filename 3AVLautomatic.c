// Design and implement an AVL Tree
// supporting insertion, deletion, and
// display operations with automatic balancing.
//
// • Insert nodes into the AVL Tree
// • Delete a specified node from the tree
// • Display the tree using inorder traversal
// • Maintain AVL balance using rotations

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
        root->left=
        leftRotate(root->left);

        return rightRotate(root);
    }

    if(balance<-1 &&
       data<root->right->data)
    {
        root->right=
        rightRotate(root->right);

        return leftRotate(root);
    }

    return root;
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current=node;

    while(current->left!=NULL)
    {
        current=current->left;
    }

    return current;
}

struct Node *deleteNode(struct Node *root,int key)
{
    if(root==NULL)
    {
        return root;
    }

    if(key<root->data)
    {
        root->left=
        deleteNode(root->left,key);
    }

    else if(key>root->data)
    {
        root->right=
        deleteNode(root->right,key);
    }

    else
    {
        if(root->left==NULL ||
           root->right==NULL)
        {
            struct Node *temp;

            if(root->left!=NULL)
            {
                temp=root->left;
            }

            else
            {
                temp=root->right;
            }

            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }

            else
            {
                *root=*temp;
            }

            free(temp);
        }

        else
        {
            struct Node *temp=
            minValueNode(root->right);

            root->data=temp->data;

            root->right=
            deleteNode(root->right,
                       temp->data);
        }
    }

    if(root==NULL)
    {
        return root;
    }

    root->height=
    max(height(root->left),
        height(root->right))+1;

    int balance=getBalance(root);

    if(balance>1 &&
       getBalance(root->left)>=0)
    {
        return rightRotate(root);
    }

    if(balance>1 &&
       getBalance(root->left)<0)
    {
        root->left=
        leftRotate(root->left);

        return rightRotate(root);
    }

    if(balance<-1 &&
       getBalance(root->right)<=0)
    {
        return leftRotate(root);
    }

    if(balance<-1 &&
       getBalance(root->right)>0)
    {
        root->right=
        rightRotate(root->right);

        return leftRotate(root);
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

int main()
{
    struct Node *root=NULL;

    int choice,data;

    while(1)
    {
        printf("\n===== AVL TREE =====\n");

        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Display Inorder\n");
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
                printf("Enter Data to Delete: ");
                scanf("%d",&data);

                root=deleteNode(root,data);

                printf("Node Deleted\n");
                break;

            case 3:
                printf("Inorder Traversal:\n");

                inorder(root);

                printf("\n");
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