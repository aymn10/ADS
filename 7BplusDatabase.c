/*
Design and implement a B+ Tree supporting insertion, deletion, and search operations for efficient database indexing.
• Construct a B+ Tree of given order
• Insert records into the B+ Tree
• Delete records from the B+ Tree
• Search for a given key
• Traverse leaf nodes sequentially
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 3

typedef struct Node
{
    int keys[MAX];
    struct Node *children[MAX + 1];
    int numKeys;
    int isLeaf;
    struct Node *next;
} Node;

Node *root = NULL;

Node *createNode(int isLeaf)
{
    Node *newNode =
        (Node *)malloc(sizeof(Node));

    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    newNode->next = NULL;

    for (int i = 0; i < MAX + 1; i++)
    {
        newNode->children[i] = NULL;
    }

    return newNode;
}

Node *search(Node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }

    int i = 0;

    while (i < root->numKeys &&
           key > root->keys[i])
    {
        i++;
    }

    if (root->isLeaf)
    {
        if (i < root->numKeys &&
            root->keys[i] == key)
        {
            return root;
        }

        return NULL;
    }

    return search(root->children[i], key);
}

void insertIntoLeaf(Node *leaf, int key)
{
    int i;

    for (i = leaf->numKeys - 1;
         i >= 0 &&
         leaf->keys[i] > key;
         i--)
    {
        leaf->keys[i + 1] =
            leaf->keys[i];
    }

    leaf->keys[i + 1] = key;

    leaf->numKeys++;
}

void splitLeaf(Node *parent,
               Node *leaf,
               int key)
{
    int temp[MAX + 1];

    for (int i = 0; i < MAX; i++)
    {
        temp[i] = leaf->keys[i];
    }

    int i;

    for (i = MAX - 1;
         i >= 0 &&
         temp[i] > key;
         i--)
    {
        temp[i + 1] = temp[i];
    }

    temp[i + 1] = key;

    Node *newLeaf =
        createNode(1);

    leaf->numKeys =
        (MAX + 1) / 2;

    newLeaf->numKeys =
        MAX + 1 - leaf->numKeys;

    for (i = 0; i < leaf->numKeys; i++)
    {
        leaf->keys[i] = temp[i];
    }

    for (i = 0;
         i < newLeaf->numKeys;
         i++)
    {
        newLeaf->keys[i] =
            temp[i + leaf->numKeys];
    }

    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    if (parent == NULL)
    {
        root = createNode(0);

        root->keys[0] =
            newLeaf->keys[0];

        root->children[0] = leaf;
        root->children[1] = newLeaf;

        root->numKeys = 1;
    }

    else
    {
        parent->keys[parent->numKeys] =
            newLeaf->keys[0];

        parent->children[parent->numKeys + 1] =
            newLeaf;

        parent->numKeys++;
    }
}

void insert(int key)
{
    if (root == NULL)
    {
        root = createNode(1);

        root->keys[0] = key;
        root->numKeys = 1;

        return;
    }

    Node *current = root;
    Node *parent = NULL;

    while (!current->isLeaf)
    {
        parent = current;

        int i = 0;

        while (i < current->numKeys &&
               key >= current->keys[i])
        {
            i++;
        }

        current = current->children[i];
    }

    if (current->numKeys < MAX)
    {
        insertIntoLeaf(current, key);
    }

    else
    {
        splitLeaf(parent, current, key);
    }
}

void deleteKey(int key)
{
    if (root == NULL)
    {
        printf("Tree is Empty\n");

        return;
    }

    Node *current = root;

    while (!current->isLeaf)
    {
        int i = 0;

        while (i < current->numKeys &&
               key >= current->keys[i])
        {
            i++;
        }

        current = current->children[i];
    }

    int found = 0;

    for (int i = 0;
         i < current->numKeys;
         i++)
    {
        if (current->keys[i] == key)
        {
            found = 1;

            for (int j = i;
                 j < current->numKeys - 1;
                 j++)
            {
                current->keys[j] =
                    current->keys[j + 1];
            }

            current->numKeys--;

            printf("Key Deleted\n");

            break;
        }
    }

    if (!found)
    {
        printf("Key Not Found\n");
    }
}

void traverseLeaves()
{
    if (root == NULL)
    {
        printf("Tree is Empty\n");

        return;
    }

    Node *current = root;

    while (!current->isLeaf)
    {
        current = current->children[0];
    }

    printf("Leaf Nodes: ");

    while (current != NULL)
    {
        for (int i = 0;
             i < current->numKeys;
             i++)
        {
            printf("%d ",
                   current->keys[i]);
        }

        current = current->next;
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n===== B+ TREE MENU =====\n");

        printf("1. Insert Key\n");
        printf("2. Delete Key\n");
        printf("3. Search Key\n");
        printf("4. Traverse Leaf Nodes\n");
        printf("5. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Key to Insert: ");
            scanf("%d", &value);

            insert(value);

            printf("Key Inserted\n");
            break;

        case 2:
            printf("Enter Key to Delete: ");
            scanf("%d", &value);

            deleteKey(value);

            break;

        case 3:
            printf("Enter Key to Search: ");
            scanf("%d", &value);

            if (search(root, value) != NULL)
            {
                printf("Key Found\n");
            }

            else
            {
                printf("Key Not Found\n");
            }

            break;

        case 4:
            traverseLeaves();

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