// Vinícius Costa e Silva - 15/0052138
// Diego Vaz Fernandes - 16/0117925

#include<bits/stdc++.h> 
#include "graph.h"
#include "map"
#include "iostream"

using namespace std;
map<int, string> codXmap;

vector<string> split(string input_string) {
  string buf;
  stringstream ss(input_string);
  vector<string> tokens;

  while (ss >> buf){
      tokens.push_back(buf);
  }
  return tokens;
}

// TODO: refatorar para ler o novo arquivo
Graph read_and_init_graph(Graph graph) {
  
  string linha;
  int element1, element2, peso;
  ifstream arquivo ("input.txt"); // ifstream = padrão ios:in
  
  if (arquivo.is_open())
  {
    while (!arquivo.eof()){ //enquanto end of file for false continua
      getline (arquivo, linha);
      vector<string> tokens = split(linha);
      element1 = stoi(tokens[0]);
      element2 = stoi(tokens[1]);
      peso = stoi(tokens[2]);
      graph = add_edge(graph, element1, element2, peso);
    }
    arquivo.close();
    return graph;
  }
  else cout << "Não foi possivel abrir o arquivo"; 
}

int main() {
  // TODO
}