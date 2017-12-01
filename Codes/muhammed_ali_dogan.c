// Muhammed Ali Doğan
// 150115035
// Project#1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

typedef struct WordList{
    char word[60];
	struct WordList *next;
}WordList;

WordList *header; FILE *file; int number = 0;

WordList * similarity(WordList ** text_1, WordList ** text_2);
WordList * read(WordList ** header, char fileName[60]);
WordList * insert(WordList ** header, char word[60]);
WordList * two_grams(WordList ** text);
WordList * allocate();

void sortedInsert(WordList** header, WordList* new_node);
void print_TermFrequency(WordList ** header, int number);
void print_TwoGrams(WordList ** header, int number);
void swap(WordList *a, WordList *b);
void sort(WordList ** header);

int isExist(WordList ** text, char word[60]);
int print(WordList ** header);
int format(char word[60]);
int counter(int input);

int main()
{	
	//Read texts lists
	WordList *text_1 = read(&header, "file1.txt");
	WordList *text_2 = read(&header, "file2.txt");
	//Merge as word-pairs lists
	WordList *two_grams_text_1 = two_grams(&text_1);
	WordList *two_grams_text_2 = two_grams(&text_2);
	//Find similarity as Term Frequency
	WordList *TF = similarity(&text_1, &text_2);
	print_TermFrequency(&TF, number); 
	//Find similarity as 2-grams
	WordList *TG = similarity(&two_grams_text_1, &two_grams_text_2);
	print_TwoGrams(&TG, (number-1));
	
	return 0;
}
//Standard insert function
WordList * insert(WordList ** header, char word[60])
{
    WordList *current, *interim, *temporary;
	
	//Create node to insert and assign values to its fields
    current = (WordList *)malloc(sizeof(WordList));
    strcpy(current->word, word);
	current->next = NULL;
	
    //If first node is null
    if(*header == NULL){
        *header = current;
    }
	//If list is not empty
	else
	{	
		interim = *header;
		while (interim->next != NULL) 
		{
			interim = interim->next;
		};
		interim->next = current;
	}
	return current;
}
//Standard bubble sort
void sort(WordList ** header)
{
    // Initialize sorted linked list
    WordList *sorted = NULL;
 
    // Traverse the given linked list and insert every
    // node to sorted
    WordList *current = *header;
    while (current != NULL)
    {
        // Store next for next iteration
        WordList *next = current->next;
 
        // insert current in sorted linked list
        sortedInsert(&sorted, current);
 
        // Update current
        current = next;
    }
 
    // Update header to point to sorted linked list
    *header = sorted;
}
//The function that insert a linked list node in sorted index
void sortedInsert(WordList** header, WordList* new_node)
{
    WordList* current;
    /* Special case for the head end */
    if (*header == NULL || strcmp((*header)->word, new_node->word) >= 0)
    {
        new_node->next = *header;
        *header = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *header;
        while (current->next!=NULL && strcmp(current->next->word, new_node->word) < 0)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
//The function that finds similarity according to Term Frequency
WordList * similarity(WordList ** text_1, WordList ** text_2)
{	
	number = 0;
	WordList *interim_1 = *text_1; WordList *interim_2 = *text_2; WordList *result = NULL;
	while(interim_1 != NULL)
	{
		if((isExist(&interim_2, interim_1->word)) == 1)
		{
			if( (isExist(&result, interim_1->word)) == 0 ){
				insert(&result, interim_1->word);
				number++;
			}
		}
		interim_1 = interim_1->next;
	}
	return result;
}
//The function that prints term frequency similarity
void print_TermFrequency(WordList ** header, int number)
{	
	sort(header);
	printf("\n---------------------------------\n");
	printf("---------Term Frequency----------\n\n");
	printf("The number of common words: %d\n", number);
	printf("The common words are: \n\n");
	print(header);
}
//The function that prints 2-grams similarity
void print_TwoGrams(WordList ** header, int number)
{	
	sort(header);
	printf("\n---------------------------------\n");
	printf("----------- 2 - Grams -----------\n\n");
	printf("The number of common word-pairs: %d\n", number);
	printf("The common word-pairs are: \n\n");
	print(header);
	printf("\n---------------------------------\n");
}
//The function that makes word list as a word-pair list
WordList * two_grams(WordList ** text)
{
	WordList *interim = *text;
	char two_grams_word[60];
	WordList *current = allocate();
	
	while(interim->next != NULL)
	{
		strcpy(two_grams_word, interim->word);
		strcat(two_grams_word, " ");
		strcat(two_grams_word, interim->next->word);
		insert(&current, two_grams_word);
		interim = interim->next;
	}
	return current;
}
//The function that read file word by word
WordList * read(WordList **header, char fileName[60])
{
    WordList *temp = *header; char word[60];
    // Open file, read word by word, then send to insert function
    file = fopen(fileName, "r");
    while (!feof(file))
    {
        fscanf(file, "%s", word);
		format(word);
        insert(&temp, word);
    }
    fclose(file);
	return temp;
}
//Print out all elements in the linked list
int print(WordList ** header)
{	
	WordList *interim = *header; char word[32];
	while(interim != NULL)
    {	
		printf("%s\n", interim->word);
		interim = interim->next;
    }
	return 0;
}
//The function that finds whether given eleme nt exists in list or not.
int isExist(WordList ** text, char word[60])
{
	WordList *interim = *text; int arbiter = 0;
	while(interim != NULL)
	{
		if(strcmp(interim->word, word) == 0)
		{
			arbiter = 1;
		}
		interim = interim->next;
	}
	return arbiter;
}
//The function that swaps data of two nodes a and b
void swap(WordList *a, WordList *b)
{
    char temporary[60];
	strcpy(temporary, b->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temporary);
}
//The function that allocates memory space for a single node
WordList * allocate()
{
    WordList *current = (WordList *)malloc(sizeof(WordList));
	current->next = NULL;
	return current;
}
//The function that deletes symbols and spaces.
int format(char word[60])
{
	int i, j;
	for(i = 0; word[i]; i++)
	{
		while (!( (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '\0') )
        {
            for(j = i; word[j] != '\0'; ++j)
            {
                word[j] = word[j+1];
            }
            word[j] = '\0';
        }
		word[i] = tolower(word[i]);
	}
}
