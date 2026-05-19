// Design and implement a Trie Data Structure
// supporting insertion, search, and prefix matching operations.
//
// • Insert words into the Trie
// • Search for a given word
// • Perform prefix matching
// • Display all words matching the prefix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

struct TrieNode
{
    struct TrieNode *children[SIZE];
    int isEndOfWord;
};

struct TrieNode *createNode()
{
    struct TrieNode *node=(struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->isEndOfWord=0;
    for(int i=0;i<SIZE;i++)
    {
        node->children[i]=NULL;
    }
    return node;
}

void insert(struct TrieNode *root,char word[])
{
    struct TrieNode *current=root;

    for(int i=0;word[i]!='\0';i++)
    {
        int index=word[i]-'a';
        if(current->children[index]==NULL)
        {
            current->children[index]=createNode();
        }
        current=current->children[index];
    }
    
    current->isEndOfWord=1;
    printf("Word Inserted Successfully\n");
}

int search(struct TrieNode *root,char word[])
{
    struct TrieNode *current=root;

    for(int i=0;word[i]!='\0';i++)
    {
        int index=word[i]-'a';

        if(current->children[index]==NULL)
        {
            return 0;
        }

        current=current->children[index];
    }

    return current->isEndOfWord;
}

void displayWords(struct TrieNode *root,char word[],int level)
{
    if(root->isEndOfWord)
    {
        word[level]='\0';
        printf("%s\n",word);
    }

    for(int i=0;i<SIZE;i++)
    {
        if(root->children[i]!=NULL)
        {
            word[level]=i+'a';
            displayWords(root->children[i],word,level+1);
        }
    }
}

void prefixMatch(struct TrieNode *root,char prefix[])
{
    struct TrieNode *current=root;

    for(int i=0;prefix[i]!='\0';i++)
    {
        int index=prefix[i]-'a';

        if(current->children[index]==NULL)
        {
            printf("No words found with this prefix\n");
            return;
        }

        current=current->children[index];
    }

    char word[100];

    strcpy(word,prefix);

    printf("Words with prefix \"%s\":\n",prefix);

    displayWords(current,word,strlen(prefix));
}

int main()
{
    struct TrieNode *root=createNode();

    int choice;
    char word[100];

    while(1)
    {
        printf("\n===== TRIE OPERATIONS =====\n");
        printf("1. Insert Word\n");
        printf("2. Search Word\n");
        printf("3. Prefix Matching\n");
        printf("4. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                printf("Enter Word: ");
                scanf("%s",word);

                insert(root,word);

                break;

            case 2:

                printf("Enter Word to Search: ");
                scanf("%s",word);

                if(search(root,word))
                {
                    printf("Word Found\n");
                }

                else
                {
                    printf("Word Not Found\n");
                }

                break;

            case 3:

                printf("Enter Prefix: ");
                scanf("%s",word);

                prefixMatch(root,word);

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

/*
Input:
apple

Output:
Word Inserted Successfully
Word Found
*/