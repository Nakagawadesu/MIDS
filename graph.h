#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int Line_max = 1024;


// DATA STRUCTURES >>
typedef struct Adj_Matrix{

    struct Vertex_Cell * head;
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
   linked_list * L = (linked_list*)malloc(sizeof(linked_list));
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
      // printf("\nremoved last : %d\n",current->V + 1);
       L->head = NULL;
   }else{
       if(current->V == L->head->V ){
       // printf("\nremoved head : %d\n",current->V + 1);
        L->head = L->head->next;
        free(current);
    }
    else if(current->V == L->foot->V){
      //  printf("\nremoved foot : %d\n",current->V + 1);
        L->foot = L->foot->previus;
        L->foot->next = NULL;
        free(current);
    }else{
      //  printf("\nremoved mid : %d\n",current->V + 1);
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
    
}


// GRAPH UTILS >>
void insert_adj(Adj_Matrix * M ,int V , int adj )
{
    if(M[V].head == NULL)
    {

     Vertex_Cell * new_cell = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));   

     new_cell->adj = adj;

     M[V].head = new_cell;
     M[V].degree++;   
    
    }
    else{
     Vertex_Cell * new_cell = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));   

     Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     aux = M[V].head;

     new_cell->adj = adj;
     while(aux->next != NULL)
     {
        aux = aux->next;
     }
    M[V].degree++;   
    aux->next = new_cell;
     
    }

    if(M[adj].head==NULL)
    {
     Vertex_Cell * new_cell = (Vertex_Cell*)malloc(sizeof(Vertex_Cell)); 
       
     new_cell->adj = V;

     M[adj].head = new_cell;
     M[adj].degree++; 
       
    }
    else{
      Vertex_Cell * new_cell = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));   

     Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     aux = M[adj].head;

     new_cell->adj = V;

     while(aux->next != NULL)
     {
        aux = aux->next;
     }
     aux->next = new_cell;
     M[adj].degree++;   
      
    }
}

Adj_Matrix * Initialize_Matrix_Dimacs(char * File , int * N)
{
    int N_vertex,N_adj;
    int vertex,adj;
   
FILE * file = fopen(File,"r");

    if(file == NULL)
    {
        printf("NO SUCH FILE\n");
        return 0;
    }


   char * line_buffer = (char*)malloc( sizeof(char) * Line_max);
   
   //ignorando o header e pegando a segunda linha

   fscanf(file ,"%d %d ",&N_adj,&N_vertex);
   *N = N_vertex; 



   Adj_Matrix * Matrix = (Adj_Matrix*)malloc(N_vertex * sizeof( Adj_Matrix));
   int count = 0;
    while(fgets(line_buffer,Line_max,file))
    {
        if(count > 0)
        {
        Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     
        sscanf(line_buffer,"%d %d",&adj,&vertex);
        /*
        if(count <10)
        {
            printf("line buffer: %s " , line_buffer);
        }
        */
        
        insert_adj(Matrix , vertex-1 , adj-1 );
        }        
        count ++;
      
    }
    return Matrix;
}
Adj_Matrix * Initialize_Matrix_BHOSLIB_old(char * File , int * N)
{
    
    int N_vertex,N_adj;
    int vertex,adj;
   
FILE * file = fopen(File,"r");

if(file == NULL)
    {
        printf("NO SUCH FILE\n");
        return 0;
    }


   char * line_buffer = (char*)malloc( sizeof(char) * Line_max);
   
   //ignorando o header e pegando a segunda linha

   fscanf(file ,"%*s %*s  %d %d ",&N_vertex, &N_adj);
   
   *N = N_vertex; 


   Adj_Matrix * Matrix = (Adj_Matrix*)malloc(N_vertex * sizeof( Adj_Matrix));
   
   for(int i =0 ; i < N_adj ; i++)
   {
       Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     
       fscanf(file,"%*s %d %d",&vertex,&adj);

        insert_adj(Matrix , vertex-1 , adj-1 );
       
            
   
   }
    return Matrix;
}
Adj_Matrix * Initialize_Matrix_BHOSLIB_new(char * File  , int * N)
{
    
    int N_vertex,N_adj;
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
   fscanf(file ,"%*s %*s  %*s %*s %*s");

   fscanf(file ,"%*d  %d %d ",&N_vertex, &N_adj);
   
   *N = N_vertex; 


   Adj_Matrix * Matrix = (Adj_Matrix*)malloc(N_vertex * sizeof( Adj_Matrix));
   
   for(int i =0 ; i < N_adj ; i++)
   {
       Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
     
       fscanf(file,"%d %d",&adj,&vertex);

        insert_adj(Matrix , vertex-1 , adj-1 );
       
            
   
   }
    return Matrix;
}

Adj_Matrix * Replicate(Adj_Matrix * M, int n)
{
    Adj_Matrix * Matrix = (Adj_Matrix*)malloc(n * sizeof( Adj_Matrix));
    int count;
    Vertex_Cell * aux = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
    for(int i = 0 ; i < n  ; i++)
   {
       Vertex_Cell * previus = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
       count = 0 ;
       if (M[i].head == NULL)
       {

       }
       else{
           Matrix[i].degree = M[i].degree;
            aux = M[i].head;
           
           while(aux->next != NULL)
           {
               if(count == 0 )
               {
                Vertex_Cell * new = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
                new->adj = aux->adj;
                previus = new;
                Matrix[i].head = new;
                aux = aux->next;
                count ++;
               }
               else{
                Vertex_Cell * new = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
                new->adj = aux->adj;
                previus->next = new;
                previus = new;
                aux = aux->next;
               }
               
           }
           if(count == 0)
           {
            Vertex_Cell * new = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
                new->adj = aux->adj;
                previus = new;
                Matrix[i].head = new;
           }
           else{
            Vertex_Cell * new = (Vertex_Cell*)malloc(sizeof(Vertex_Cell));
            new->adj = aux->adj;
            previus->next = new;
            new->next = NULL;
           }
            
       }
   }
    return Matrix;
}

int print_matrix(Adj_Matrix * Matrix, int N_vertex)
{
    Vertex_Cell * aux;
    printf("\n");
    for (int i =0 ;i< N_vertex;i++)
        {
        if(Matrix[i].head == NULL)
          {
              printf("%d : NULL \n",i + 1);
            
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
int print_matrix_degrees(Adj_Matrix * Matrix, int N_vertex)
{
    
    printf("\n");
    for (int i =0 ;i< N_vertex;i++)
        {
        if(Matrix[i].head == NULL)
          {
              printf("%d : NULL \n",i + 1);
            
          }
          else{
            
           printf("degree : %d || vertex : %d :", Matrix[i].degree,i+1);
           
           printf("\n");
          }  
           
           
        }
}
Solution * create_solution(Adj_Matrix * M , int n)
{
    Solution * S = (Solution*)malloc(sizeof(Solution));
    S->V = create_list();
   /* for(int i = 0 ; i < n ; i++)
    {
        insert_in_list(S->V ,i , M[i].degree );
    }*/
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
        //printf("\nalready removed : %d \n",selected+1);
        //printf("\nremoving vertex %d \n",selected);
       return -1;
    }
    else{
       // printf("\nremoving vertex : %d \n",selected+1);
       // printf("\nremoving vertex %d \n",selected);
    M[selected].head = NULL;
    }

    return 1;
}
int remove_neighbors(Adj_Matrix * M , int selected , Solution * S )
{
    
    int removed = 0;
 
    if(M[selected].head == NULL)
    {
       // printf("\nalready removed: %d \n",selected+1);
       return -1;
    }
    else{
        //printf("\nremoving neighboor: %d \n",selected+1);
        
    Vertex_Cell * aux = M[selected].head;
    while(aux->next != NULL)
    {

        reduce_neighbors_degree(M,aux->adj);
        
        removed = remove_vertex(M,aux->adj,S);
         if(removed != -1 )
        {
            insert_Complement(aux->adj ,S);
           
        }
        aux = aux->next;
    }
    
    removed = remove_vertex(M,aux->adj,S);

    if(removed != -1 )
        {
            insert_Complement(aux->adj ,S);
            
        }
    }
    return 1;
}
int reduce_neighbors_degree(Adj_Matrix * M , int selected )
{

    
    int removed = 0;
 
    if(M[selected].head == NULL)
    {
       return -1;
    }
    else{
 
    Vertex_Cell * aux = M[selected].head;
    while(aux->next != NULL)
    {
        
        M[aux->adj].degree--;
        aux = aux->next;
    }
    
    M[aux->adj].degree--;
    return 1;

    }
}

#endif // GRAPH_H
