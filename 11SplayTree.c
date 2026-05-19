// Design and implement a Splay Tree
// supporting self-adjusting operations through splaying.
//
// • Implement insertion operation
// • Implement search operation with splaying
// • Implement deletion operation
// • Display the tree after each splay operation

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *node=(struct Node *)malloc(sizeof(struct Node));
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    return node;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x=y->left;

    y->left=x->right;
    x->right=y;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y=x->right;

    x->right=y->left;
    y->left=x;

    return y;
}

struct Node *splay(struct Node *root,int key)
{
    if(root==NULL || root->data==key)
    {
        return root;
    }

    if(key<root->data)
    {
        if(root->left==NULL)
        {
            return root;
        }

        if(key<root->left->data)
        {
            root->left->left=
            splay(root->left->left,key);

            root=rightRotate(root);
        }

        else if(key>root->left->data)
        {
            root->left->right=
            splay(root->left->right,key);

            if(root->left->right!=NULL)
            {
                root->left=
                leftRotate(root->left);
            }
        }

        return(root->left==NULL)?
               root:rightRotate(root);
    }

    else
    {
        if(root->right==NULL)
        {
            return root;
        }

        if(key>root->right->data)
        {
            root->right->right=
            splay(root->right->right,key);

            root=leftRotate(root);
        }

        else if(key<root->right->data)
        {
            root->right->left=
            splay(root->right->left,key);

            if(root->right->left!=NULL)
            {
                root->right=
                rightRotate(root->right);
            }
        }

        return(root->right==NULL)?
               root:leftRotate(root);
    }
}

struct Node *insert(struct Node *root,int key)
{
    if(root==NULL)
    {
        return createNode(key);
    }

    root=splay(root,key);

    if(root->data==key)
    {
        return root;
    }

    struct Node *newNode=createNode(key);

    if(key<root->data)
    {
        newNode->right=root;
        newNode->left=root->left;
        root->left=NULL;
    }

    else
    {
        newNode->left=root;
        newNode->right=root->right;
        root->right=NULL;
    }

    return newNode;
}

struct Node *deleteNode(struct Node *root,int key)
{
    struct Node *temp;

    if(root==NULL)
    {
        return NULL;
    }

    root=splay(root,key);

    if(root->data!=key)
    {
        printf("Node Not Found\n");
        return root;
    }

    if(root->left==NULL)
    {
        temp=root;
        root=root->right;
    }

    else
    {
        temp=root;

        root=splay(root->left,key);

        root->right=temp->right;
    }

    free(temp);

    return root;
}

void inorder(struct Node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);

        printf("%d ",root->data);

        inorder(root->right);
    }
}

void display(struct Node *root)
{
    printf("\nTree (Inorder): ");

    inorder(root);

    printf("\n");
}

int main()
{
    struct Node *root=NULL;

    int choice,data;

    while(1)
    {
        printf("\n===== SPLAY TREE OPERATIONS =====\n");

        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter Data: ");
                scanf("%d",&data);

                root=insert(root,data);

                printf("After Splaying:\n");

                display(root);

                break;

            case 2:
                printf("Enter Data to Search: ");
                scanf("%d",&data);

                root=splay(root,data);

                if(root!=NULL &&
                   root->data==data)
                {
                    printf("Node Found\n");
                }

                else
                {
                    printf("Node Not Found\n");
                }

                printf("After Splaying:\n");

                display(root);

                break;

            case 3:
                printf("Enter Data to Delete: ");
                scanf("%d",&data);

                root=deleteNode(root,data);

                printf("After Splaying:\n");

                display(root);

                break;

            case 4:
                display(root);

                break;

            case 5:
                printf("Program Exited\n");

                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}