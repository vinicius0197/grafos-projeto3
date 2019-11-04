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
typedef vector <VertexSchool> GraphSchool;

void display_graph(Graph graph) {
  for(int i = 0; i < graph.size(); i++) {
    cout << "qualificação do professor "<< i+1 <<": "<< graph[i].qualification <<endl;
    for(int j = 0; j < graph[i].intentions.size(); j++) {
      cout <<"  Intenção de prioridade "<< j+1 <<": " << graph[i].intentions[j] << endl;
    }
    cout << "                "<< endl << endl;
  }
}

void display_graph_school(GraphSchool graphSchool) {
  for(int i = 0; i < graphSchool.size(); i++) {
    cout << "Quantidade de vagas na escola " <<i+1 <<": "<< graphSchool[i].vacancy.size() <<endl;
    for(int j = 0; j < graphSchool[i].vacancy.size(); j++) {
      cout <<"  Qualificação da vaga "<< j+1 <<": " << graphSchool[i].vacancy[j].qualification << endl;
    }
    cout << "                "<< endl << endl;
  }

}