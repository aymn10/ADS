// Design and implement an Interval Tree
// supporting efficient interval overlap queries.
//
// • Insert an interval into the tree
// • Delete an interval from the tree
// • Search for overlapping intervals
// • Display the tree using inorder traversal

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int low,high,max;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int low,int high)
{
    struct Node *node=(struct Node *)malloc(sizeof(struct Node));
    node->low=low;
    node->high=high;
    node->max=high;
    node->left=NULL;
    node->right=NULL;
    return node;
}

int getMax(int a,int b)
{
    return (a>b)?a:b;
}

struct Node *insert(struct Node *root,int low,int high)
{
    if(root==NULL)
    {
        return createNode(low,high);
    }

    if(low<root->low)
    {
        root->left=insert(root->left,low,high);
    }

    else
    {
        root->right=insert(root->right,low,high);
    }

    if(root->max<high)
    {
        root->max=high;
    }

    return root;
}

int isOverlap(int low1,int high1,int low2,int high2)
{
    return (low1<=high2 && low2<=high1);
}

void searchOverlap(struct Node *root,int low,int high)
{
    if(root==NULL)
    {
        return;
    }

    if(isOverlap(root->low,root->high,low,high))
    {
        printf("Overlapping Interval: [%d,%d]\n",
               root->low,
               root->high);
    }

    if(root->left!=NULL &&
       root->left->max>=low)
    {
        searchOverlap(root->left,low,high);
    }
    else 
        searchOverlap(root->right,low,high);
}

struct Node *minValueNode(struct Node *root)
{
    struct Node *current=root;

    while(current->left!=NULL)
    {
        current=current->left;
    }

    return current;
}

struct Node *deleteNode(struct Node *root,int low,int high)
{
    if(root==NULL)
    {
        return NULL;
    }

    if(low<root->low)
    {
        root->left=deleteNode(root->left,low,high);
    }

    else if(low>root->low)
    {
        root->right=deleteNode(root->right,low,high);
    }

    else if(root->high==high)
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

        struct Node *temp=minValueNode(root->right);

        root->low=temp->low;
        root->high=temp->high;

        root->right=deleteNode(root->right, temp->low, temp->high);
    }

    if(root!=NULL)
    {
        root->max=root->high;

        if(root->left!=NULL)
        {
            root->max=getMax(root->max, root->left->max);
        }

        if(root->right!=NULL)
        {
            root->max=getMax(root->max, root->right->max);
        }       
    }

    return root;
}

void inorder(struct Node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);

        printf("[%d,%d] Max=%d\n",
               root->low,
               root->high,
               root->max);

        inorder(root->right);
    }
}

int main()
{
    struct Node *root=NULL;

    int choice;
    int low,high;

    while(1)
    {
        printf("\n===== INTERVAL TREE =====\n");

        printf("1. Insert Interval\n");
        printf("2. Delete Interval\n");
        printf("3. Search Overlap\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter Low and High: ");
                scanf("%d%d",&low,&high);

                root=insert(root,low,high);

                printf("Interval Inserted\n");
                break;

            case 2:
                printf("Enter Low and High: ");
                scanf("%d%d",&low,&high);

                root=deleteNode(root,low,high);

                printf("Interval Deleted\n");
                break;

            case 3:
                printf("Enter Search Interval: ");
                scanf("%d%d",&low,&high);

                printf("Overlapping Intervals:\n");

                searchOverlap(root,low,high);
                break;

            case 4:
                printf("\nInorder Traversal:\n");

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