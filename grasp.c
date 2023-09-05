#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "grasp.h"
#include "utils.h"
int main()
{
    
char dir[100];
char c;
scanf("%c" , &c );

if(c == 98)//bhoslib
{
strcat(dir,"/home/matheus/BHOSLIB_ascii/");
printf("C:%c ,dir :%s\n",c,dir);
}else{//dimacs
strcat(dir,"/home/matheus/dimacs.mis/");
printf("C:%c ,dir :%s\n",c,dir);
}

char graph_name[30] ;


scanf("%s" , &graph_name);

 int N_vertex ;
 double elapsed = 0 ;

strcat(dir,graph_name);
printf("dir :%s\n",dir);

srand(time(NULL));

// INITIALIZE MATRIX
Adj_Matrix * Matrix;

if(c == 98)//bhoslib
{
Matrix = Initialize_Matrix_BHOSLIB_old(dir,&N_vertex);
}else{//dimacs
Matrix = Initialize_Matrix_Dimacs(dir,&N_vertex);
}


//Adj_Matrix * Replica = Replicate(Matrix,N_vertex);

Solution * S = GRASP(Matrix , N_vertex , &elapsed );


printf("\nMin Found :%d \n",S->Min);
//print_solution(S);

// WRITE RESULTS


char results_dir[100] = "/home/matheus/BHOSLIB_results/";
//char results_dir[100] = "/home/matheus/ dimacs.mis_results/";

write_results(results_dir , graph_name , elapsed ,  S->Min);
//write_results_sets(results_dir,graph_name,S,elapsed);

// TEST Solution
//Replica = test_solution(Replica,S);
//print_matrix(Replica,N_vertex);
//printf("\nExecuted in : %f s\n", time_spent);
return 0;
}