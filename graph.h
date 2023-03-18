#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int Line_max = 256;


// DATA STRUCTURES >>
typedef struct Adj_Matrix{

    struct Vertex_Cell * head;
   // int vertex;
    int degree;
    
}Adj_Matrix;

typedef struct L_cell{
 int V;
 int D;
 struct L_cell * next ;
 struct L_cell * previus; 
}L_cell;

typedef struct linked_list{
 struct L_cell * head;
 struct L_cell * foot;
 int Min_degree;
}linked_list;

typedef struct Vertex_Cell{

    int adj;
    struct Vertex_Cell  * next;

}Vertex_Cell;

typedef struct Solution{
    linked_list * V;
    linked_list * D;
    linked_list * C;
    int Min;
}Solution;


// Linked Lists >>
linked_list * create_list()
{
   linked_list * L = (struct linkedlist*)malloc(sizeof(linked_list));
   L->head = NULL;
   L->foot = NULL;
   L->Min_degree = 0 ;
   return L;
}
L_cell * create_cell(int V , int D)
{
   L_cell * aux = (L_cell*)malloc(sizeof(L_cell));
   aux->V = V;
   aux->D = D;
   aux->previus = NULL;
   aux->next = NULL;
   return aux;

}
int insert_in_list(linked_list * L, int V, int D)
{
    if(L->head == NULL)
    {
        L->head = create_cell(V,D);
        L->foot = L->head;
        return 1;
    }else{
    L_cell * aux = L->foot;
    L->foot = create_cell(V,D);
    aux->next = L->foot;
    L->foot->previus = aux;
    }
    
    return 1;
}

int remove_Cell_list(linked_list * L, L_cell * current )
{
    
   if(L->head->V == L->foot->V)
   {    
       printf("\nremoved last : %d\n",current->V + 1);
       L->head = NULL;
   }else{
       if(current->V == L->head->V ){
        printf("\nremoved head : %d\n",current->V + 1);
        L->head = L->head->next;
        free(current);
    }
    else if(current->V == L->foot->V){
        printf("\nremoved foot : %d\n",current->V + 1);
        L->foot = L->foot->previus;
        L->foot->next = NULL;
        free(current);
    }else{
        printf("\nremoved mid : %d\n",current->V + 1);
    L_cell * prev = current->previus;
    L_cell * next = current->next;
    next->previus = current->previus;
    prev->next = current->next;
    free(current);
    }
    
   }

    
    return 1;
}

void print_list(linked_list * L)
{
    printf("\n");
    if(L->head == NULL)
    {
        return ;
    }
    L_cell * aux = L->head;
    while(aux->next != NULL)
    {
        printf(" %d|%d -> ",aux->V + 1 , aux->D);
        aux = aux->next;
        
    }
     printf(" %d|%d",aux->V + 1 , aux->D);
    return 1;
}

int Order_list();


// GRAPH UTILS >>

Adj_Matrix * Initialize_Matrix(char * File , int * max_degree)
{
    *max_degree = 0;
    int N_rows,N_cols,N_ones;
    int vertex,adj;
//abre a strnam para o arquivo desejado    
FILE * file = fopen(File,"r");

if(file == NULL)
    {
        printf("NO SUCH FILE\n");
        return 0;
    }


   char * line_buffer = (char*)malloc( sizeof(char) * Line_max);
   
   //ignorando o header e pegando a segunda linha

   fscanf(file ,"%*s %*s %*s %*s %*s %d %d %d ",&N_rows ,&N_cols, &N_ones);
   

  // printf("%d %d %d\n",N_rows ,N_cols,N_ones);

   Adj_Matrix * Matrix = (Adj_Matrix*)malloc(N_rows * sizeof( Adj_Matrix));
   /*
   for(int i = 0 ; i < N_rows; i++ )
   {
       Matrix[i].vertex = i; //cada cabeca tera um numero correspondendo ao vertice
       //para possibilitar a ordenacao por grau no vertice
   }
*/
   Vertex_Cell * previus = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
  
  
   for(int i =0 ; i < N_ones + 1 ; i++)
   {
       Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     
       fscanf(file,"%d %d",&adj,&vertex);
       aux->adj = adj-1;
     // printf("%d %d ", aux->adj , vertex);
      //printf("\n");
       if(Matrix[vertex - 1].head == NULL)
       {
           Matrix[vertex - 1].degree++;
           Matrix[vertex - 1].head = aux;
           previus = aux;
       }
       else{
            Matrix[vertex - 1].degree++;
            previus->next = aux;
            previus = aux;
       }
       
      if (*max_degree < Matrix[vertex - 1].degree )
      {
           *max_degree = Matrix[vertex - 1].degree;
      }
       
   }
   //print_matrix(Row,N_rows,N_cols);
   return Matrix;

}

int  Number_of_adjacency(FILE * File)
{
FILE * file = fopen(File,"r");

int n;

fscanf(file ,"%*s %*s %*s %*s %*s %*d %*d %*d", &n);

//printf("%d",n);
fclose(file);
    return n;
}

int  Number_of_vertex(FILE * File)
{
FILE * file = fopen(File,"r");

int n;

fscanf(file ,"%*s %*s %*s %*s %*s %d", &n);

//printf("%d",n);
fclose(file);
    return n;
}


int print_matrix(Adj_Matrix * Matrix, int N_vertex)
{
    Vertex_Cell * aux;
    printf("\n");
    for (int i =0 ;i< N_vertex;i++)
        {
        if(Matrix[i].head == NULL)
          {
              printf("%d : NULL",i + 1);
            
          }
          else{
            
           printf("degree : %d || vertex : %d :", Matrix[i].degree,i+1);
            aux = Matrix[i].head;
            while (aux->next != NULL)
            {
                printf(" -> %d",aux->adj+1);
                aux = aux->next;
              
            }
              printf(" -> %d",aux->adj+1);
           printf("\n");
          }  
           
           
        }
}

Solution * create_solution(Adj_Matrix * M , int n)
{
    Solution * S = (Solution*)malloc(sizeof(Solution));
    S->V = create_list();
    for(int i = 0 ; i < n ; i++)
    {
        insert_in_list(S->V ,i , M[i].degree );
    }
    S->C = create_list();
    S->D = create_list();
    S->Min = 0;
    return S;
}
void * insert_Complement(int n , Solution* S)
{
   insert_in_list(S->C,n,0);
}
void * insert_Dominant(int n , Solution* S)
{
    insert_in_list(S->D,n,0);
}
void print_solution(Solution * S)
{ 
    printf("\nDominants:\n");
    print_list(S->D);
    printf("\nComplements:\n");
    print_list(S->C);
}

int remove_vertex(Adj_Matrix * M , int selected , Solution * S )
{
    
    if(M[selected].head == NULL)
    {
        printf("\nalready removed : %d \n",selected+1);
        //printf("\nremoving vertex %d \n",selected);
       return -1;
    }
    else{
        printf("\nremoving vertex : %d \n",selected+1);
       // printf("\nremoving vertex %d \n",selected);
    M[selected].head = NULL;
    }

    return 1;
}
int remove_neighbors(Adj_Matrix * M , int selected , Solution * S )
{
    
    
 
    if(M[selected].head == NULL)
    {
        printf("\nalready removed: %d \n",selected+1);
       return -1;
    }
    else{
        printf("\nremoving neighboor: %d \n",selected+1);
        
    Vertex_Cell * aux = M[selected].head;
    while(aux->next != NULL)
    {
        insert_Complement(aux->adj ,S);
        remove_vertex(M,aux->adj,S);
        aux = aux->next;
    }
    insert_Complement(aux->adj ,S);
    remove_vertex(M,aux->adj,S);
    }
    return 1;
}

// GRASP 

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
int Choose_Random_RCL(linked_list * RCL  ,Solution * S)
{
    
    if (RCL->head == NULL)
       return -1;
 
    srand(time(NULL));
 
    int selected = RCL->head->V;
    L_cell * To_remove ;
    To_remove = RCL->head;
    
    L_cell  * current = RCL->head;
    
    for (int n=2; current!=NULL; n++)
    {
        
        if (rand() % n == 0)
        {
           selected = current->V;
           To_remove = current;
          //printf("\nto removed : %d\n",To_remove->V + 1);
        }
           
        current = current->next;

    }
    
    //printf("\nRandomly selected key is %d\n", selected+1);
    
    remove_Cell_list(RCL,To_remove);
    print_list(RCL);
    return selected;
}

Solution * GRASP_construction(linked_list * RCL ,Adj_Matrix * M , int n )
{
      Solution * S  = create_solution(M , n);
      
 
      int selected_vertex;
      while(RCL->head != NULL)
      {
      selected_vertex = Choose_Random_RCL(RCL ,S);
      if(M[selected_vertex].head != NULL)
      {
          insert_Dominant(selected_vertex,S);
      }
      remove_neighbors(M, selected_vertex ,S);
      remove_vertex(M, selected_vertex ,S);
      }
      
      return S;

}
#endif // GRAPH_H
