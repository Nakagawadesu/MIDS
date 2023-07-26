#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "grasp.h"
#include "utils.h"
int main()
{
    



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

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26vg .clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-3.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-4.clq";
//char* file_name = "/home/matheus/BHOSLIB_ascii/frb59-26-5.clq";


//frb100-40

//char* file_name = "/home/matheus/BHOSLIB_ascii/frb100-40.clq";


char dir[100] = "/home/matheus/dimacs.mis/";
char graph_name[30] = "brock200_1.mis";

/*
char dir[100] = "/home/matheus/Desktop/MIDS/";
char graph_name[30]= "test_matrix";
*/
/*
char dir[100] = "/home/matheus/BHOSLIB_ascii/";
char graph_name[30] = "frb30-15-1.clq";
*/

//char* file_name = "test_matrix";
//scanf("%s" , &graph_name);

 int N_vertex ;
 double elapsed = 0 ;



strcat(dir,graph_name);

// INITIALIZE MATRIX
//Adj_Matrix * Matrix = Initialize_Matrix_BHOSLIB_old(dir,&N_vertex);
Adj_Matrix * Matrix = Initialize_Matrix_Dimacs(dir,&N_vertex);

/*
print_matrix_degrees(Matrix,N_vertex);

Find_degree_stats(Matrix , N_vertex, &max_deg , &min_deg , &avg_deg);
Recalculate_alfa(Matrix, N_vertex ,&max_deg , &min_deg , &avg_deg , &alfa);
printf("\nmax deg : %d || min deg : %d || avg deg : %f || alfa: %f\n", max_deg, min_deg, avg_deg,alfa);
 
*/


Adj_Matrix * Replica = Replicate(Matrix,N_vertex);

//Solution * S = GRASP(Matrix,N_vertex,max_deg , &elapsed);

Solution * S = GRASP(Matrix , N_vertex , &elapsed );


printf("\nMin Found :%d \n",S->Min);
 print_solution(S);

// WRITE RESULTS


//char results_dir[100] = "/home/matheus/BHOSLIB_results/";
//char results_dir[100] = "/home/matheus/ dimacs.mis_results/";

//write_results(results_dir , graph_name , elapsed ,  S->Min);
//write_results_sets(results_dir,graph_name,S,elapsed);

// TEST Solution
//Replica = test_solution(Replica,S);
//print_matrix(Replica,N_vertex);
//printf("\nExecuted in : %f s\n", time_spent);
return 0;
}