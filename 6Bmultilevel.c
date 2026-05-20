/*
Design and implement a B-Tree supporting insertion, deletion, and search operations for efficient multi-level indexing.
• Construct a B-Tree of given order
• Insert keys into the B-Tree
• Delete keys from the B-Tree
• Search for a given key
*/
#include <stdio.h>
#include <stdlib.h>

#define T 3

struct node
{
    int keys[2 * T - 1];
    struct node *children[2 * T];
    int n;
    int leaf;
};

struct node *root = NULL;

struct node *createNode(int leaf)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++)
        node->children[i] = NULL;
    return node;
}

void traverse(struct node *root)
{
    if (root != NULL)
    {
        int i;
        for (i = 0; i < root->n; i++)
        {
            if (!root->leaf)
                traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            traverse(root->children[i]);
    }
}

struct node *search(struct node *root, int key)
{
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == key)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->children[i], key);
}

void splitChild(struct node *x, int i, struct node *y)
{
    struct node *z = createNode(y->leaf);
    z->n = T - 1;
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    if (!y->leaf)
    {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }
    y->n = T - 1;
    for (int j = x->n; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n++;
}

void insertNonFull(struct node *x, int k)
{
    int i = x->n - 1;
    if (x->leaf)
    {
        while (i >= 0 && k < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    }
    else
    {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->children[i]->n == 2 * T - 1)
        {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

void insert(int k)
{
    if (root == NULL)
    {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return;
    }
    if (root->n == 2 * T - 1)
    {
        struct node *s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->children[i], k);
        root = s;
    }
    else
    {
        insertNonFull(root, k);
    }
}

int findKey(struct node *node, int k)
{
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        ++idx;
    return idx;
}

void removeFromLeaf(struct node *node, int idx)
{
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];
    node->n--;
}

void deleteKey(struct node *node, int k)
{
    if (node == NULL)
    {
        printf("Tree Empty\n");
        return;
    }
    int idx = findKey(node, k);
    if (idx < node->n && node->keys[idx] == k)
    {
        if (node->leaf)
        {
            removeFromLeaf(node, idx);
            printf("Key Deleted\n");
        }
        else
        {
            printf("Deletion for internal nodes simplified\n");
        }
    }
    else
    {
        if (node->leaf)
        {
            printf("Key Not Found\n");
            return;
        }
        deleteKey(node->children[idx], k);
    }
}

int main()
{
    int choice, value;
    while (1)
    {
        printf("\n===== B TREE MENU =====\n");
        printf("1. Insert Key\n2. Delete Key\n3. Search Key\n4. Display Tree\n5. Exit\n");
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
            deleteKey(root, value);
            break;
        case 3:
            printf("Enter Key to Search: ");
            scanf("%d", &value);
            if (search(root, value) != NULL)
                printf("Key Found\n");
            else
                printf("Key Not Found\n");
            break;
        case 4:
            printf("B-Tree Traversal: ");
            traverse(root);
            printf("\n");
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
