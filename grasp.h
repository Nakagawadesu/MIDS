#ifndef GRASP_H
#define GRASP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

void Find_degree_stats(Adj_Matrix * M , int N, int * max_deg , int * min_deg , float * avg ,int * V_left)
{
    *max_deg = 0 ;
    *min_deg = __INT32_MAX__;
    int sum = 0, vertex_count = 0;
    for(int i = 0 ; i <  N ; i++)
    {
        if(M[i].head != NULL)
        {
            if(M[i].degree > *max_deg)
        {
            *max_deg = M[i].degree;
        }
        if(M[i].degree < *min_deg)
        {
            *min_deg = M[i].degree;
        }
        vertex_count ++;
        sum += M[i].degree;
        }
        
        
    }
    *avg = sum/vertex_count;
    *V_left = vertex_count;
}
void Recalculate_alfa (Adj_Matrix * M , int N , int * max_deg , int * min_deg , float * avg , float *alfa , int * V_left)
{
   
    Find_degree_stats(M, N, max_deg, min_deg, avg, V_left);
    
    *alfa = ( *avg / *max_deg ) + (1 - ( *avg / *max_deg ))/2 ; 
}
linked_list * create_RCL(Adj_Matrix * M ,int max_degree , int n ,float alfa )
{
 linked_list * RCL = create_list();
 RCL->Min_degree = max_degree * alfa;
 printf("alfa : %f",alfa);
 for(int i = 0 ; i< n ;i++)
 {
     if(M[i].degree > RCL->Min_degree )
     {
         insert_in_list(RCL,i,M[i].degree);
     }
 }
 return RCL;
}
int post_RCL(Adj_Matrix * M ,int n , Solution * S )
{

  for(int i = 0 ; i< n ; i++)
  {
      if(M[i].head != NULL)
      {
         // printf("\ninserted in S->V :%d\n", i );
          insert_in_list(S->V , i , M[i].degree);
      }
  }
  return 1;
} 
int Choose_Random_post_RCL(Adj_Matrix * M   ,Solution * S)
{
     
    if (S->V->head == NULL)
       return -1;
 
    srand(time(NULL));
 
    int is_Dominant = 1;
    int selected = S->V->head->V;
    L_cell * To_remove ;
    To_remove = S->V->head;
    
    L_cell  * current = S->V->head;
    
    for (int n=2; current!=NULL; n++)
    {
        
       
        if(M[current->V].head == NULL) // adjacencia ja foi retirada  nao pode ser selecionada para ser dominante 
        {
            To_remove = current;
            is_Dominant = 0;
            current = NULL;
        }else{//caso nao tenha sido returado podera ser escolhido
         if (rand() % n == 0)
        {
           selected = current->V;
           To_remove = current;
           
          //printf("\nto removed : %d\n",To_remove->V + 1);
        }
        current = current->next;
        }
    }
    
    //printf("\nRandomly selected key is %d\n", selected+1);
    
    remove_Cell_list(S->V,To_remove);
    if(is_Dominant == 1)
    {
        insert_Dominant(selected , S);//saiu do for como escolhido e nao porque a adjacencia ja foi removido
        S->Min ++;
        //print_list(S->V);
        return selected;
    }else{//nenhuma adjacencia foi selecionada 
       // print_list(S->V);
        return -1;
    }
    return -1;
}  
int Choose_Random_RCL(Adj_Matrix * M ,linked_list * RCL  ,Solution * S)
{
    
    if (RCL->head == NULL)
       return -1;
 
    srand(time(NULL));
 
    int is_Dominant = 1;
    int selected = RCL->head->V;
    L_cell * To_remove ;
    To_remove = RCL->head;
    
    L_cell  * current = RCL->head;
    
    for (int n=2; current!=NULL; n++)
    {
        
       
        if(M[current->V].head == NULL) // adjacencia ja foi retirada  nao pode ser selecionada para ser dominante 
        {
            To_remove = current;
            is_Dominant = 0;
            current = NULL;
        }else{//caso nao tenha sido returado podera ser escolhido
         if (rand() % n == 0)
        {
           selected = current->V;
           To_remove = current;
           
          //printf("\nto removed : %d\n",To_remove->V + 1);
        }
        current = current->next;
        }
    }
    
    //printf("\nRandomly selected key is %d\n", selected+1);
    
    remove_Cell_list(RCL,To_remove);
    if(is_Dominant == 1)
    {
        insert_Dominant(selected , S);//saiu do for como escolhido e nao porque a adjacencia ja foi removida
        S->Min ++;
        //print_list(RCL);
        return selected;
    }else{//nenhuma adjacencia foi selecionada 
        //print_list(RCL);
        return -1;
    }
    return -1;
}

Solution * GRASP_construction(Adj_Matrix * M , int n  , Solution * S , int max_deg , float alfa )
{
       
      linked_list * RCL  = create_RCL(M,max_deg,n,alfa);
 
      int selected_vertex;
      while(RCL->head != NULL)
      {
      selected_vertex = Choose_Random_RCL( M ,RCL ,S);
      if(selected_vertex != -1)// ja foi removido
      {
          remove_neighbors(M, selected_vertex ,S);
          remove_vertex(M, selected_vertex ,S);
      }
      }
     
      return S;

}
Solution * GRASP_post_construction(Adj_Matrix * M , Solution * S , int n )
{
      
 
      int selected_vertex;
      while(S->V->head != NULL)
      {
      selected_vertex = Choose_Random_post_RCL( M  ,S);
      if(selected_vertex != -1)// ja foi removido
      {
          remove_neighbors(M, selected_vertex ,S);
          remove_vertex(M, selected_vertex ,S);
      }
      }
      return S;

}
Solution * GRASP(Adj_Matrix * M , int n ,double * elapsed)
{
    clock_t begin = clock();
   
     Solution * S  = create_solution(M , n);

    float alfa ,avg ;
    int max_deg = 0, min_deg =4000 , V_left = n; 

    Recalculate_alfa(M , n, &max_deg, &min_deg, &avg, &alfa , &V_left);

    printf("\nmax deg : %d || min deg : %d || avg deg : %f || alfa: %f || V_left: %d\n", max_deg, min_deg, avg,alfa,V_left);

    while( alfa >= 0.51  && max_deg >= 2  && avg > 2 )
    {
        

        S = GRASP_construction( M , n, S , max_deg , alfa);
        
        Recalculate_alfa(M , n, &max_deg, &min_deg, &avg, &alfa ,&V_left);
        printf("\nmax deg : %d || min deg : %d || avg deg : %f || alfa: %f|| V_left: %d\n", max_deg, min_deg, avg,alfa,V_left);
    }
    post_RCL(M , n , S );
    print_list(S->V);
    GRASP_post_construction(M , S ,n);
    
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    *elapsed = time_spent;
    printf("\nExecuted in : %f s\n", *elapsed);
    return S;
}
Adj_Matrix * test_solution(Adj_Matrix * M,Solution *S)
{
    L_cell * aux = S->D->head;
    while(aux->next != NULL)
    {
        remove_neighbors(M,aux->V,S);
        aux = aux->next;
    }
    remove_neighbors(M,aux->V,S);
    return M;
}
#endif // GRASP_H