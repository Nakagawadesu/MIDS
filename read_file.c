

/* 
int swap(Vertex_Degree * vector ,int  a ,int  b)
{
    Vertex_Degree  aux ;
    aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;
    //printf("%d < - > %d\n",a,b); 
    return 1;

}
void CocktailSort(Vertex_Degree * vector, int n)
{
    int swapped = 0;
    int start = 0;
    int end = n-1;

while(end != start )
{
    //printf("log");
    for(int i = 0; i < end ;i++)
    {
      if(vector[i].degree < vector[i+1].degree)
      {
          swap( vector,i,i+1);
          swapped = 1;
          printf("direction:right , index %d\n",i);
      }
    }

    if(swapped != 1)
        break;

    swapped = 0;

    end--;

    for(int i = end; i >= start ;i--)
    {
      if(vector[i].degree < vector[i+1].degree)
      {
          swap(vector,i,i+1);
          printf("direction:left , index %d\n",i);
          swapped = 1;
      }
    }

   start++;
}
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Line_max = 256;



typedef struct Adj_Matrix{

    struct Vertex_Cell * head;
    int vertex;
    int degree;
    
}Adj_Matrix;

typedef struct Vertex_Cell{

    int adj;
    struct Vertex_Cell  * next

}Vertex_Cell;

typedef struct Solution{
    Adj_Matrix * V;
    int  * D;
    int * C;
    int N_dominants;
    int N_complements;
    int N_vertex;
}Solution;
/* typedef struct Adj_Matrix{
    struct Rows * Row;
    int N_vertices;
}; */

int print_matrix(Adj_Matrix * Matrix, int N_vertex)
{
    Vertex_Cell * aux;
    
    for (int i =0 ;i< N_vertex;i++)
        {
        if(Matrix[i].head == NULL)
          {
              printf("%d : NULL",i + 1);
              /* for (int j= 0 ; j < N_vertex ; j++)
              {
                printf("0 ");
              } */
          }
          else{
              printf("degree : %d // vertex : %d :",Matrix[i].degree,i + 1);
              int j = 0 ;
             aux = Matrix[i].head;
              while(aux->next != NULL){

                  /* for( j ; j < aux->adj ;j++ )
                  {
                      printf("0 ");
                  }
                  j = aux->adj;
                  
                  printf("1 "); */
                  printf(" -> %d" , aux->adj);
                  aux = aux->next;
              }
             /*  j = aux->adj;
              printf("1 "); */
              printf(" -> %d",aux->adj);
              /* for(int i = j ; j< N_vertex ; j++)
              {
                   printf("0 ");
              } */
          }  
           
           printf("\n");
        }
}



Adj_Matrix * Initialize_Matrix(char * File )
{
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
   
   for(int i = 0 ; i < N_rows; i++ )
   {
       Matrix[i].vertex = i; //cada cabeca tera um numero correspondendo ao vertice
       //para possibilitar a ordenacao por grau no vertice
   }

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
       
      
       
   }
   //print_matrix(Row,N_rows,N_cols);
   return Matrix;

}

int Insertion_sort( Adj_Matrix * Matrix , int left , int right )
{

    
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

 
/* 
Solution * Gulosinho(int N_vertex,Vertex_Degree * Degree_Vector ,struct Rows * Adj_matrix)
{
   Vertex_Degree * Dominant = (Vertex_Degree*)malloc(N_vertex * sizeof(Vertex_Degree));
   Vertex_Degree * Complement = (Vertex_Degree*)malloc(N_vertex * sizeof(Vertex_Degree));
   int D_counter = 0,C_counter = 0;
   //optei nao utilizar listas encadeadas devido a perda de tempo com alocacao de memoria dinamica ja que a otimizacao de custo
   //de memoria nao importa apenas enficinecia de tempo
   for (int i = 0 ;i < N_vertex ; i++ )
   {
       if(Adj_matrix[i].Colum != NULL)
       {
           
         printf("dominant vertex: %d \n",D_counter);
         Dominant[D_counter].vertex = Degree_Vector[i].vertex  ;//adiciona o vertice ao conjunto dos dominantes
         D_counter++;
         printf("neighborhood \n");
         for(int j = 0 ; j < N_vertex ;j++ )//para cada vertice ainda no Grafo G
         {
             if (Adj_matrix[i].Colum[j] == 1 ) // se encontrar adjacencia (aplicar um algoritimo de busca mais eficiente)
             {
                printf(" %d ",j);
                Complement[C_counter].vertex = j+1;//adiciona vertices adjacentes ao conjnto complementar
                free(Adj_matrix[j].Colum);//remove da lista de adjacencia os vertices 
                C_counter++;
             }
             
         }
         printf("\n");
        free(Adj_matrix[i].Colum);//remove da matris de adjacencia  G          
       }
       Degree_Vector[i].vertex  = 0;//remove o vertice do conjunto G
     

   } 
   Solution * solution = (Solution*)malloc(sizeof(Solution));
   //printf(" %d %d",D_counter ,C_counter);
   solution->N_dominants = D_counter;
   solution->N_complements = C_counter;
   solution->C = Complement;
   solution->D = Dominant;
}*/

int main()
{
    
 clock_t begin = clock();


 char* file_name = "text_matrix";
 //char* file_name = "text_matrix";
 //char* file_name = "frb100-40.txt";
 Adj_Matrix * Matrix = Initialize_Matrix(file_name);
 
 int N_adjs = Number_of_adjacency(file_name);
 int N_vertex = Number_of_vertex(file_name);

 
 printf("Unsorted\n");
 
 print_matrix(Matrix,N_vertex);
/*   for(int i =  0 ;i < N_vertex ;i++)
{
    printf("vertex: %d Degree : %d\n",Degree_Vector[i].vertex ,Degree_Vector[i].degree);
} 

//CocktailSort(Degree_Vector,N_vertex);

printf("Sorted\n");
for(int i =  0 ;i < N_vertex ;i++)
{
    printf("vertex: %d Degree : %d\n",Degree_Vector[i].vertex,Degree_Vector[i].degree);
} 
 */


//Solution * solution = Gulosinho(N_vertex,Degree_Vector , Adj_Matrix);

printf("Solution:\n");

/* printf("Dominant set:\n");

for(int i =  0 ;i < solution->D ;i++)
{
    printf(" %d ",solution->D[i].vertex);
} 

printf("Complement:\n");

for(int i =  0 ;i < solution->C ;i++)
{
    printf(" %d ", solution->C[i].vertex);
}  */


clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("Executed in : %f s\n", time_spent);
return 0;
}