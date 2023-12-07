# Projeto SuperComp

Produzido por: Bruno Boldrim Saboya

Esse projeto tem como objetivo encontrar o Clique Maximo em um Grafo a partir de um input de texto por meio de 3 abordagens.

A primeira abordagem será a exaustiva: A exaustão é uma abordagem que seleciona iterativamente os vértices para formar um clique, geralmente começando com um vértice e adicionando outros que tenham o maior número de vizinhos já na clique.

A segunda abordagem será a Implementação com Threads OpenMP: A implementação de uma solução com OpenMP para encontrar cliques em um grafo usando a heurística gulosa envolve a paralelização das iterações do algoritmo em diferentes threads. O OpenMP simplifica a criação de threads e a coordenação entre elas.

E por fim, a última abordagem será Paralelização e Distribuição do Processamento com MPI. Onde nesta implementação, deve-se o problema em várias partes e distribuí-las para diferentes processadores usando a biblioteca MPI (Message Passing Interface). Cada processador será responsável por encontrar cliques em uma parte do grafo, e os resultados serão combinados no final para encontrar todas as cliques no grafo.
