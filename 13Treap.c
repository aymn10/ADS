// Design and implement a Treap Data Structure
// using randomized algorithms by combining
// Binary Search Tree and Heap properties.

// • Store a key and random priority in each node
// • Implement insertion operation
// • Implement deletion operation
// • Implement search operation
// • Use rotations to maintain balance and heap property

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int key;
    int priority;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int key)
{
    struct Node *node=(struct Node *)malloc(sizeof(struct Node));
    node->key=key;
    node->priority=rand()%100;
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

struct Node *insert(struct Node *root,int key)
{
    if(root==NULL)
    {
        return createNode(key);
    }
    if(key<root->key)
    {
        root->left=insert(root->left,key);
        if(root->left->priority>root->priority)
        {
            root=rightRotate(root);
        }
    }
    else if(key>root->key)
    {

        root->right=insert(root->right,key);
        if(root->right->priority>root->priority)
        {
            root=leftRotate(root);
        }
    }
    return root;
}

struct Node *deleteNode(struct Node *root,int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(key<root->key)
    {
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->key)
    {
        root->right=deleteNode(root->right,key);
    }
    else
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left==NULL)
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
        else
        {
            if(root->left->priority>
               root->right->priority)
            {
                root=rightRotate(root);
                root->right= deleteNode(root->right,key);
            }

            else
            {
                root=leftRotate(root);
                root->left= deleteNode(root->left,key);
            }
        }
    }

    return root;
}

    int search(struct Node *root,int key)
    {
        if(root==NULL)
        {
            return 0;
        }

        if(root->key==key)
        {
            return 1;
        }

        if(key<root->key)
        {
            return search(root->left,key);
        }

        return search(root->right,key);
    }

void inorder(struct Node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);

        printf("Key = %d  Priority = %d\n",
               root->key,
               root->priority);

        inorder(root->right);
    }
}

int main()
{
    struct Node *root=NULL;

    int choice,value;

    srand(time(NULL));

    while(1)
    {
        printf("\n===== TREAP OPERATIONS =====\n");

        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display Treap\n");
        printf("5. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d",&value);

                root=insert(root,value);

                printf("Node Inserted\n");
                break;

            case 2:
                printf("Enter Value to Delete: ");
                scanf("%d",&value);

                root=deleteNode(root,value);

                printf("Node Deleted\n");
                break;

            case 3:
                printf("Enter Value to Search: ");
                scanf("%d",&value);

                if(search(root,value))
                {
                    printf("Node Found\n");
                }
                else
                {
                    printf("Node Not Found\n");
                }

                break;

            case 4:
                printf("\nTreap Elements:\n");

                inorder(root);

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