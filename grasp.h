#ifndef GRASP_H
#define GRASP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"


linked_list * RCL(Adj_Matrix * M ,int max_degree , int n ,float alfa )
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
      if(M[i].head != NULL)//coloca tudo oque sobrou em uma lista de vertices restantes
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

Solution * GRASP_construction(linked_list * RCL ,Adj_Matrix * M , int n )
{
      Solution * S  = create_solution(M , n);
      
 
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
      post_RCL(M,n,S);
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
Solution * Best_Solution(Adj_Matrix * M  , int n , int Best , Solution * Best_S , int stop ,linked_list * RCL)
{
  
    if(Best <= stop ){
        printf("\n FOUND \n");
        return Best_S;
    }
    else{
        Adj_Matrix * M_Replica  = Replicate(M,n);

        Solution * S = GRASP_construction(RCL , M_Replica , n);
        S = GRASP_post_construction(M_Replica  , S , n );

        if(S->Min < Best)
        {
            printf("\nNot Found , Current minimun : %d \n",Best);
            print_solution(S);
            return Best_Solution(M , n, S->Min , S , stop , RCL);
        }
        else{
            
            printf("\nNot Found , Current minimun : %d \n",Best);
            print_solution(S);
            return Best_Solution(M , n, Best , S , stop , RCL);
        }
        
        
    }
}

#endif // GRASP_H