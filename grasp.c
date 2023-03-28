#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "sorting.h"
int main()
{
    
 clock_t begin = clock();


 char* file_name = "text_matrix";
 //char* file_name = "text_matrix";
 //char* file_name = "frb100-40.txt";
 int max_deg;
 float alfa = 0.4;
 Adj_Matrix * Matrix = Initialize_Matrix(file_name, &max_deg);
 
 int N_adjs = Number_of_adjacency(file_name);
 int N_vertex = Number_of_vertex(file_name);

 
 printf("Unsorted Matrix\n");
 
 print_matrix(Matrix,N_vertex);
 
printf("unsorted RCL|| Maximun degree : %d\n",max_deg);

linked_list * rcl = RCL(Matrix , max_deg,N_vertex , alfa);
print_list(rcl);
Solution * S = GRASP_construction(rcl , Matrix , N_vertex);

S = GRASP_post_construction(Matrix , N_vertex , S);
print_solution(S);
printf("\nMin : %d\n", S->Min);
 //CocktailSort(Matrix,N_vertex);
 //printf("Sorted Matrix\n");
 //Choose_Random_RCL(rcl);
 //printf("\n%d",Choose_Random_RCL(rcl)+1);
 
 //print_matrix(Matrix,N_vertex);
 
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nExecuted in : %f s\n", time_spent);
return 0;
}