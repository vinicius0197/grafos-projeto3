// Vinícius Costa e Silva - 15/0052138
// Diego Vaz Fernandes - 16/0117925

#include  <bits/stdc++.h> 
// #include "graph.h"
#include "utils.h"
#include "map"
#include "iostream"
#include "matching.h"

using namespace std;

map<int, string> codXmap;
   
//  
void read_and_init_graph(Graph &graph, GraphSchool &graphSchool) {
  
  string linha;
  int element1, element2, peso;
  ifstream arquivo ("input.txt"); // ifstream = padrão ios:in
  
  if (arquivo.is_open()){
    int contador = 0;
    while (!arquivo.eof()){ //enquanto end of file for false continua
      //pega uma linha do arquivo e coloca na varialvel linha
      getline (arquivo, linha);

      if ((contador > 2) && (contador < 103)){
        
        Vertex vertex;
        replaceLine(linha);
        std::replace(linha.begin(), linha.end(), 'P', ' ');

        vector<int> teacher = split(linha);
        
        vertex.qualification = teacher[1];
        for (int i = 2; i<teacher.size(); i++){
          vertex.intentions.push_back(teacher[i]);
        }
        graph.push_back(vertex);
        // cada professor vai ser a sua posição correspondente -1  no vetor do grafo
      }else if(contador >105){
        
        VertexSchool vertexSchool;
        replaceLine(linha);
        vector<int> school = split(linha);

        for (int i = 1; i<school.size(); i++){
          vertexSchool.vacancy.push_back(school[i]);
        }
        graphSchool.push_back(vertexSchool);
      }
      contador ++;
    }
    arquivo.close();
  }
  else cout << "Não foi possivel abrir o arquivo"; 
}

int main() {
  Graph graphTeacher;
  GraphSchool graphSchool;
  vector<Matching> match;
  read_and_init_graph(graphTeacher, graphSchool);

  // display_graph(graphTeacher);
  // display_graph_school(graphSchool);
  match = matching(graphTeacher, graphSchool);

  for(int i = 0; i < match.size(); i++) {
    cout << "ESCOLA NÚMERO " << i << "\n";
    for(int j = 0; j < match[i].professors_id.size(); j++) {
      cout << "Professor " << match[i].professors_id[j] << " \n";
    }
    cout << "=====\n";
  }

  return 0;
}