#include <stdio.h>
#include <stdlib.h>

#define MAX 3

struct node {
    int keys[MAX];
    struct node *children[MAX+1];
    int numKeys;
    int isLeaf;
    struct node *next;
};

struct node *root = NULL;

struct node *createNode(int isLeaf) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    newNode->next = NULL;
    for(int i=0;i<MAX+1;i++) newNode->children[i] = NULL;
    return newNode;
}

struct node *search(struct node *root,int key) {
    if(root==NULL) return NULL;
    int i=0;
    while(i<root->numKeys && key>root->keys[i]) i++;
    if(root->isLeaf) {
        if(i<root->numKeys && root->keys[i]==key) return root;
        return NULL;
    }
    return search(root->children[i],key);
}

void insertIntoLeaf(struct node *leaf,int key) {
    int i;
    for(i=leaf->numKeys-1;i>=0 && leaf->keys[i]>key;i--) leaf->keys[i+1]=leaf->keys[i];
    leaf->keys[i+1]=key;
    leaf->numKeys++;
}

void splitLeaf(struct node *parent,struct node *leaf,int key) {
    int temp[MAX+1];
    for(int i=0;i<MAX;i++) temp[i]=leaf->keys[i];
    int i;
    for(i=MAX-1;i>=0 && temp[i]>key;i--) temp[i+1]=temp[i];
    temp[i+1]=key;
    struct node *newLeaf=createNode(1);
    leaf->numKeys=(MAX+1)/2;
    newLeaf->numKeys=MAX+1-leaf->numKeys;
    for(i=0;i<leaf->numKeys;i++) leaf->keys[i]=temp[i];
    for(i=0;i<newLeaf->numKeys;i++) newLeaf->keys[i]=temp[i+leaf->numKeys];
    newLeaf->next=leaf->next;
    leaf->next=newLeaf;
    if(parent==NULL) {
        root=createNode(0);
        root->keys[0]=newLeaf->keys[0];
        root->children[0]=leaf;
        root->children[1]=newLeaf;
        root->numKeys=1;
    } else {
        parent->keys[parent->numKeys]=newLeaf->keys[0];
        parent->children[parent->numKeys+1]=newLeaf;
        parent->numKeys++;
    }
}

void insert(int key) {
    if(root==NULL) {
        root=createNode(1);
        root->keys[0]=key;
        root->numKeys=1;
        return;
    }
    struct node *current=root,*parent=NULL;
    while(!current->isLeaf) {
        parent=current;
        int i=0;
        while(i<current->numKeys && key>=current->keys[i]) i++;
        current=current->children[i];
    }
    if(current->numKeys<MAX) insertIntoLeaf(current,key);
    else splitLeaf(parent,current,key);
}

void deleteKey(int key) {
    if(root==NULL) {
        printf("Tree is Empty\n");
        return;
    }
    struct node *current=root;
    while(!current->isLeaf) {
        int i=0;
        while(i<current->numKeys && key>=current->keys[i]) i++;
        current=current->children[i];
    }
    int found=0;
    for(int i=0;i<current->numKeys;i++) {
        if(current->keys[i]==key) {
            found=1;
            for(int j=i;j<current->numKeys-1;j++) current->keys[j]=current->keys[j+1];
            current->numKeys--;
            printf("Key Deleted\n");
            break;
        }
    }
    if(!found) printf("Key Not Found\n");
}

void traverseLeaves() {
    if(root==NULL) {
        printf("Tree is Empty\n");
        return;
    }
    struct node *current=root;
    while(!current->isLeaf) current=current->children[0];
    printf("Leaf Nodes: ");
    while(current!=NULL) {
        for(int i=0;i<current->numKeys;i++) printf("%d ",current->keys[i]);
        current=current->next;
    }
    printf("\n");
}

int main() {
    int choice,value;
    while(1) {
        printf("\n===== B+ TREE MENU =====\n");
        printf("1. Insert Key\n2. Delete Key\n3. Search Key\n4. Traverse Leaf Nodes\n5. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d",&choice);
        switch(choice) {
            case 1:
                printf("Enter Key to Insert: ");
                scanf("%d",&value);
                insert(value);
                printf("Key Inserted\n");
                break;
            case 2:
                printf("Enter Key to Delete: ");
                scanf("%d",&value);
                deleteKey(value);
                break;
            case 3:
                printf("Enter Key to Search: ");
                scanf("%d",&value);
                if(search(root,value)!=NULL) printf("Key Found\n");
                else printf("Key Not Found\n");
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
