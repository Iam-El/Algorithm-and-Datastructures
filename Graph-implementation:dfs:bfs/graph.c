// Implementation provided by Elsy Fernandes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************Function:Depth First Search************************************************************************/
void depthFirstSearch(int G[10][10], int* nodeIncluded, int node, int size, char name[][200], bool print) {
    int j;
    if(print)
        printf("%s\n",name[node]);
    nodeIncluded[node] = 1;
    for(j=0; j<size; j++) {
        if(nodeIncluded[j]==0 && G[node][j] == 1) {
            depthFirstSearch(G,nodeIncluded,j,size, name, print);
        }
    }
}

/***********************************Main Function**************************************************************************************/

int main() {
    int N;                            //Declare Number of vertices
    int i;                            //Variable for loops
    int j;                            //Variables for loops
    int numberOfEdges = 0;
    bool flag = true;
    printf("\n");
    printf("Program output: ");
    printf("\n");
    printf("\n");
    printf("Enter number of vertices, N:");
    scanf("%d", &N);
    if(N==-1)
    {
        return 0;
    }

 /************************************Variable declaration******************************************************************************************/   
    char name[N][200];              
    char name1[N][200];             
    char name2[N][200];
    char inputName1[200];
    char inputName2[200];
    int resultMatrix[N][N];


    for (i = 0; i < N; i++) {

        printf("Enter name1: ");
        scanf("%s", &name[i]);
        if (strcasecmp(name[i], "-1") == 0) {
            return 0;
        }
    }
/*************************************Print Matrix********************************************************************************************/
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            resultMatrix[i][j] = 0;

        }
    }
    i = 0;


    while (flag) {
        printf("Enter name1 name2:");
        scanf("%s", &name1[i]);
        scanf("%s", &name2[i]);

        if (strcasecmp(name1[i], "-1") == 0 && strcasecmp(name2[i], "-1") == 0) {
            flag = false;
            numberOfEdges = i;
        }
        i++;
    }
    printf("\nGRAPH:\nN = %d\n",N);
    for (i = 0; i < N; i++) {
        printf("%d-%s\n",i, name[i]);
    }

    for(i=0; i<numberOfEdges; i++) {
        int indexOfFirstNode = 0;
        int indexOfSecondNode = 0;
        for(j=0; j<N; j++) {
            if(strcasecmp(name1[i], name[j]) == 0) {
                indexOfFirstNode = j;
            }
        }

        for(j=0; j<N; j++) {
            if(strcasecmp(name2[i], name[j]) == 0) {
                indexOfSecondNode = j;
            }
        }

        resultMatrix[indexOfFirstNode][indexOfSecondNode] = 1;
        resultMatrix[indexOfSecondNode][indexOfFirstNode] = 1;
    }

    printf("\n");

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            printf("%d ",resultMatrix[i][j]);

        }
        printf("\n");
    }
/**************************************Implementing DFS To form Groups*********************************************************************************************/
    int nodeIncluded[N];
    for(i=0; i<N; i++) {
        nodeIncluded[i] = 0;
    }
    int groupNumber = 1;
    int x = 0;

    for(i=0; i<N; i++) {
        if(nodeIncluded[i] == 0) {
            x = x+1;
            depthFirstSearch(resultMatrix,nodeIncluded,i,N, name, false);
        }
    }
    printf("Number of groups: %d\n",x);

    for(i=0; i<N; i++) {
        nodeIncluded[i] = 0;
    }
    x = 1;

    for(i=0; i<N; i++) {
        if(nodeIncluded[i] == 0) {
            printf("Group: %d\n",x );
            x = x+1;
            depthFirstSearch(resultMatrix,nodeIncluded,i,N, name, true);
            printf("\n");
        }
    }
    return 0;
}

