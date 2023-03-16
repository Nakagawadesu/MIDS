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
    Adj_Matrix * V;
    int  * D;
    int * C;
    int Max_Degree;
    int N_dominants;
    int N_complements;
    int N_vertex;
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
    
   printf("\nremoved : %d\n",current->V + 1);
   
    if(current->V== L->head->V ){
        L->head = current->next;
        free(current);
    }
    else if(current->V == L->foot->V){
        L->foot = current->previus;
        free(current);
    }else{
    L_cell * prev = current->previus;
    L_cell * next = current->next;
    next->previus = current->previus;
    prev->next = current->next;
    free(current);
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
        printf("V|D : %d|%d -> ",aux->V + 1 , aux->D);
        aux = aux->next;
        
    }
     printf("V|D:%d|%d",aux->V + 1 , aux->D);
    return 1;
}

int Order_list();


// GRAPH UTILS >>

Adj_Matrix * Initialize_Matrix(char * File , int * max_degree)
{
    *max_degree = 0;
    int N_rows,N_cols,N_ones;
    int vertex;
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
     
       fscanf(file,"%d %d",& aux->adj,&vertex);
       
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
                printf(" -> %d",aux->adj);
                aux = aux->next;
              
            }
              printf(" -> %d",aux->adj);
           printf("\n");
          }  
           
           
        }
}


int remove_vertex();
int add_vertex();
int remove_neighbors();

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
int Choose_Random_RCL(linked_list * RCL )
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
          // printf("\nto remove : %d\n",To_remove->V + 1);
        }
           
        current = current->next;

    }
    
    //printf("\nRandomly selected key is %d\n", selected+1);
    remove_Cell_list(RCL,To_remove);
    return selected;
}

#endif // GRAPH_H
