#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "grasp.h"
#include "utils.h"
int main()
{
    
 clock_t begin = clock();

 //char* file_name = "test_matrix";
 
 //frb30-15

char* file_name = "/home/matheus/BHOSLIB_ascii/frb30-15-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb30-15-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb30-15-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb30-15-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb30-15-5.clq";

 //frb35-17

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb35-17-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb35-17-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb35-17-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb35-17-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb35-17-5.clq";


 //frb40-19

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb40-19-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb40-19-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb40-19-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb40-19-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb40-19-5.clq";


 //frb45-21

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb45-21-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb45-21-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb45-21-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb45-21-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb45-21-5.clq";


//frb50-23

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb50-23-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb50-23-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb50-23-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb50-23-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb50-23-5.clq";


//frb53-24

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb53-24-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb53-24-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb53-24-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb53-24-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb53-24-5.clq";


//frb59-26

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-1.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-2.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-5.clq";


//frb100-40

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb100-40.clq";


 int max_deg,N_vertex ;
 double elapsed =0 ;
 
 //char* file_name = "test_matrix";

 Adj_Matrix * Matrix = Initialize_Matrix_BHOSLIB(file_name, &max_deg, &N_vertex);


 //TEST AND DEBUG
 /*
 printf("Matrix\n");
 print_matrix(Matrix,N_vertex);
 Solution * S = GRASP(Matrix,N_vertex,max_deg);
 print_solution(S);
 printf("\nMin Found :%d \n",S->Min);
*/

Solution * S = GRASP(Matrix,N_vertex,max_deg , &elapsed);

 char* file_results = "test_results";
 
write_results(file_results , elapsed ,  S->Min);
printf("\nMin Found :%d \n",S->Min);

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//printf("\nExecuted in : %f s\n", time_spent);
return 0;
}