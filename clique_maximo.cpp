#include <iostream>
#include <fstream>
#include <vector>

// Função para ler o grafo a partir do arquivo de entrada
std::vector<std::vector<int>> LerGrafo(const std::string& nomeArquivo, int& numVertices) {
    std::ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    std::vector<std::vector<int>> grafo(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

// Função para encontrar a clique máxima em um grafo
std::vector<int> EncontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    for (int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;

        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);

            std::vector<int> novosCandidatos;

            for (int u : candidatos) {
                bool adjacenteATodos = true;

                for (int c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }

            candidatos = novosCandidatos;
        }
    }

    return cliqueMaxima;
}

int main() {
    // Nome do arquivo de entrada
    std::string nomeArquivo = "grafo.txt";

    // Leitura do grafo a partir do arquivo
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo(nomeArquivo, numVertices);

    // Encontrar a clique máxima
    std::vector<int> cliqueMaxima = EncontrarCliqueMaxima(grafo, numVertices);

    // Exibir a clique máxima encontrada
    std::cout << "Clique maxima encontrada: ";
    for (int v : cliqueMaxima) {
        std::cout << v + 1 << " ";  // +1 para ajustar os índices (começando em 1)
    }
    std::cout << std::endl;

    return 0;
}
