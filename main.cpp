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
          VacancyInfo vacancy;
          vacancy.teacher_alocated = -1;
          vacancy.qualification=school[i];
          vertexSchool.vacancy.push_back(vacancy);
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
  matching(graphTeacher, graphSchool);
  

  for(int i = 0; i < graphSchool.size(); i++) {
    cout << "ESCOLA NÚMERO " << i + 1 << "\n";
    for(int j = 0; j < graphSchool[i].vacancy.size(); j++) {
      cout << "Professor alocado" << graphSchool[i].vacancy[j].teacher_alocated + 1<< " \n";
    }
    cout << "=====\n";
  }

  return 0;
}