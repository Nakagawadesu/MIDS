#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 
toggle : ctrl + 8
next : crtl+ 0
previus : crtl+ 9
 */
int Line_max = 256;

typedef struct Adj_Matrix
{

    struct Vertex_Cell *head;
    int vertex;
    int degree;

} Adj_Matrix;

typedef struct Temp_degree_vec
{
    int vertex;
    int degree;
}Temp_degree_vec; 

typedef struct Vertex_Cell
{

    int adj;
    struct Vertex_Cell **adj_head;
    //struct Adj_Matrix *adj_head;
    struct Vertex_Cell *next

} Vertex_Cell;

typedef struct Solution
{
    Adj_Matrix *V;
    int *D;
    int *C;
    int N_dominants;
    int N_complements;
    int N_vertex;
} Solution;


int print_matrix(Adj_Matrix *Matrix, int N_vertex)
{
    Vertex_Cell *aux ;

    for (int i = 0; i < N_vertex; i++)
    {
        if (Matrix[i].head == NULL)
        {
            printf("%d : NULL", i + 1);
            
        }
        else
        {
            printf("degree : %d // vertex : %d :", Matrix[i].degree, Matrix[i].vertex);
            int j = 0;
            aux = Matrix[i].head;
            while (aux->next != NULL)
            {

    
                printf(" -> %d:%d", aux->adj, aux->adj_head);
                aux = aux->next;
            }
           
            printf(" -> %d:%d", aux->adj, aux->adj_head);
            
        }

        printf("\n");
    }
}

int print_matrix_degree_only(Adj_Matrix *Matrix, int N_vertex)
{
    Vertex_Cell *aux;

    for (int i = 0; i < N_vertex; i++)
    {
        if (Matrix[i].head == NULL)
        {
            printf("degree : %d // vertex : %d ", Matrix[i].degree, Matrix[i].vertex);
            
        }
        else
        {
            printf("degree : %d // vertex : %d ", Matrix[i].degree, Matrix[i].vertex);
            
        }

        printf("\n");
    }
}

Adj_Matrix *Initialize_Matrix(char *File)
{
    int N_rows, N_cols, N_ones;
    int vertex;
    // abre a strnam para o arquivo desejado
    FILE *file = fopen(File, "r");

    if (file == NULL)
    {
        printf("NO SUCH FILE\n");
        return 0;
    }

    char *line_buffer = (char *)malloc(sizeof(char) * Line_max);

    // ignorando o header e pegando a segunda linha

    fscanf(file, "%*s %*s %*s %*s %*s %d %d %d ", &N_rows, &N_cols, &N_ones);

    // printf("%d %d %d\n",N_rows ,N_cols,N_ones);

    Adj_Matrix *Matrix = (Adj_Matrix *)malloc(N_rows * sizeof(Adj_Matrix));

    for (int i = 0; i < N_rows; i++)
    {
        Matrix[i].vertex = i + 1; // cada cabeca tera um numero correspondendo ao vertice
        // para possibilitar a ordenacao por grau no vertice
    }

    Vertex_Cell *previus = (Vertex_Cell *)malloc(sizeof(Vertex_Cell));
    
    for (int i = 0; i < N_ones + 1; i++)
    {
        Vertex_Cell *aux = (Vertex_Cell *)malloc(sizeof(Vertex_Cell));
      
        fscanf(file, "%d %d", &aux->adj, &vertex);
 
        
        // printf("%d %d ", aux->adj , vertex);
        // printf("\n");
        if (Matrix[vertex - 1].head == NULL)
        {
            Matrix[vertex - 1].degree++;
            Matrix[vertex - 1].head = aux;
            previus = aux;
        }
        else
        {
            Matrix[vertex - 1].degree++;
            previus->next = aux;
            previus = aux;
        }
        //aux->adj_head = Matrix[aux->adj-1].head;  
    }
    for (int i = 0; i < N_ones + 1; i++)
    {
        Vertex_Cell * aux =(Vertex_Cell *)malloc(sizeof(Vertex_Cell));
        aux =  Matrix[i].head;
        while(aux->next != NULL)
         {
             
             aux->adj_head = Matrix[aux->adj-1].head;
             aux = aux->next;

         }
            aux->adj_head = Matrix[aux->adj-1].head;
         
      
        
    }
    // print_matrix(Row,N_rows,N_cols);
    return Matrix;
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



int Number_of_adjacency(FILE *File)
{
    FILE *file = fopen(File, "r");

    int n;

    fscanf(file, "%*s %*s %*s %*s %*s %*d %*d %*d", &n);

    // printf("%d",n);Vertex_Degree
    fclose(file);
    return n;
}
int Number_of_vertex(FILE *File)
{
    FILE *file = fopen(File, "r");

    int n;

    fscanf(file, "%*s %*s %*s %*s %*s %d", &n);

    // printf("%d",n);
    fclose(file);
    return n;
}


Solution * Gulosinho(int N_vertex,Adj_Matrix * Matrix )
{
   int * Dominant = (int*)malloc(N_vertex * sizeof(int));
   int * Complement = (int*)malloc(N_vertex * sizeof(int));
   int D_counter = 0,C_counter = 0;
   Vertex_Cell *aux ;

   int j = N_vertex-1;
   //adicionar vertices desconexos a solução
   while(Matrix[j].head ==NULL)
   {
     Dominant[C_counter]= j;
     D_counter++;
     j--;
   }
   
   //optei nao utilizar listas encadeadas devido a perda de tempo com alocacao de memoria dinamica ja que a otimizacao de custo
   //de memoria nao importa apenas enficinecia de tempo
   for (int i = 0 ;i < N_vertex ; i++ )
   {
       if(Matrix[i].head != NULL)
       {

         
         printf("dominant vertex: %d \n",Matrix[i].vertex);
         Dominant[D_counter] = Matrix[i].vertex  ;//adiciona o vertice ao conjunto dos dominantes
         
         D_counter++;
         
         printf("neighborhood \n");
         if (Matrix[i].head != NULL)
         {
         aux = Matrix[i].head ;
        
         while(aux->next != NULL)
         {
             
             printf("%d ",aux->adj);
             Complement[C_counter] = aux->adj;
             aux->adj_head = NULL;
             C_counter++;
             aux = aux->next;

         }
            printf("%d ",aux->adj);
             Complement[C_counter] = aux->adj;
             aux->adj_head= NULL;
             C_counter++;
         }
        
           printf("\n");
        // printf("\n Matrix state : \n");
        // print_matrix(Matrix,N_vertex);
       }
      
     
  
   }
       Solution * solution = (Solution*)malloc(sizeof(solution));
       solution->C = Complement;
       solution->D = Dominant;
       solution->N_complements = C_counter;
       solution->N_dominants = D_counter;
       solution->N_vertex = N_vertex;
       solution->V = Matrix;
   
   return solution;
   
}

int main()
{

    clock_t begin = clock();

     char *file_name = "text_matrix";
     //char* file_name = "frb30-15-1.mtx";
     //char* file_name = "frb100-40.txt";
    Adj_Matrix *Matrix = Initialize_Matrix(file_name);
    
    int N_adjs = Number_of_adjacency(file_name);
    int N_vertex = Number_of_vertex(file_name);

    

    printf("Unsorted\n");

    print_matrix(Matrix, N_vertex);

    printf("Sorted\n");
    // Insertion_sort(Matrix, 0, N_vertex-1);
    CocktailSort(Matrix ,N_vertex);
    //Tim_sort(Matrix,N_vertex);
    print_matrix(Matrix, N_vertex);
    //print_matrix_degree_only(Matrix, N_vertex);

       

    printf("Solution:\n");
    
    Solution * solution = Gulosinho(N_vertex, Matrix);
    printf("Dominant set:\n");

    for(int i =  0 ;i < solution->N_dominants ;i++)
    {
        printf(" %d ",solution->D[i]);
    }

    printf("Complement:\n");

    for(int i =  0 ;i < solution->N_complements ;i++)
    {
        printf(" %d ", solution->C[i]);
    }   
 
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Executed in : %f s\n", time_spent);
    return 0;
}