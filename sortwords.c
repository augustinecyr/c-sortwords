#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define word_limit 32

// create the structure based on topic 4, create and store inside all the variables that will be used in this structure.
// reused syntax from guessword.c
typedef struct Node
{
    char word[word_limit];
    struct Node *next;
} Node;

// create node then use malloc to allocate the user input
Node *createNode(const char *word)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        exit(EXIT_FAILURE); // can use this as a exception handling
    }
    strncpy(newNode->word, word, word_limit);
    newNode->next = NULL; // next pointer is then null
    return newNode;
}
// function to insert the node to linked list.
// in general, use head as a pointer for first node.
void insertNode(Node **head, const char *word)
{
    Node *newNode = createNode(word); // creates a new node in the linked list and allocate to memory
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int compareWords(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

// check for blank user input, aka {enter} key as user input.
int isBlank(const char *str)
{
    while (*str)
    {
        if (!isspace(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

// reused syntax from guessword.c
int isValid(const char *word)
{
    for (int i = 0; word[i]; i++)
    {
        if (!(isalpha(word[i]) || word[i] == '\'' || word[i] == '-' || word[i] == '/')) // all these are the allowed conditions.
        {
            return 0;
        }
    }
    return 1;
}

void sortList(Node **head)
{
    // Count the number of nodes in the linked list
    int size = 0;
    Node *temp = *head;
    while (temp != NULL)
    {
        size++;
        temp = temp->next;
    }

    // Allocate memory for an array of strings to store words from nodes
    char **words = (char **)malloc(size * sizeof(char *));
    if (words == NULL)
    {
        exit(EXIT_FAILURE); // Exit the program if malloc fails
    }

    // check the linked list and copy words to the array
    temp = *head;
    for (int i = 0; i < size; ++i)
    {
        words[i] = strdup(temp->word); // Duplicate the word and store it in the array
        tolower(words[i]);             // Convert the copied word to lowercase
        temp = temp->next;             // Move to the next node in the linked list
    }

    // Use quicksort to sort the array of strings.
    qsort(words, size, sizeof(char *), compareWords);

    // Copy the sorted words back to the linked list nodes
    temp = *head;
    for (int i = 0; i < size; ++i)
    {
        strncpy(temp->word, words[i], word_limit); // Copy the sorted word back to the node
        temp = temp->next;                         // Move to the next node in the linked list
        free(words[i]);                            // Free the duplicated word in the array
    }

    // Step 6: Free the memory allocated for the array of strings
    free(words);
}

// print the sorted list.
void printList(Node *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->word);
        head = head->next;
    }
}

int main()
{
    Node *head = NULL; // instantiate as null first.
    char input[word_limit];

    while (1)
    {
        printf("Please enter a word:\n");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (isBlank(input))
        {
            printf("No input detected.\n"); // test case 10 is still failing, no idea why
            continue;
        }
        // conclude the game when user gives "***"
        if (strcmp(input, "***") == 0)
        {
            break; // once break, should sort the list and print the list.
        }

        if (!isValid(input))
        {
            printf("The word contains invalid characters.\n");
            continue;
        }
        // since it's only one user input to consider, just used the standard tolower function in main() instead.
        for (int i = 0; input[i]; i++)
        {
            input[i] = tolower(input[i]);
        }

        insertNode(&head, input); // use the insertnode function to add to the linkedlist.
    }

    sortList(&head); // sort the list
    printf("All the entered words in order:\n");
    printList(head);

    while (head != NULL) // as long as there is nodes
    {
        Node *temp = head; // temp is temporary pointer
        head = head->next;
        free(temp); // deallocate the memory.
    }

    return 0;
}
