// Implementation provided by Elsy Fernandes

#include <stdio.h>
#include <stdlib.h>


/*******************************************RECURSIVE FUNCTION******************************************************************/

  int foo(int N) {
  if (N <= 1) return 5;
  int res1 = 3 * foo(N / 2);
  int res2 = foo(N - 1);
  if (res1 >= res2)
    return res1;
  else
    return res2;
}

/*******************************************ITERATIVE FUNCTION******************************************************************/
int foo_iterative(int N) {
  int i;
  int res1;
  int res2;
  int itr[N];
  itr[0] = 5;
  itr[1] = 5;
  
  if(N<=1){
      return 5;
  }
  for(i=2;i<=N;i++){
      res1 = 3* itr[i/2];
      res2 = itr[i-1];
      if(res1>= res2){
          itr[i]= res1;
      }
      else{
          itr[i]= res2;
      }
  }  
  return itr[N];
}

/*******************************************WRAPPER FUNCTION FOR MEMOIZED CODE***************************************************/

int foo_wrapper(int N) {
    int i;
  int solution[N + 1];
  solution[0] = 5;
  solution[1] = 5;
  for (i = 2; i < N + 1; i++) {
    solution[i] = -1;
  }
  int max_depth = 2;
  return foo_memoized(N, solution, max_depth);

}

/**********************************************MEMOIZED FUNCTION**********************************************************************************/

int foo_memoized(int N, int * Solution, int max_depth) {
    int i;
  max_depth = max_depth + 3;

  for (i = 0; i < max_depth; i++) {
    printf(" ");
  }

  printf("N = %d\n\n", N);
  if (Solution[N] != -1) {
    max_depth = max_depth - 3;
    return Solution[N];

  }

  int res1 = 3 * foo_memoized(N / 2, Solution, max_depth);
  int res2 = foo_memoized(N - 1, Solution, max_depth);
  if (res1 >= res2) {
    max_depth = max_depth - 3;
    Solution[N] = res1;
    return res1;
  } else {
    max_depth = max_depth - 3;
    Solution[N] = res2;
    return res2;
  }
}

/**************************************************MAIN FUNCTION*****************************************************************************/
int main() {
  int N;
  int result_rec;
  int result_iter;
  int result_wrap;
  int max_depth=0;

  while (1) {
    printf("Enter N:");
    scanf("%d", & N);
    if (N == -1) {
      break;
    }
    //call recursive function and print the result    
    int result_rec = foo(N);
    printf("Result of Recursive function for N=%d is:%d\n\n",N,result_rec);
    
    //call iterative function and print the result
    int result_iter = foo_iterative(N);
    printf("Result of Iterative function for N=%d is:%d\n\n", N,result_iter);
    
    //call wrapper function and print the memoized
    int result_wrap = foo_wrapper(N);
    printf("Result of memoized function for N=%d is:%d\n\n",N,result_wrap);

  }

}


