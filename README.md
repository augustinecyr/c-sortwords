## Sorted Word Entry and Display

This C program allows users to enter words, stores them in a linked list, sorts the list alphabetically, and displays the sorted words.

### Program Overview:

#### Structures:
- `Node`: Represents a node in a linked list.
  - `word`: Stores the entered word.
  - `next`: Points to the next node in the linked list.

#### Functions:

- `Node *createNode(const char *word)`: Creates a new node with the provided word.
- `void insertNode(Node **head, const char *word)`: Inserts a new node into the linked list.
- `int compareWords(const void *a, const void *b)`: Compares two words for sorting purposes.
- `int isBlank(const char *str)`: Checks if the input is blank.
- `int isValid(const char *word)`: Validates if the word contains valid characters.
- `void sortList(Node **head)`: Sorts the linked list of words alphabetically.
- `void printList(Node *head)`: Prints the sorted list of words.

#### Main Function:

- **Input**:
  - Users can enter words until they input "***" to signify the end of word entry.

- **Functionality**:
  - Validates and stores entered words into a linked list.
  - Sorts the linked list alphabetically.
  - Displays the sorted list of words.

### Notes:

- Words are stored in a linked list and sorted using quicksort.
- Input validation checks for valid characters in the words.
- The program handles blank input and provides appropriate messages.

### Example Output:

```
Please enter a word:
[User enters a word]

Please enter a word:
[User enters another word]

Please enter a word:
***

All the entered words in order:
[Sorted list of entered words is displayed]
```
