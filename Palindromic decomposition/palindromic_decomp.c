// Implementation provided by Elsy Fernandes

#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <stdlib.h> 
#include <string.h>
#include<strings.h>

/****************************Substring Function declaration****************************************************/
 char * substring(char s[], int p, int l);

/*****************************Function:To test elements in increasing order or not****************************/
int increasing(int * A, int N) {

  
  if (N <= 1)
    return 1;

  else if (A[N - 1] >= A[N - 2]) {
    return increasing(A, N - 1);

  }
  return 0;
}

/*****************************Function min_rec_1:To find minimum in an array**********************************/

int min_rec_1(int * A, int N, int * rec_ct, int * base_ct,int *max_depth) {
    *max_depth=*max_depth+1;
  if (N == 1) //base case
  {
    * base_ct = * base_ct + 1;
    return A[0];

  }
  * rec_ct = * rec_ct + 1;
  int temp = min_rec_1(A, N - 1, & ( * rec_ct), & ( * base_ct),&(*max_depth));
  if (temp < A[N - 1])
    return temp;
  else
    return A[N - 1];
}

/*****************************Function min_rec_2:To find minimum in an array**********************************/

int min_rec_2(int * A, int N, int * rec_ct, int * base_ct, int *max_depth) {
   
 
  if (N == 1) //base case
  {
     * base_ct = * base_ct + 1;
    return A[0];
  }
  
  if (min_rec_2(A, N - 1, & ( * rec_ct), & ( * base_ct), & ( *max_depth))< A[N - 1]) {
      
    * rec_ct = * rec_ct + 1;
    
    *max_depth=*max_depth+1;
    return min_rec_2(A, N - 1, & ( * rec_ct), & ( * base_ct), & ( *max_depth));
   
  } else{
     
    *rec_ct = * rec_ct + 1;
  }
  return A[N - 1];
  
}

/*****************************Function min_rec_tail:To find minimum in an array**********************************/
int min_rec_tail(int * A, int N, int * rec_ct, int * base_ct,int *max_depth) {
    *max_depth=*max_depth+1;
  if (N == 0) {
    * base_ct = * base_ct + 1;
    return A[0];
  }
  * rec_ct = * rec_ct + 1;
  N--;

  return min_rec_tail(A + (A[0] > A[N]), N, & ( * rec_ct), & ( * base_ct),&(*max_depth));

}


/*****************************Function substring:To generate substring from a string*******************************/


char * substring(char s[], int p, int l) {
  int substringLength = l - p;
  int i;
  char * newSubstring = malloc((substringLength+1) *sizeof(char));
  int count = 0;
  for (i = p; i < l; i++) {
    newSubstring[count] = s[i];
    count = count + 1;
  }
  newSubstring[count] = '\0';
  return newSubstring;
  free(newSubstring);
}

/*****************************Function checkPalindrome :To Test if the string is palindrome or not****************/

int checkPalindrome(char * Arr, int l, int r) {
  while (l < r) 
  {
    if (Arr[l] != Arr[r])                                  //compare characters
      return 0;                                                   //return 0 if its not a palindrome
    l++;
    r--;
  }
  return 1;                                                      ////return 1 if its a palindrome
}

/*****************************Function PalindromeDecomp :Recursive function for palindrome decomposition****************/

void PalindromeDecomp(int stringlength, int pos, char * myString, char testArray[100][100], int * count) {
  int i = pos;
  int z;

  if (pos >= stringlength) {                                        //if the index is greater than string length print the array
    for (z = 0; z < stringlength; z++) {
      if (strlen(testArray[z]) != 0) {
        printf("%s,", testArray[z]);
      }
    }
    ( * count) ++;                                                  //generate the count of substrings generated
    printf("\n");
    return;
  }
  for (i = pos; i < stringlength; i++) {
    if (checkPalindrome(myString, pos, i)) {                          //Function call to check palindrome
      int newSubsLength = i - pos + 1;
      char * newSubstring;
      newSubstring = substring(myString, pos, i + 1);                 //if entered string is palindrome then call a substring function
      strcpy(testArray[pos], newSubstring);                            //copy the substring generated to test array
      PalindromeDecomp(stringlength, i + 1, myString, testArray, count);   //palindrome decomposition recursive call
      strcpy(testArray[pos], "");
      free(newSubstring);
      
    }
  }
}

/*********************Function palindromeDecompositionWrapper:Wrapper function to support Function PalindromeDecomp****************/
void palindromeDecompositionWrapper(char st[]) {
  int stringlength = strlen(st);                                        //calculate string length
  char *myString = malloc((stringlength + 1) * sizeof(char)); 
  strcpy(myString, st);                                                 //copy entered string to a new variable
  printf("\n");
  int count = 0;
  char testArray[100][100] ={0};
  PalindromeDecomp(stringlength, 0, myString, testArray, & count);             //Function call
  printf("%d", count);
  free(myString);
  
  
}
/*********************************************************************************************************************************/


int main() {

  /*******************************************Variable declaration*****************************************************************/
  int N;        //To enter array size
  int i;        //variable for the loops
  char st[100];  //declare a string 
  /*******************************************************************************************************************************/
  
  /**************************values to be entered to test if array is increasing or decreasing**************************************/
  
  while (1) {

      
      printf("Enter size of array.(Stop with -1)");                //Enter array size
      scanf("%d", &N);

      if (N == -1) {                                               //when user enters -1 program terminates and ask user to enter values for next function
          break;
      }

      
      printf("Enter array elements separated by spaces:");         //Enter array elements and store it in an array
      int a[N];
      for (i = 0; i < N; ++i) {
          scanf("%d", &a[i]);
      }

      int increasing_result = increasing(a, N);                    //Function call 
      if (increasing_result == 1)
          printf("increasing:1\n");
      else
          printf("increasing:0\n");
  }

  /***********************************values to be entered for Function:to find minimum in an array****************************************/


  while (1) {

      printf("Enter size of array(Stop with -1.)\n");                 //Enter array size
      scanf("%d", &N);
	
      if (N == -1) {
          break;                                                      //when user enters -1 program terminates and ask user to enter values for next function
      }
     
      printf("Enter array elements separated by spaces\n");
      int a[N];                                                       //Enter array elements and store it in an array

      for (i = 0; i < N; ++i) {
          scanf("%d", &a[i]);
      }
   

      int rec_ct = 0;
      int base_ct = 0;
      int max_depth=0;

      int minimum2 = min_rec_1(a, N, &rec_ct, &base_ct,&max_depth);
      printf("\n");
      printf("smallest_1:\tsmallest = %d, base_ct = %d, rec_ct = %d, max_depth = %d\n",minimum2,base_ct,rec_ct,max_depth); //Function call 

      rec_ct = 0;
      base_ct = 0;
      max_depth=0;
     
      int minimum1 = min_rec_2(a, N, &rec_ct, &base_ct, &max_depth);
      printf("smallest_2:\tsmallest = %d, base_ct = %d, rec_ct = %d, max_depth = %d\n",minimum1,base_ct,rec_ct,max_depth); //Function call 
      
      
      rec_ct = 0;
      base_ct = 0;
      max_depth=0;

      int minimum3 = min_rec_tail(a, N, &rec_ct, &base_ct,&max_depth);
      printf("smallest_tail:\tsmallest = %d, base_ct = %d, rec_ct = %d, max_depth = %d\n",minimum3,base_ct,rec_ct,max_depth); //Function call 
  }

  /*******************************Values to be Entered for function to decompose the strings**********************************************/

  
  int count = 0;
  printf("Enter strings. Stop with -1.");               //Enter strings
  while (1) {
    printf("\ns =");
    scanf("%s", & st);
    if (strcasecmp(st, "-1") == 0) {                    //When user enters  -1 terminates the program
      return 0;
    }
    printf("\n");
    palindromeDecompositionWrapper(st);                 //palindromeDecompositionWrapper Function call 
    printf("\n");
  }
  return 0;
}

