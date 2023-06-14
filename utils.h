#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"


void write_results (char * dir , char * g_name , double time_elapsed , int min )
{
    strcat(dir,g_name);
    FILE * file = fopen(dir,"a");
    if(file == NULL)
    {
        exit(-1);
    }
    fprintf(file, "%d,%lf\n",min ,time_elapsed);
    fclose(file);
}
void write_results_sets(char * dir , char * g_name , Solution * S, double time_elapsed  )
{

    strcat(dir,g_name);
    strcat(dir,"_sets");
    FILE * file = fopen(dir,"a");
    if(file == NULL)
    {
        exit(-1);
    }
    fprintf(file, "%d,%lf\n",S->Min ,time_elapsed);
    fprintf(file, "D :{\n");
    
      
    if(S->D->head != NULL)
    {
    L_cell * aux = S->D->head;
    while(aux->next != NULL)
    {
        fprintf(file, "%d\n",aux->V);
        aux = aux->next;
        
    }
     fprintf(file, "%d\n",aux->V);
    

    }
   
    fprintf(file, "\n}\n");
    fprintf(file, "C :\n");

    if(S->C->head != NULL)
    {
    L_cell * aux = S->C->head;
    while(aux->next != NULL)
    {
        fprintf(file, "%d\n",aux->V);
        aux = aux->next;
        
    }
     fprintf(file, "%d\n",aux->V);
    

    }

     fprintf(file, "\n}\n");
    fclose(file);
}

int swap(Adj_Matrix *Adj_matrix, int a, int b)
{
    Adj_Matrix aux;

    aux = Adj_matrix[a];
    Adj_matrix[a] = Adj_matrix[b];
    Adj_matrix[b] = aux;
   // printf("swapped : %d <-> %d \n", Adj_matrix[a].vertex, Adj_matrix[b].vertex);
    return 1;
}

void CocktailSort(Adj_Matrix * Matrix, int n)
{
    int swapped = 0;
    int start = 0;
    int end = n-1;

while(end != start )
{
    //printf("log");
    for(int i = 0; i < end ;i++)
    {
      if(Matrix[i].degree < Matrix[i+1].degree)
      {
          swap(Matrix , i, i+1);
          swapped = 1;
          //printf("direction:right , index %d\n",i);
      }
    }

    if(swapped != 1)
        break;

    swapped = 0;

    end--;

    for(int i = end; i >= start ;i--)
    {
      if(Matrix[i].degree < Matrix[i+1].degree)
      {
          swap(Matrix,i,i+1);
          //printf("direction:left , index %d\n",i);
          swapped = 1;
      }
    }

   start++;
}
}

#endif //UTILS_H