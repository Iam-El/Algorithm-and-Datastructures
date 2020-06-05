// Implementation provided by Elsy Fernandes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/******************************************Structure definition**************************************************************/
struct item
{
    char englishWord[100];
    char spanishWord[1000];
};

/****************************************Function: Quadratic Probing*********************************************************/
int QuadraticProbing(int hashKey, int i, int M)
{
    return (hashKey + (3 * i)+(5 * i * i)) % M;
}

/****************************************Function:Calculate hash value******************************************************/
int hash(char *v, int M)
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a * h + *v) % M;
    return h;
}

/***************************************Structure(Copy english word to hash table)********************************************/

struct item copyStructItem(struct item source, struct item destination)
{
    strncpy(destination.englishWord, source.englishWord, strlen(source.englishWord));
    strncpy(destination.spanishWord, source.spanishWord, strlen(source.spanishWord));
    return destination;
}

/***************************************Structure(Append spanish word)**********************************************************/
struct item appendSpanishWord(struct item source, struct item destination)
{
    strncat(destination.spanishWord, ";", 1);
    strncat(destination.spanishWord, source.spanishWord, strlen(source.spanishWord));
    return destination;
}

/***************************************unction:To print message************************************************************************************/
void printInsertMessage(struct item source)
{
    printf("\tWill insert pair [%s,%s]\n", source.englishWord, source.spanishWord);
}

/*********************Function:To check if the position in the table is empty*******************************************************************/
bool isPositionEmpty(struct item destination)
{
    int test = strcmp(destination.englishWord, " ");
    int test1 = strcmp(destination.englishWord, "DELETED");
    return (test == 0) && (test1 != 0);
}

/***************************************Function:Check if word is deleted************************************************************************************/
bool isWordDeleted(struct item destination)
{
    int test = strcmp(destination.englishWord, "DELETED");
    return (test == 0);
}

/***************************************Function:To check if new word is present************************************************************************************/
bool isNewWordAlreadyPresent(struct item destination, struct item source)
{
    int test = (strcmp(destination.englishWord, source.englishWord));
    int test1 = strcmp(destination.englishWord, "DELETED");
    return (test == 0) && (test1 != 0);
}

/***************************************Function:check if word is present************************************************************************************/
bool isSearchWordPresent(struct item destination, char* source)
{
    int test = (strcmp(destination.englishWord, source));
    int test1 = strcmp(destination.englishWord, "DELETED");
    return (test == 0)&& (test1 != 0);
}

/***************************************Function:Calculate hash table result************************************************************************************/
void calculateAndPrintHashTableResults(int keyCount[])
{
    int i;
    float totalProbesDictionary = 0;
    float totalKeysDictionary = 0;
    int maxProbes = 0;
    for (i = 1; i <= 100; i++) {
        totalProbesDictionary = totalProbesDictionary + (i * keyCount[i]);
        totalKeysDictionary = totalKeysDictionary + keyCount[i];
        if (keyCount[i] != 0) {
            maxProbes = i;
        }
    }
    //***************************************Print hash table************************************************************************/
    printf("\n\n");
    printf("Hash Table\n");
    printf("\taverage number of probes:\t\t %.2f\n", (totalProbesDictionary / totalKeysDictionary));
    printf("\tmax_run of probes:\t\t\t %d\n", maxProbes);
    printf("\ttotal PROBES (for %f items):\t%.2f\n", totalKeysDictionary, totalProbesDictionary);
    printf("\titems NOT hashed (out of %f):\t 0\n", totalKeysDictionary);

}

//***************************************Function: Print dictionary**************************************************************/

void printDictionary(struct item dictionary[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        printf("%s-%s\n", dictionary[i].englishWord, dictionary[i].spanishWord);
    }
}

void printDataItem(struct item a)
{
    printf("%s-%s", a.englishWord, a.spanishWord);
}

/*****************************************Function:To split english and spanish word********************************************/

struct item splitWord(char str[], int lengthstr)
{
    struct item dictionaryitems;
    int x, y;
    int i = 0;
    while (str[i] != '\t') {
        i++;
    }
    x = i;
    y = i + 1;


    for (i = 0; i < x; i++) {
        dictionaryitems.englishWord[i] = str[i];
    }
    dictionaryitems.englishWord[i] = '\0';
    for (i = 0; i < (lengthstr - 1 - y); i++) {
        dictionaryitems.spanishWord[i] = str[y + i];
    }
    dictionaryitems.spanishWord[i] = '\0';

    return dictionaryitems;
}

//***************************************Function: To search english word**************************************************************/

int search(char english[], struct item dictionary[], int size)
{
    int probes = 1;
    int key = hash(english, size);
    bool wordFound = false;
    bool repeat = true;
    if (isSearchWordPresent(dictionary[key], english)) {
        printf("\t%d probes\n", probes);
        printf("\tTranslation: %s\n", dictionary[key].spanishWord);
        wordFound = true;
    }
    else if (isWordDeleted(dictionary[key])) {
        int i = 0;
        while (repeat) {
            probes = probes + 1;
            int quadraticKey = QuadraticProbing(key, i, size);
            if (isSearchWordPresent(dictionary[quadraticKey], english)) {
                printf("\t%d probes\n", probes);
                printf("\tTranslation: %s\n", dictionary[quadraticKey].spanishWord);
                wordFound = true;
                repeat = false;
                break;
            }
            else if (!isWordDeleted(dictionary[quadraticKey])) {
                repeat = false;
                break;
            }
            else {
                i++;
            }
        }
    }
    else {
        int i = 0;
        while (i < size) {
            probes = probes + 1;
            int quadraticKey = QuadraticProbing(key, i, size);
            if (isSearchWordPresent(dictionary[quadraticKey], english)) {
                printf("\t%d probes\n", probes);
                printf("\tTranslation: %s\n", dictionary[quadraticKey].spanishWord);
                i = size;
                wordFound = true;
                break;
            }
            else {
                i++;
            }
        }
    }
    if (!wordFound) {
        printf("\t%d probes\n", probes);
        printf("\tNOT found\n");
    }
    return probes;

}
//***************************************Function:To insert a english word and its translations**********************************/

struct item* insert(struct item dictionary[], struct item data, int size, bool addToProbes, int *keyCount, int *insertProbes)
{
    int probes = 1;

    int key = hash(data.englishWord, size);

    if (isPositionEmpty(dictionary[key])) {
        dictionary[key] = copyStructItem(data, dictionary[key]);
    }
    else if (isNewWordAlreadyPresent(dictionary[key], data)) {
        dictionary[key] = appendSpanishWord(data, dictionary[key]);
    }
    else {
        int i = 0;
        while (i < size) {
            probes = probes + 1;
            int quadraticKey = QuadraticProbing(key, i, size);
            if (isPositionEmpty(dictionary[quadraticKey])) {
                dictionary[quadraticKey] = copyStructItem(data, dictionary[quadraticKey]);
                break;
            }
            if (isNewWordAlreadyPresent(dictionary[quadraticKey], data)) {
                dictionary[quadraticKey] = appendSpanishWord(data, dictionary[quadraticKey]);
                break;
            }
            else {
                i++;
            }
        }
    }

    if (addToProbes) {
        *insertProbes = *insertProbes + probes;
        printf("\t%d probes\n", probes);
    }
    else {
        keyCount[probes]++;
    }

    return dictionary;
}

//***************************************Function:To delete key value pair**************************************************************/

int delete(char english[], struct item dictionary[], int size)
{

    int probes = 1;
    int key = hash(english, size);
    bool wordFound = false;
    bool repeat = true;
    if (isSearchWordPresent(dictionary[key], english)) {
        strncpy(dictionary[key].englishWord, "DELETED", 100);
        strncpy(dictionary[key].spanishWord, "DELETED", 1000);
        printf("\t%d probes\n", probes);
        printf("\tItem was deleted\n");
        wordFound = true;
    }
    else if (isWordDeleted(dictionary[key])) {
        int i = 0;
        while (repeat) {
            probes = probes + 1;
            int quadraticKey = QuadraticProbing(key, i, size);
            if (isSearchWordPresent(dictionary[quadraticKey], english)) {
                strncpy(dictionary[quadraticKey].englishWord, "DELETED", 100);
                strncpy(dictionary[quadraticKey].spanishWord, "DELETED", 1000);
                wordFound = true;
                repeat = false;
                break;
            }
            else if (!isWordDeleted(dictionary[quadraticKey])) {
                repeat = false;
                break;
            }
            else {
                i++;
            }
        }
    }
    else {
        int i = 0;
        while (i < size) {
            probes = probes + 1;
            int quadraticKey = QuadraticProbing(key, i, size);
            if (isSearchWordPresent(dictionary[quadraticKey], english)) {
                strncpy(dictionary[quadraticKey].englishWord, "DELETED", 100);
                strncpy(dictionary[quadraticKey].spanishWord, "DELETED", 1000);
                printf("\t%d probes\n", probes);
                printf("\tItem was deleted\n");
                wordFound = true;
                i = size;
            }
            else {
                i++;
            }
        }
    }

    if (!wordFound) {
        printf("\t%d probes\n", probes);
        printf("\tItem not found => no deletion.\n");
    }

    return probes;
}

int main()
{
    char filename[100];
    FILE *test;
    char choice[50];
    char str[500];
    char c;
    int size = 20123;
    int count = 0;
    char file[100];
    char english[100];
    char spanish[100];
    char result[1000];
    struct item temp;
    int keyCount[101] = {0};

    int totalProbes = 0;
    int totalOperations = 0;
    int probes = 1;
    int i;
    int key;

    //****************************************Create a empty hash table***********************************************************************************/

    struct item *dictionary = (struct item*) malloc(size * sizeof (struct item));

    for (i = 0; i < size; i++) {
        strncpy(dictionary[i].englishWord, " ", 100);
        strncpy(dictionary[i].spanishWord, " ", 1000);
    }

    printf("Enter the filename with the dictionary data (include the extension e.g. Spanish.txt):");
    scanf("%s", &filename);
    test = fopen(filename, "r");
    for (c = getc(test); c != EOF; c = getc(test)) {
        if (c == '\n') { // Increment count if this character is newline 
            count = count + 1;
        }
    }

    i = 1;
    fclose(test);
    int j = 1;
    test = fopen(filename, "r");
    while (j <= count) {
        fgets(str, 250, test);
        int lengthstr = strlen(str);
        temp = splitWord(str, lengthstr);
        dictionary = insert(dictionary, temp, size, false, &keyCount[0], &totalProbes);
        j++;
    }
    fclose(test);

    /****************************************Print hash table results*************************************************************/
    calculateAndPrintHashTableResults(keyCount);

    /*****************************************Print the table with count of keys**************************************************/
    printf("\n\n");
    printf("Probes|Count of keys\n");
    printf("-------------\n");
    for (i = 1; i <= 100; i++) {
        printf("%6d|%6d\n", i, keyCount[i]);
        printf("-------------\n");
    }
    printf("\n");
    printf("Enter words to look-up. Enter -1 to stop.");
    printf("\n");
    /******************************************Perform read operations*************************************************************/
    while (1) {
        totalOperations = totalOperations + 1;
        printf("READ op:");
        scanf("%s", &choice);
        printf("%s", choice);
        if (strcasecmp(choice, "-1") == 0) {
            return 0;
        }

        int value2 = strcmp(choice, "q");
        if (value2 == 0) {
            printf("\n\n\n");
            printf("Average probes per operation: %f", (float) totalProbes / (float) totalOperations);
            printf("\n\n\n");
            free(dictionary);
            exit(0);
        }

        int value = strcmp(choice, "s");
        if (value == 0) {
            printf(" query:");
            scanf("%s", &english);
            printf("%s", english);
            printf("\n");
            probes = search(english, dictionary, size);
            totalProbes = totalProbes + probes;
        }
        int value1 = strcmp(choice, "d");
        if (value1 == 0) {
            printf(" query:");
            scanf("%s", &english);
            printf("%s", english);
            printf("\n");
            probes = delete(english, dictionary, size);
            totalProbes = totalProbes + probes;
        }
        int value3 = strcmp(choice, "i");

        if (value3 == 0) {
            printf(" query:");
            scanf("%s", temp.englishWord);
            printf("%s", temp.englishWord);
            scanf("%s", temp.spanishWord);
            printf("\n");
            insert(dictionary, temp, size, true, &keyCount[0], &totalProbes);
            printInsertMessage(temp);
        }
    }
}
