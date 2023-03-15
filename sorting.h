#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

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
/*
void Insertion_sort(Adj_Matrix *Matrix, int left, int right)
{
    int sorted = left, insert = left + 1;

    for (int i = left; i < right; i++)
    {
        sorted = insert;

        while (Matrix[sorted].degree < Matrix[sorted - 1].degree )
        {

            swap(Matrix, sorted, sorted - 1);
            sorted--;
        }

        insert++;
    }
   
}

void Merge_sort(Adj_Matrix * Matrix , int left , int mid, int right )
{
    int left_counter = 0 , merge_counter = left , right_counter =  0;
    Temp_degree_vec * Temp = (Temp_degree_vec*)malloc((right - left) * sizeof(Temp_degree_vec));
   

    while(left_counter < mid - left -1 && right_counter < right - mid -1)
    {
        if(Matrix[right +right_counter].degree > Matrix[left + left_counter].degree  )
        {
            Temp[merge_counter].degree =  Matrix[right + right_counter].degree;
            Temp[merge_counter].vertex =  Matrix[right + right_counter].vertex; 
            merge_counter++;
            right_counter++;

        }
        else{
            Temp[merge_counter].degree =  Matrix[left + left_counter].degree;
            Temp[merge_counter].vertex =  Matrix[left + left_counter].vertex;
            merge_counter++;
            left_counter++;

        }
        
        //inserir o restante dos dados ordenados
        for(int i = left_counter ; i < mid-left ;i++ )
        {
            Temp[merge_counter].degree =  Matrix[left + left_counter].degree;
            Temp[merge_counter].vertex =  Matrix[left + left_counter].vertex;
            merge_counter++;
            left_counter++;
        }

        for(int i = right_counter ; i < mid-right ;i++ )
        {
            Temp[merge_counter].vertex =  Matrix[right + right_counter].vertex;
            Temp[merge_counter].degree =  Matrix[right + right_counter].degree;
            merge_counter++;
            right_counter++;
        }
        
    }
    merge_counter = 0;
    for(int i = left ; i < right ;i++ )
    {
        Matrix[i].degree = Temp[merge_counter].degree ;
        Matrix[i].vertex = Temp[merge_counter].vertex ;
        merge_counter++;
    }
} 

void  Tim_sort(Adj_Matrix * Matrix , int n_vertex )
{
  int RUN = 16;
  for(int i = 0 ; i < n_vertex ; i += RUN )
  {
      Insertion_sort(Matrix , i , i + RUN); 
  }

}
*/
#endif 