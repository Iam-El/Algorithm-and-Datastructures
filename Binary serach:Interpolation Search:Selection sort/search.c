/****************************************INSTRUCTIONS************************************************************/
/* Compiling instructions:
 * 
 * connect to omega server with putty by providing host name and username
 * 
 * copy search.c to omega server and execute the following command in SSH to compile
 * 
 * gcc -o search search.c
 * 
 * run the search.c by following command
 * 
 * ./search
 *
 * 
 */

// Created by :Elsy Fernandes
/**************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

/*********************************PROGRAM FUNCTIONALITY********************************************************/
/*
1. Code provides 3 options for the user to enter 0-exit ,1-to create and save random data for search,2-load the data ,sort and run searches
2. When user selects 0 code terminates.
3. When user enters 1 he is asked to enter numbers of elements , elements to be searched within a particular range and a filename.
4. Code generates random numbers for N and S
5. Codes reads and stores the data 
6. Runs selection sort on N and prints the sorted array
7. Runs the binary and interpolation search on S values
8. Compare the results of binary and interpolation search
 */
/***************************************************************************************************************/

/***********************************STRUCTURE DEFINITION********************************************************/

struct binresult
{
    int bin_index;
    int bin_iterations;

};

struct interresult
{
    int inter_index;
    int inter_iterations;

};

struct searchResults
{
    int index;
    int value;
    int interpolationIndex;
    int binaryIndex;
    int interpolationIteration;
    int binaryInteration;

};

/*****************************************************************************************************************/

/**************************************FUNCTION DECLARATION*******************************************************/

void selection(int A[], int M);
void printArray(int arr[], int size);
struct binresult binarysearch(int A[], int N, int v);
struct interresult interpolatedsearch(int A[], int N, int v);

/****************************************************************************************************************/

int main(void)
{
/****************************************VARIABLE DECLARATION****************************************************/


    int N; //To store the number of elements                    
    int S; //To store elements to be searched
    int start_value; //Start value of the range 
    int end_value; //End value of the range
    int temp; //temporary variable to store random numbers generated for N and S values
    int i, j, k, l; //Index used in For loop
    int x; //Element to be searched in binary search    
    int y; //Element to be searched in interpolation search
    char filename[100]; //Name of the file where data will be saved
    int exitflag = 1; //Used for While loop
    int choice; //To store the user entered choice
    FILE *fptr; //Declare pointer of a type file
/***************************************************************************************************************/



    while (exitflag) {

  /****************************************CHOICE ENTERED BY THE USER************************************/


        printf("Choose from the menu option below\n");
        printf("0-exit\n");
        printf("1-create and save random data for search.\n");
        printf("2-load data from file,sort array and run searches.\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice);

        switch (choice) {

  /*****************************************WHEN USER SELECTS CHOICE '0'********************************************/
        case 0:
        {
            printf("See You In Class");
            exit(1);
            break;
        }

  /****************************************CASE 1: CREATE AND SAVE RANDOM DATA FOR SEARCHES***************************/

        case 1:
        {

  /***************************************READ DATA FROM CONSOLE STORE IT IN A VARIABLE********************************/
            printf("Enter N S start_value end_value filename : ");
            scanf("%d", &N);
            scanf("%d", &S);
            scanf("%d", &start_value);
            scanf("%d", &end_value);
            scanf("%s", filename);

   /*******************************************SETTING BOUNDARY LIMIT FOR START_VALUE AND END_VALUE(start_value should be less than end_value)***********************/
            while (start_value > end_value) {

                printf("Enter N S start_value end_value filename : ");
                scanf("%d", &N);
                scanf("%d", &S);
                scanf("%d", &start_value);
                scanf("%d", &end_value);
                scanf("%s", filename);

            }

   /**************************************************STORE THE VALUES ENTERED BY THE USER INTO A FILE**********************************************************************************/



            fptr = fopen(filename, "w");
            fprintf(fptr, "%d %d %d %d\n", N, S, start_value, end_value);
            fclose(fptr);

   /**************************************************GENERATE RANDOM NUMBERS FOR N AND STORE IT IN A FILE**********************************************************************/


            int arrayOfrandomNumbers[N];
            srand((unsigned int) time(NULL));
            for (i = 0; i <= N - 1; i++) {

                temp = (rand() % (end_value - start_value + 1)) + start_value;
                arrayOfrandomNumbers[i] = temp;
            }


            for (i = 0; i <= N - 1; i++) {
                fptr = fopen(filename, "a");
                fprintf(fptr, "%d ", arrayOfrandomNumbers[i]);
                fclose(fptr);
            }
            fptr = fopen(filename, "a");
            fprintf(fptr, "\n");
            fclose(fptr);

    /******************************************************GENERATE RANDOM NUMBERS FOR S AND STORE IT IN A FILE****************************************************************/

            int arrayOfNumbersToSearch[S];
            srand((unsigned int) time(NULL));
            for (j = 0; j <= S - 1; j++) {
                temp = (rand() % (end_value - start_value + 1)) + start_value;
                arrayOfNumbersToSearch[j] = temp;
            }


            for (i = 0; i <= S - 1; i++) {
                fptr = fopen(filename, "a");
                fprintf(fptr, "%d ", arrayOfNumbersToSearch[i]);
                fclose(fptr);
            }
            break;
        }

    /*******************************************************END OF CASE 1*******************************************************************************************************/


    /*****************************************************CASE 2 :LOAD DATA FROM FILE,SORT ARRAY AND RUN SEARCHES***************************************************************/


        case 2:
        {

            FILE *fptrToOpen; //Declare pointer of a type file
            int verboseFlag; // Used for while loop
            int option; // To store user entered option for verbose and non verbose output
            float a, b; //To store the averages of loop iterations
            float binarySum = 0.0, interpolationSum = 0.0; //To store the sum of loop iterations


   /*******************************************************USER SELECTS THE FILENAME TO READ AND OPTION 1 OR 2 FOR VERBOSE AND NON-VERBOSE****************************************/



            printf("Enter: filename, mode(1-verbose, 2-not verbose:");
            scanf("%s", filename);
            scanf("%d", &option);
            verboseFlag = (option == 1 || option == 2);
            
            while (!verboseFlag) {
                printf("\nEnter the format for the output(1- for verbose , 2- for non-verbose):");
                scanf("%d", &option);
                verboseFlag = (option == 1 || option == 2);
            }

    /****************************************************WHEN USER ENTERS WRONG FILENAME*******************************************************************************************/

            fptrToOpen = fopen(filename, "r");
            if (fptrToOpen == NULL) {
                printf("\n ERROR:File could not be opened \n\n");
                break;
            }
    /**************************************************READ AND STORE DATA FROM A FILE AND STORE IT IN AN ARRAY*********************************************************************/
            fscanf(fptrToOpen, "%d", &N);
            fscanf(fptrToOpen, "%d", &S);
            fscanf(fptrToOpen, "%d", &start_value);
            fscanf(fptrToOpen, "%d", &end_value);

            int randomNumberArrayFromFile[N], searchNumbersArrayFromFile[S];

            struct searchResults sr[S];
            for (i = 0; i < N; i++) {
                fscanf(fptrToOpen, "%d", &temp);
                randomNumberArrayFromFile[i] = temp;
            }
            for (j = 0; j < S; j++) {
                fscanf(fptrToOpen, "%d", &temp);
                searchNumbersArrayFromFile[j] = temp;
            }

    /*************************************************FUNCTION CALL :SELECTION SORT,PRINT ARRAY,BINARY SEARCH AND INTERPOLATION SEARCH************************************************/
            selection(randomNumberArrayFromFile, N);
            printf("\nSorted array: ");
            printArray(randomNumberArrayFromFile, N);
            //            //call binary search
            for (k = 0; k < S; k++) {
                x = searchNumbersArrayFromFile[k];
                struct binresult binresultValue = binarysearch(randomNumberArrayFromFile, N, x);
                struct interresult interresultValue = interpolatedsearch(randomNumberArrayFromFile, N, x);
                sr[k].index = k;
                sr[k].value = searchNumbersArrayFromFile[k];
                sr[k].interpolationIndex = interresultValue.inter_index;
                sr[k].binaryIndex = binresultValue.bin_index;
                sr[k].interpolationIteration = interresultValue.inter_iterations;
                sr[k].binaryInteration = binresultValue.bin_iterations;
                binarySum = binarySum + sr[k].binaryInteration;
                interpolationSum = interpolationSum + sr[k].interpolationIteration;
            }

    /***************************************************PERFORM AVERAGES OF NUMBER OF ITERATIONS OF BINARY AND INTERPOLATION SEARCH******************************************************************/
            a = binarySum / S;
            b = interpolationSum / S;

    /****************************************************PRINT RESULT FOR VERBOSE OUTPUT WITH FORMATTED TABLE****************************************************************************************/


            if (option == 1) {

                printf("\n|        |        | found at index  |    repetitions  |\n");
                printf("|       i|   value|  interp|  binary|  interp|  binary|\n");
                for (l = 0; l < S; l++) {
                    printf("|%8d|%8d|%8d|%8d|%8d|%8d|\n", sr[l].index, sr[l].value,
                           sr[l].interpolationIndex, sr[l].binaryIndex,
                           sr[l].interpolationIteration, sr[l].binaryInteration);
                }
                printf("|     avg|        |        |        |%8.2f|%8.2f|\n", b, a);

            }
    /****************************************************PRINT RESULT FOR NON-VERBOSE OUTPUT WITH FORMATTED TABLE*********************************************************************************/
            else {
                printf("\n|        |        | found at index  |    repetitions  |\n");
                printf("|       i|   value|  interp|  binary|  interp|  binary|\n");
                printf("|     avg|        |        |        |%8.2f|%8.2f|\n", b, a);
            }

            break;
        }
        }
    }
}

/**************************************************************END OF CASE 2********************************************************************************************/

/**************************************************************FUNCTION:SELECTION SORT**********************************************************************************/
void selection(int A[], int M)
{
    int i, j, temp;
    for (j = 0; j < M; j++) {
        int min_idx = j;
        for (i = j + 1; i < M; i++)
            if (A[i] < A[min_idx])
                min_idx = i;
        temp = A[min_idx];
        A[min_idx] = A[j];
        A[j] = temp;
    }
}

/***************************************************************FUNCTION:TO PRINT SORTED ARRAY************************************************************************************/

void printArray(int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/***************************************************************BINARY SEARCH***********************************************************************************/
struct binresult binarysearch(int A[], int N, int v)
{
    struct binresult r;
    int left, right, count = 0;

    left = 0;
    right = N - 1;
    while (left <= right) {
        int m = (left + right) / 2;
        count++;
        if (v == A[m]) {
            r.bin_index = m;
            r.bin_iterations = count;
            return r;
        }
        if (v < A[m])
            right = m - 1;
        else
            left = m + 1;

    }
    r.bin_index = -1;
    r.bin_iterations = count;

    return r;
}

/******************************************************************INTERPOLATION SEARCH**********************************************************************************/

struct interresult interpolatedsearch(int A[], int N, int v)
{
    struct interresult interPolatedSearchResult;
    int left, right, count = 0;
    left = 0;
    right = N - 1;
    while (left <= right && v >= A[left] && v <= A[right]) {
        int m = left + ((v - A[left])*(right - left) / (A[right] - A[left]));
        count++;
        if (v == A[m]) {
            interPolatedSearchResult.inter_index = m;
            interPolatedSearchResult.inter_iterations = count;
            return interPolatedSearchResult;

        }
        if (v < A[m])
            right = m - 1;
        else
            left = m + 1;
    }

    interPolatedSearchResult.inter_index = -1;
    interPolatedSearchResult.inter_iterations = count;
    return interPolatedSearchResult;
}
