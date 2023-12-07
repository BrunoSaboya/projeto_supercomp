#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <chrono>

std::vector<std::vector<int>> LerGrafo(const std::string& nomeArquivo, int& numVertices) {
    std::ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    std::vector<std::vector<int>> grafo(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;
    }

    arquivo.close();

    return grafo;
}

std::vector<int> EncontrarCliqueMaximaParallel(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::vector<int> cliqueMaxima;
    std::vector<int> grauDosVertices(numVertices, 0);

    #pragma omp parallel for
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            grauDosVertices[i] += grafo[i][j];
        }
    }

    while (!grauDosVertices.empty()) {
        int v = VérticeComMaiorGrau(grauDosVertices);
        std::vector<int> cliqueAtual = EncontrarClique(grafo, v);

        #pragma omp critical
        {
            if (cliqueAtual.size() > cliqueMaxima.size()) {
                cliqueMaxima = cliqueAtual;
            }
        }

        #pragma omp parallel for
        for (int i = 0; i < cliqueAtual.size(); ++i) {
            int u = cliqueAtual[i];

            #pragma omp parallel for
            for (int j = 0; j < grauDosVertices.size(); ++j) {
                if (grafo[u][j] == 1) {
                    #pragma omp critical
                    {
                        grauDosVertices[j]--;
                    }
                }
            }
            #pragma omp critical
            {
                grauDosVertices[u] = 0;
            }
        }
    }

    return cliqueMaxima;
}

int main() {
    std::string nomeArquivo = "grafo.txt";

    auto start_time = std::chrono::high_resolution_clock::now();

    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo(nomeArquivo, numVertices);

    std::vector<int> cliqueMaxima = EncontrarCliqueMaximaParallel(grafo, numVertices);

    std::cout << "Clique maxima encontrada: ";
    for (int v : cliqueMaxima) {
        std::cout << v + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}


/// Justificativa para as alterações:

/// Paralelização do Cálculo do Grau dos Vértices: A computação dos graus dos vértices é paralelizada para distribuir a carga de trabalho entre as threads.

/// Paralelização da Atualização do Grau dos Vértices: Durante a construção de cliques, a atualização dos graus dos vértices também é paralelizada para melhorar a eficiência.

/// Uso de Critical Section: As seções críticas são utilizadas para garantir que partes do código, como a comparação e a atualização da clique máxima, sejam executadas de forma atômica para evitar condições de corrida.