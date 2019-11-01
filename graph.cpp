/*
  Funções de apoio para o programa principal.
*/

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "map"
#include "structures.h"
#include <algorithm>


using namespace std;

typedef vector <Vertex> Graph;

int findIndex(Graph graph, int origem){
  int tamGraph = graph.size();
  if(tamGraph != 0){
    for(int i=0; i<tamGraph; i++){
      if(graph[i].code == origem){
        return i;
      }
    }
  }
  return -1;
}

/*
  Recebe um grafo e dois vértices +
  (int) e adiciona
  uma aresta entre eles.
*/
Graph add_edge(Graph graph, int origem, int destino , int weight) {
  int contem = findIndex(graph, origem);
  if(contem != -1){
    graph[contem].adjacents.push_back(destino);
  } else {
    Vertex vertex;
    vertex.code = origem;
    vertex.weight = weight;
    vertex.adjacents.push_back(destino);
    graph.push_back(vertex);
  }
  return graph;
}
/*
  Mostra a lista de de adjacências do grafo.
*/
void display_graph(Graph graph) {
  for(int i = 0; i < graph.size(); i++) {
    cout << "adjacentes do vertice " << graph[i].code << "  com peso = "<< graph[i].weight <<endl;
    for(int j = 0; j < graph[i].adjacents.size(); j++) {
      cout <<"     " << graph[i].adjacents[j] << endl;
    }
    cout << "                "<< endl << endl;
  }
}

bool contains(distanceArray path, int value) {
  if(std::find(path.path.begin(), path.path.end(), value) != path.path.end()) {
    return true;
  } else {
    return false;
  }
}