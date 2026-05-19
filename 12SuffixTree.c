// Design and implement a Suffix Tree for a given string
// and support pattern matching operations.
//
// • Construct the Suffix Tree for the input string
// • Search whether a pattern exists in the string
// • Display all suffixes using tree traversal
// • Find the longest repeated substring

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Node
{
    struct Node *children[26];
    int isEnd;
};

struct Node *createNode()
{
    struct Node *node=(struct Node *)malloc(sizeof(struct Node));
    node->isEnd=0;
    for(int i=0;i<26;i++)
    {
        node->children[i]=NULL;
    }
    return node;
}

void insertSuffix(struct Node *root,char *suffix)
{
    struct Node *current=root;

    for(int i=0;suffix[i]!='\0';i++)
    {
        int index=suffix[i]-'a';

        if(current->children[index]==NULL)
        {
            current->children[index]=createNode();
        }

        current=current->children[index];
    }

    current->isEnd=1;
}

void buildSuffixTree(struct Node *root,char str[])
{
    int n=strlen(str);

    for(int i=0;i<n;i++)
    {
        insertSuffix(root,str+i);
    }
}

int searchPattern(struct Node *root,char pattern[])
{
    struct Node *current=root;

    for(int i=0;pattern[i]!='\0';i++)
    {
        int index=pattern[i]-'a';

        if(current->children[index]==NULL)
        {
            return 0;
        }

        current=current->children[index];
    }

    return 1;
}

void displaySuffixes(struct Node *root,char word[],int level)
{
    if(root->isEnd)
    {
        word[level]='\0';
        printf("%s\n",word);
    }

    for(int i=0;i<26;i++)
    {
        if(root->children[i]!=NULL)
        {
            word[level]=i+'a';
            displaySuffixes(root->children[i],word,level+1);
        }
    }
}

void longestRepeated(struct Node *root,char temp[],int level,char result[],int *maxLen)
{
    int childCount=0;

    for(int i=0;i<26;i++)
    {
        if(root->children[i]!=NULL)
        {
            childCount++;
            temp[level]=i+'a';

            longestRepeated(root->children[i],temp,level+1,result,maxLen);
        }
    }

    if(childCount>=2)
    {
        temp[level]='\0';

        if(level>*maxLen)
        {
            *maxLen=level;
            strcpy(result,temp);
        }
    }
}

int main()
{
    struct Node *root=createNode();

    char str[MAX];
    char pattern[MAX];
    char word[MAX];
    char temp[MAX];
    char result[MAX]="";

    int maxLen=0;
    int choice;

    printf("Enter Input String (lowercase only): ");
    scanf("%s",str);

    buildSuffixTree(root,str);

    while(1)
    {
        printf("\n===== SUFFIX TREE OPERATIONS =====\n");

        printf("1. Search Pattern\n");
        printf("2. Display All Suffixes\n");
        printf("3. Find Longest Repeated Substring\n");
        printf("4. Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                printf("Enter Pattern: ");
                scanf("%s",pattern);

                if(searchPattern(root,pattern))
                {
                    printf("Pattern Exists\n");
                }

                else
                {
                    printf("Pattern Not Found\n");
                }

                break;

            case 2:

                printf("\nAll Suffixes:\n");
                displaySuffixes(root,word,0);

                break;

            case 3:

                longestRepeated(root,temp,0,result,&maxLen);

                if(maxLen>0)
                {
                    printf("Longest Repeated Substring: %s\n",result);
                }

                else
                {
                    printf("No Repeated Substring Found\n");
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

/*
Input:
banana

Output:
Pattern Exists
Longest Repeated Substring: ana
*/