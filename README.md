# MIDS
### Dominância
- Em teoria dos grafos, um conjunto dominante para um grafo G = (V, E) é um subconjunto D de V de tal modo que cada vértice que não está em D é adjacente a pelo menos um membro de D. O número de dominação γ(G) é o número de vértices em um menor conjunto dominante de G.

- O problema do conjunto dominante refere-se a testar se γ(G) ≤ K para um dado grafo G e entrada K; É um clássico problema de decisão NP-completo em teoria de complexidade computacional (Garey & Johnson 1979). Portanto, acredita-se que não existe um algoritmo eficiente que encontre um menor conjunto dominante para um dado grafo.



### Dominância + independencia

- Conjuntos dominantes estão intimamente relacionados a conjuntos independentes: um conjunto independente é também um conjunto dominante se, e somente se, é um conjunto independente máximo, de modo que qualquer conjunto independente máximo em um grafo é necessariamente também um conjunto dominante mínimo. Assim, o menor conjunto independente máximo também é o menor conjunto dominante independente. O número de dominação independente i(G) de um grafo G é o tamanho do menor conjunto independente (ou, de forma equivalente, o tamanho do menor conjunto independente máximo).

- O conjunto dominante mínimo num grafo não será necessariamente independente, mas o tamanho do conjunto dominante mínimo é sempre inferior ou igual ao tamanho de um máximo conjunto independente mínimo, isto é, γ(G) ≤ i(G).

### Sobre este repositório :pushpin: 

- O objetivo final é superar o estado atual da arte , utilizando o um algoritimo guloso randomizado e para a busca local a Colonia de Formigas.
   >[Estado atual da arte](https://www.sciencedirect.com/science/article/abs/pii/S1568494619307306?fr=RR-2&ref=pdf_download&rr=7603ffebed1d00f2)
- read_file.c contém os algoritimos de ordenação utilizados, a leitura do arquivo ".txt", as estruturas de dado e a solução do problema MIDS.
- As matrizes utilizadas fazem parte de um grande repositório de dados (BHOSLIB)
   >[Repositório de grafos utilizados](https://networkrepository.com/bhoslib.php)
-  frb30-15-1.mtx(matriz de 400 vertices)
-  frb100-40.txt(matriz de 4000 vertices)
-  text_matrix(matriz de teste 10 vertices)   
  
### Pseudo Code
     
