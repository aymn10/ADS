// Design and implement a Red-Black Tree
// supporting insertion, deletion, and
// display operations while preserving
// balancing properties.
//
// • Insert nodes into the Red-Black Tree
// • Delete a specified node
// • Display the tree using inorder traversal
// • Maintain Red-Black Tree properties

#define RED 1
#define BLACK 0

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *root=NULL;

struct Node *createNode(int data)
{
    struct Node *node=(struct Node *)malloc(sizeof(struct Node));

    node->data=data;
    node->color=RED;
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;

    return node;
}

void leftRotate(struct Node *x)
{
    struct Node *y=x->right;

    x->right=y->left;

    if(y->left!=NULL)
    {
        y->left->parent=x;
    }

    y->parent=x->parent;

    if(x->parent==NULL)
    {
        root=y;
    }

    else if(x==x->parent->left)
    {
        x->parent->left=y;
    }

    else
    {
        x->parent->right=y;
    }

    y->left=x;
    x->parent=y;
}

void rightRotate(struct Node *y)
{
    struct Node *x=y->left;

    y->left=x->right;

    if(x->right!=NULL)
    {
        x->right->parent=y;
    }

    x->parent=y->parent;

    if(y->parent==NULL)
    {
        root=x;
    }

    else if(y==y->parent->left)
    {
        y->parent->left=x;
    }

    else
    {
        y->parent->right=x;
    }

    x->right=y;
    y->parent=x;
}

void fixInsert(struct Node *z)
{
    while(z->parent!=NULL &&
          z->parent->color==RED)
    {
        if(z->parent==
           z->parent->parent->left)
        {
            struct Node *y=
            z->parent->parent->right;

            if(y!=NULL &&
               y->color==RED)
            {
                z->parent->color=BLACK;
                y->color=BLACK;

                z->parent->parent->color=RED;

                z=z->parent->parent;
            }

            else
            {
                if(z==z->parent->right)
                {
                    z=z->parent;

                    leftRotate(z);
                }

                z->parent->color=BLACK;

                z->parent->parent->color=RED;

                rightRotate(z->parent->parent);
            }
        }

        else
        {
            struct Node *y=
            z->parent->parent->left;

            if(y!=NULL &&
               y->color==RED)
            {
                z->parent->color=BLACK;
                y->color=BLACK;

                z->parent->parent->color=RED;

                z=z->parent->parent;
            }

            else
            {
                if(z==z->parent->left)
                {
                    z=z->parent;

                    rightRotate(z);
                }

                z->parent->color=BLACK;

                z->parent->parent->color=RED;

                leftRotate(z->parent->parent);
            }
        }
    }

    root->color=BLACK;
}

void insert(int data)
{
    struct Node *z=createNode(data);

    struct Node *y=NULL;
    struct Node *x=root;

    while(x!=NULL)
    {
        y=x;

        if(z->data<x->data)
        {
            x=x->left;
        }

        else
        {
            x=x->right;
        }
    }

    z->parent=y;

    if(y==NULL)
    {
        root=z;
    }

    else if(z->data<y->data)
    {
        y->left=z;
    }

    else
    {
        y->right=z;
    }

    fixInsert(z);
}

struct Node *minimum(struct Node *node)
{
    while(node->left!=NULL)
    {
        node=node->left;
    }

    return node;
}

struct Node *deleteNode(struct Node *root,
                        int key)
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
        if(root->left==NULL)
        {
            struct Node *temp=root->right;

            free(root);

            return temp;
        }

        else if(root->right==NULL)
        {
            struct Node *temp=root->left;

            free(root);

            return temp;
        }

        struct Node *temp=
        minimum(root->right);

        root->data=temp->data;

        root->right=
        deleteNode(root->right,
                   temp->data);
    }

    return root;
}

void inorder(struct Node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);

        if(root->color==BLACK)
        {
            printf("%d(B) ",root->data);
        }

        else
        {
            printf("%d(R) ",root->data);
        }

        inorder(root->right);
    }
}

int main()
{
    int choice,data;

    while(1)
    {
        printf("\n===== RED BLACK TREE =====\n");

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

                insert(data);

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