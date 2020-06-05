/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 * 
 */
// Modified and added functions by Elsy Fernandes

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

struct node_struct
{
    Item item;
    link next;
};

struct list_struct
{
    link first;
    int length;
};

/* Builds and returns a list with integers read from standard input.
 * Note that it assumes the Item is int.
 * Notice that all the list access is done through it's interface (functions).
 */
list buildListOfInts()
{
    list the_list = newList();

    link current_link = NULL;
    while (1) {
        Item number;
        printf("please enter an integer: ");
        int items_read = scanf("%d", &number);
        if (items_read != 1) {
            break;
        }

        /* allocate memory for the next link */
        link next_item = newLink(number, NULL);
        insertLink(the_list, current_link, next_item);
        current_link = next_item;
    }
    return the_list;
}

list arrayToList(int arr[], int sz)
{
    int i;
    link p, new_p;
    list A = newList();

    p = newLink(arr[0], NULL);
    insertLink(A, NULL, p);

    for (i = 1; i < sz; i++) {
        new_p = newLink(arr[i], NULL);
        insertLink(A, p, new_p);
        p = new_p;
    }

    return A;
}




// ------------- link functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
link newLink(Item value, link next_in)
{
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link)
{
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link)
{
    if (the_link != NULL) {
        return the_link->item;
    }
    else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1; // NOTE: This line can be improved.
    }
}

link getLinkNext(link the_link)
{
    if (the_link != NULL) {
        return the_link->next;
    }
    else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value)
{
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next)
{
    if (the_link != NULL) {
        the_link->next = next;
    }
}

/*    --------  LIST functions    */

int listIsNULL(list the_list)
{
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }
    else {
        return 0;
    }
}

/* Creates and returns an empty list. */
list newList()
{
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list)
{
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }

        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list)
{
    if (listIsNULL(the_list) == 1) {
        return NULL;
    }

    return the_list->first;
}

int getLength(list the_list)
{
    if (listIsNULL(the_list) == 1) {
        return -1;
    }

    return the_list->length;
}

/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */
void setEmpty(list the_list)
{
    the_list->first = NULL;
    the_list->length = 0;
}

/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link)
{
    if (listIsNULL(my_list) == 1) {
        return;
    }

    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    }
    else {
        new_link->next = previous->next;
        previous->next = new_link;
    }

    my_list->length += 1;
}

/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link)
{
    setLinkNext(new_link, getFirst(my_list)); // replaces: new_link->next = my_list->first;
    my_list->first = new_link;
    my_list->length += 1;
}

/* Removes from the list and returns the link coming AFTER link x. 
 * This function DOES NOT remove link x itself. 
 */
link removeNext(list my_list, link x)
{
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    }
    else {
        temp = x->next;
        x->next = x->next->next; // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
It does not free the memory for that node. */
link removeFirst(list my_list)
{
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void printList(list my_list)
{
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}

void printListHoriz(list my_list)
{
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%5d    ", curr->item);
        i++;
    }
    printf("\n");
}

void printListHorizPointer(list my_list)
{
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\nList items:    ", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%-11d  ", curr->item);
        i++;
    }
    printf("\n");
    printf("List pointers: ");
    for (i = 0, curr = my_list->first; (curr != NULL) && (i < n); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
    printf("\n");
}

int computeLength(list my_list)
{
    if (listIsNULL(my_list) == 1) {
        return -1;
    }

    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

void setFirst(list my_list, link new_link)  // Method to set the first address to the list.
{
    my_list->first = new_link;
}

void myDestroyList(list the_list)     //Method used to delete the list when memory errors occur of some inputs
{
    if (listIsNULL(the_list) == 1) {
        return;
    }
    int listLength = getLength(the_list);
    int i;
    link current = the_list->first;
    link nextLink;
    for (i = 0; i < listLength; i++) {
        if (current == NULL) {
            i = listLength;
        }
        nextLink = getLinkNext(current);
        destroyLink(current);
        current = nextLink;
    }
    free(the_list);
    the_list = NULL;
}

/*----------------------------------------------------------------
 New functions.
 Finish their implementation below. 
 If you need to use helper functions you can define them and use them in this file.
 ***You should not change the behavior of any of the functions defined above. 
 Instead, write a new function with the behavior that you want.***
 */
// Implementations provided by Elsy Fernandes
void deleteOccurrences(list A, Item V)
{
    if (A == NULL) {                                           //Check if the list is NULL
        printf("List A is NULL\n");
        return;
    }
    int ListLength = getLength(A);
    if (ListLength == 0) {                                      //Check if the list has zero length
        printf("List A is empty \n");

    }
    else {
        int i;
        link current = getFirst(A);                               
        link previous = NULL;
        int ListLength = getLength(A);                           //Get list Length
        for (i = 0; i < ListLength; i++) {
            Item TestElement = getLinkItem(current);             //Get the First Item from the List A
            link nextLinkNew = getLinkNext(current);
            if (TestElement == V) {
                link temp;                                       // If the Item is equal to item to be searched
                if (i == 0) {
                    temp = removeFirst(A);                       //Remove the first link
                    destroyLink(temp);
                }
                else {
                    temp = removeNext(A, previous);              //else removes the next link of previous
                    destroyLink(temp);
                }
                current = nextLinkNew;
            }
            else {
                previous = current;
                current = nextLinkNew;
            }
        }
    }
    return;

}

list sublist(list A, list pos_list)
{
    if (A == NULL) {
        printf("list A is NULL\n");                              //Check if the list A is NULL
        return NULL;
    }
    int listLength = getLength(A);
    if (listLength == 0) {
        printf("List A is empty\n");                             //Check if the list A has zero length
        return NULL;
    }
    if (pos_list == NULL) {
        printf("List A is NULL \n");                             //Check if the pos_list is NULL
        return NULL;
    }

    if (pos_list->length == 0) {                                  //Check if the list pos_list has zero length
        printf("List A is empty \n");
        return NULL;
    }
    else {
        int i;
        list subList = newList();                                //Create new sublist to store the values returned from the function
        link sublistLink = NULL;
        link newLinkToAdd;
        link startLink = getFirst(A);                             //Get first link of list A
        link currentLink, nextLink;
        link previousLinkAddedToSublist;
        link currentLinkForPosList = getFirst(pos_list);           //Get first link of pos_list
        int posListLength = getLength(pos_list);                   //Get length of pos_list
        int count = 0;
        Item itemAtRequiredIndex;
        Item itemToGet = getLinkItem(currentLinkForPosList);        //Get first item of Pos_list

        currentLink = startLink;
        for (i = 0; i < posListLength; i++) {                        
            if (itemToGet > listLength) {                            //Handled for Index out of bound test case
                destroyList(subList);
                return NULL;
            }
            while (count != itemToGet) {
                nextLink = getLinkNext(currentLink);                //get the value from pos_list
                count++;
                currentLink = nextLink;
            }
            newLinkToAdd = newLink(getLinkItem(currentLink), NULL);   //if lengthof sublist ==0 Insert the value returned from the list A based on the pos_list value to the new sublist
            if (getLength(subList) == 0) {                            
                insertAtBeginning(subList, newLinkToAdd);
            }
            else {
                insertLink(subList, previousLinkAddedToSublist, newLinkToAdd); //else insert to next node
            }
            previousLinkAddedToSublist = newLinkToAdd;
            currentLinkForPosList = getLinkNext(currentLinkForPosList);
            if (currentLinkForPosList != NULL) {
                itemToGet = getLinkItem(currentLinkForPosList);               
            }
            count = 0;
            currentLink = startLink;
        }
        return subList;
    }

}

void moveAllMaxAtEnd(list A)
{
    int listLength = getLength(A);
    if (A == NULL) {                                           //Check if the list A is NULL
        printf("List A is NULL \n");
        return;
    }
    else if (listLength == 0) {
        printf("List A is empty \n");                          //Check if List length is empty
    }
    else if (listLength > 1) {
        int i, j;
        int listLength = getLength(A);
        link current = getFirst(A);                            //Get the first link of a list A
        Item testItem;
        Item newTestItem;
        int maxValue = 0;                                      //Assign maxvalue=0
        link previous = NULL;
        int countOfOccurences = 0;                             //assign countOfOccurences = 0

        for (i = 0; i < listLength; i++) {
            Item testItem = getLinkItem(current);               //For i = 0 to listlength,compare if testitem is greater than maxvalue
            if (testItem > maxValue) {
                maxValue = testItem;                           //if testitem>maxvalue then maxvalue is asigned a new value of testItem
            }
            link nextLink = getLinkNext(current);               //Do the above action for all the items 
            current = nextLink;
        }

        current = getFirst(A);
        for (i = 0; i < listLength; i++) {                      //Checks for all the iterations og listlength if testitem==maxvalue
            Item testItem = getLinkItem(current);
            if (testItem == maxValue) {
                countOfOccurences = countOfOccurences + 1;       //Increment countOfOccurences for all the items if testitem==maxvalue
            }
            link nextLink = getLinkNext(current);
            current = nextLink;
        }

        if (countOfOccurences < listLength) {                      //If countOfOccurences is less than Listlength then remove the links
            link linksRemoved[countOfOccurences];
            link nextCurrent = getFirst(A);
            int arrayPointer = 0;
            for (i = 0; i < listLength; i++) {
                Item testItem = getLinkItem(nextCurrent);           
                link nextCurrentLink = getLinkNext(nextCurrent);    //remove the max element from the list to be added at the end
                if (testItem == maxValue) {
                    if (previous == NULL) {
                        setFirst(A, nextCurrentLink);
                    }
                    else if (nextCurrentLink != NULL) {
                        setLinkNext(previous, nextCurrentLink);
                    }
                    linksRemoved[arrayPointer] = nextCurrent;
                    arrayPointer++;
                }
                previous = nextCurrent;
                nextCurrent = nextCurrentLink;
            }
            for (i = 0; i < countOfOccurences; i++) {
                link maxLink = linksRemoved[i];                       //add the removed items to the end of the list
                setLinkNext(maxLink, NULL);
                setLinkNext(previous, maxLink);
                previous = maxLink;
            }
        }
    }

}


// swaps the first and the third nodes

void swapFirstThird(list A)
{
    int listLength = getLength(A);                             //Get List length
    link previous = NULL;

    if (A == NULL) {
        printf("List A is Null \n");                           //Check if A is NULL
    }
    else if (listLength == 0) {                                //Check if list length is zero
        printf("List A is empty\n");
    }

    else if (listLength > 2) {
        link current = getFirst(A);
        link secondLink = getLinkNext(current);
        link thirdLink = getLinkNext(secondLink);
        link fourthLink = getLinkNext(thirdLink);               //If list length is greater than 2 swap first and third
        setLinkNext(current, fourthLink);
        setLinkNext(secondLink, current);
        setLinkNext(thirdLink, secondLink);
        setFirst(A, thirdLink);
    }
    else if (listLength == 2) {
        link current = getFirst(A);
        link temp = NULL;
        link secondLink = getLinkNext(current);                  //If list length is equal to 2 swap first and second
        temp = current;
        A->first = secondLink;
        link newFirst = getFirst(A);
        setLinkNext(newFirst, temp);
    }
}
//
// Set-up and call your testing functions from this function.

int run_student_tests()
{
    list A;
    list pos_list;
    list result;
    printf("\n Running function run_student_test.\n ");
    printf("\n\n--------------------------------------\n");

    /**************************************************TEST CASES FOR DELETE OCCURENCE FUNCTION*******************************************************/


    printf("\n Running TestCases For:deleteOccurrences(list A, int V)");
    printf("\n*****************************************\n");


    /*********************TestCase:1************************************************/

    A = NULL;
    printf("Test case 1: List A is NULL \n");
    deleteOccurrences(A, 20);
    destroyList(A);
    printf("\n");

    /**********************TestCase:2*********************************************/

    printf("Test case 2 : List A is empty \n");

    A = newList();
    deleteOccurrences(A, 20);
    destroyList(A);
    printf("\n");

    /*************************TestCase:3****************************************************/
    printf("Test case 3 : Normal data V is in A \n");
    int del_arr[] = {15, 100, 7, 5, 100, 7, 30};
    A = arrayToList(del_arr, 7);
    deleteOccurrences(A, 7);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:4****************************************************/
    printf("Test case 4 : V does not occur in A\n");
    int del_arr1[] = {15, 100, 7, 5};
    A = arrayToList(del_arr1, 4);
    deleteOccurrences(A, 9);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:5****************************************************/
    printf("Test case 5 :  Repeated consecutive occurrences\n");
    int del_arr2[] = {15, 7, 7, 5};
    A = arrayToList(del_arr2, 4);
    deleteOccurrences(A, 7);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:6****************************************************/
    printf("Test case 6 :  A has one item and that is V\n");
    int del_arr3[] = {7};
    A = arrayToList(del_arr3, 1);
    deleteOccurrences(A, 7);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:7****************************************************/
    printf("Test case 7 :  A has only items with Value V in it\n");
    int del_arr4[] = {7, 7, 7};
    A = arrayToList(del_arr4, 3);
    deleteOccurrences(A, 7);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n******************************************************************************\n");

    /**************************************************TEST CASES FOR SUBLIST FUNCTION*******************************************************/


    printf("\n Running TestCases For:sublist(list A, list pos_list)");
    printf("\n*****************************************\n");


    /*********************TestCase:1************************************************/

    A = NULL;
    printf("Test case 1: List A is NULL \n");
    int pos_arr[] = {6};
    pos_list = arrayToList(pos_arr, 1);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n");

    /**********************TestCase:2*********************************************/

    printf("Test case 2 : List A is empty \n");


    A = newList();
    int pos_arr1[] = {5};
    pos_list = arrayToList(pos_arr1, 1);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n");

    /*********************TestCase:3************************************************/


    printf("Test case 3: Index out of bound\n");
    int sub_arr2[] = {10, 10, 40, 20};
    int pos_arr2[] = {3, 50, 3};
    pos_list = arrayToList(pos_arr2, 3);
    A = arrayToList(sub_arr2, 4);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    myDestroyList(pos_list);
    destroyList(A);
    myDestroyList(result);
    printf("\n");

    /*********************TestCase:4************************************************/


    printf("Test case 4: A is not modified by sublist");
    int sub_arr3[] = {15, 100, 7, 5, 100};
    int pos_arr3[] = {3, 0, 2};
    pos_list = arrayToList(pos_arr3, 3);
    A = arrayToList(sub_arr3, 5);
    result = sublist(A, pos_list);
    printListHorizPointer(A);
    destroyList(pos_list);
    destroyList(A);
    destroyList(result);
    printf("\n");

    /*********************TestCase:5************************************************/


    printf("Test case 5: Normal data");
    int sub_arr4[] = {15, 100, 7, 5, 100, 7, 30};
    int pos_arr4[] = {3, 0, 6, 4};
    pos_list = arrayToList(pos_arr4, 4);
    A = arrayToList(sub_arr4, 7);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n");

    /*********************TestCase:6************************************************/


    printf("Test case 6: Repeated positions");
    int sub_arr5[] = {5};
    int pos_arr5[] = {0, 0, 0};
    pos_list = arrayToList(pos_arr5, 3);
    A = arrayToList(sub_arr5, 1);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n");


    /*********************TestCase:7***********************************************/

    pos_list = NULL;
    printf("Test case 7: List pos_list is NULL \n");
    int sub_arr6[] = {6, 7};
    A = arrayToList(sub_arr6, 2);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n");

    /**********************TestCase:8*********************************************/

    printf("Test case 8 : List pos_list is empty \n");


    pos_list = newList();
    int sub_arr7[] = {8, 9, 10};
    A = arrayToList(sub_arr7, 3);
    result = sublist(A, pos_list);
    printListHorizPointer(result);
    destroyList(A);
    destroyList(pos_list);
    destroyList(result);
    printf("\n*******************************************************************\n");



    /**************************************************TEST CASES FOR SWAP FIRST AND THIRD*******************************************************/


    printf("\n Running TestCases For:swapFirstThird(list A)");
    printf("\n*****************************************\n");

    /*********************TestCase:1************************************************/

    A = NULL;
    printf("Test case 1: List A is NULL \n");
    swapFirstThird(A);
    destroyList(A);
    printf("\n");

    /**********************TestCase:2*********************************************/

    printf("Test case 2 : List A is empty \n");

    A = newList();
    swapFirstThird(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:3****************************************************/
    printf("Test case 3 : List A has one element");
    int swap_arr[] = {15};
    A = arrayToList(swap_arr, 1);
    swapFirstThird(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");
    /*************************TestCase:4****************************************************/
    printf("Test case 4 : List A has two elements");
    int swap_arr1[] = {15, 30};
    A = arrayToList(swap_arr1, 2);
    swapFirstThird(A);
    printListHorizPointer(A);
    myDestroyList(A);
    printf("\n");
    /*************************TestCase:5****************************************************/
    printf("Test case 5 : List A has three elements");
    int swap_arr2[] = {15, 30, 20};
    A = arrayToList(swap_arr2, 3);
    swapFirstThird(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*************************TestCase:6****************************************************/
    printf("Test case 6 : List A has more than three elements");
    int swap_arr3[] = {15, 30, 20, 40, 50, 16};
    A = arrayToList(swap_arr3, 6);
    swapFirstThird(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n*******************************************************************************/");

    /**************************************************TEST CASES FOR MOVE ALL MAX TO END*******************************************************/


    printf("\n Running TestCases For:moveAllMaxAtEnd(list A)");
    printf("\n*****************************************\n");

    /*********************TestCase:1************************************************/

    A = NULL;
    printf("Test case 1: List A is NULL \n");
    moveAllMaxAtEnd(A);
    destroyList(A);
    printf("\n");

    /**********************TestCase:2*********************************************/

    printf("Test case 2 : List A is empty \n");

    A = newList();
    moveAllMaxAtEnd(A);
    destroyList(A);
    printf("\n");

    /*********************TestCase:3************************************************/


    printf("Test case 3: Normal data \n");
    int max_arr1[] = {15, 100, 5, 100, 30};
    A = arrayToList(max_arr1, 5);
    moveAllMaxAtEnd(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*********************TestCase:4************************************************/


    printf("Test case 4: A has one item\n");
    int max_arr2[] = {7};
    A = arrayToList(max_arr2, 1);
    moveAllMaxAtEnd(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");


    /*********************TestCase:5************************************************/


    printf("Test case 5: A has only one item of same value in it\n");
    int max_arr3[] = {7, 7, 7};
    A = arrayToList(max_arr3, 3);
    moveAllMaxAtEnd(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*********************TestCase:6************************************************/


    printf("Test case 6: Max is on the first position\n");
    int max_arr4[] = {100, 7, 20};
    A = arrayToList(max_arr4, 3);
    moveAllMaxAtEnd(A);
    printListHorizPointer(A);
    destroyList(A);
    printf("\n");

    /*********************TestCase:7************************************************/


    printf("Test case 7: Max is on the last position\n");
    int max_arr5[] = {10, 7, 200};
    A = arrayToList(max_arr5, 3);
    moveAllMaxAtEnd(A);
    printListHorizPointer(A);
    myDestroyList(A);
    printf("\n************************************************************************\n");
}
