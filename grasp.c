#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "grasp.h"
#include "sorting.h"
int main()
{
    
 clock_t begin = clock();


 char* file_name = "text_matrix";
 //char* file_name = "text_matrix";
 //char* file_name = "frb100-40.txt";
 int max_deg;
 int iteration_counter = 0;
 float alfa = 0.7;
 Adj_Matrix * Matrix = Initialize_Matrix(file_name, &max_deg);
 
 int N_adjs = Number_of_adjacency(file_name);
 int N_vertex = Number_of_vertex(file_name);

 
 printf("Unsorted Matrix\n");
 
 print_matrix(Matrix,N_vertex);
 /*printf("\n");
Adj_Matrix * M = Replicate(Matrix, N_vertex);

 print_matrix(M,N_vertex);
 */

linked_list * rcl = RCL(Matrix , max_deg ,N_vertex , alfa);
Solution * S = Best_Solution(Matrix , N_vertex , N_vertex , create_solution(Matrix,N_vertex) , 3 , rcl);
print_solution(S);
printf("\nMin Found :%d , Searched : %d\n",S->Min, iteration_counter);


/*
linked_list * rcl = RCL(Matrix , max_deg,N_vertex , alfa);
print_list(rcl);
Solution * S = GRASP_construction(rcl , Matrix , N_vertex);
S = GRASP_post_construction(Matrix  , S , N_vertex );
print_solution(S);
printf("\nMin : %d\n", S->Min);
*/

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nExecuted in : %f s\n", time_spent);
return 0;
}