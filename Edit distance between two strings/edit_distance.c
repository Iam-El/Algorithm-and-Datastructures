// Implementation provided by Elsy Fernandes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<strings.h>

/********************************************Function:To find minimum between 3 numbers**********************************************************************************/
int findMinimum(int a, int b, int c)
{
    if (a <= b && a <= c) {
        return a;
    }
    if (b <= a && b <= c) {
        return b;
    }
    return c;
}

/*********************************************Function: To calculate edit distance*************************************************************************************************/

int editDistance(char str1[], char str2[], int length_str1, int length_str2)
{
   
    int i, j;
    int editDistance[length_str1 + 1][length_str2 + 1];


    for (i = 0; i <= length_str1; i++) {
        for (j = 0; j <= length_str2; j++) {
            if (i == 0 && j == 0) { //When i =0 and j=0
                editDistance[0][0] = 0;
            }
            
            else if(i == 0)             //When i=0
            {
                editDistance[0][j] = editDistance[i][j-1]+1;
            }
            else if (j == 0)             //When j=0
            {
                editDistance[i][0] = editDistance[i-1][j]+1;
            }
            else {
                 if (str1[i - 1] == str2[j - 1]) { //when str1[i-1]=str2[i-1]
                    
             editDistance[i][j] = findMinimum(editDistance[i - 1][j - 1], editDistance[i][j - 1] + 1, editDistance[i - 1][j] + 1); //Find minimum
                    
                }
                else {
            editDistance[i][j] = findMinimum(editDistance[i - 1][j - 1] + 1, editDistance[i][j - 1] + 1, editDistance[i - 1][j] + 1); //Find minimum
                    
                }
            }
        }
    }
    /*******************************************************PRINT THE OUTPUT IN TABLE FORM*********************************************************************************/
    printf("\n");
    int m;
    for (i = 0; i <= length_str2 + 1; i++) {
        if (i < 2) {
            printf("   |");
        }
        else {
            printf("%3c|", str2[i - 2]);
        }
    }
    printf("\n");
    for (m = 0; m < (length_str2 + 2)*4; m++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i <= length_str1; i++) {
        for (j = 0; j <= length_str2 + 1; j++) {
            if (j == 0 && i == 0) {
                printf("   |");
            }
            else if (j == 0) {
                printf("%3c|", str1[i - 1]);
            }

            else {
                printf("%3d|", editDistance[i][j - 1]);
            }
        }
        printf("\n");
        for (m = 0; m < (length_str2 + 2)*4; m++) {
            printf("-");
        }
        printf("\n");



    }

    printf("edit distance: %d", editDistance[length_str1][length_str2]);
    printf("\n");
    printf("--------------------------------------------------------------------------------------------------------");
    printf("\n\n");


}

/***************************************************MAIN FUNCTION****************************************************************************/

int main()
{
    
    char str1[100]; //Variable declaration
    char str2[100];

    printf("\n");
    printf("Enter two words separated by a space (e.g.: cat someone).Stop with: -1 -1 : ");
    printf("\n");

    while (1) {
        printf("First : ");
        scanf("%s", str1);
        printf("%s", str1);
        printf("\n");
        printf("Second :");
        scanf("%s", str2);
        printf("%s", str2);
        printf("\n");
        if ((strcmp("-1", str1)) == 0) {
            break;
        }
        if((strcmp("-1", str2)) == 0){
            break;
        }
        int length_str1 = strlen(str1);
        int length_str2 = strlen(str2);
        int value=editDistance(str1, str2, length_str1, length_str2); //Call edit distance function
    }
    return 0;

}



