#include <bits/stdc++.h> 
#include "structures.h"
#include "graph.h"

using namespace std;

/*
  Cria uma lista de candidatos possíveis para cada escola baseado nas preferências dos professores. O rankeamento
  será feito dentro do próprio algoritmo, considerando as qualificações.
*/
vector<ListSchool> build_school_list(Graph professor_graph, GraphSchool school_graph) {
  vector<ListSchool> projected_school_list;

  for(int i = 0; i < school_graph.size(); i++) {
    ListSchool school_list;
    vector<int> projected_professors;
    for(int j = 0; j < professor_graph.size(); j++) {
      for(int k = 0; k < professor_graph[j].intentions.size(); k++) {
        if(professor_graph[j].intentions[k]-1 == i) {
          projected_professors.push_back(j+1);
        }
      }
    }
    school_list.school_id = i;
    school_list.projected_professors = projected_professors;
    projected_school_list.push_back(school_list);
  }

  return projected_school_list;
}

/*
  Função principal que realiza o matching entre escolas e professores. Recebe os grafos
  de professores e escolas e retorna um objeto do tipo `Matching`.
*/
vector<Matching> matching(Graph professor_graph, GraphSchool school_graph) {
  vector<ListSchool> projected_school_list;
  vector<Matching> test;
  projected_school_list = build_school_list(professor_graph, school_graph);

  // Função de DEBUG para ver como está a lista de professores nas filas das escolas
  for(int i = 0; i < projected_school_list.size(); i++) {
    cout << "ESCOLA NUMERO " << i + 1 << "\n";
    cout << "PROFESSORES NA FILA: \n";
    for(int j = 0; j < projected_school_list[i].projected_professors.size(); j++) {
      cout << "Professor " << projected_school_list[i].projected_professors[j] << "\n";
    }
    cout << "===== \n";
  }


  // for(int i = 0; i < projected_school_list.size(); i++) {
  //   cout << "Escola de número " << i << "\n";
  //   cout << "Possíveis professores: \n";
  //   cout << projected_school_list[i].projected_professors.size() << "\n";
  //   // for(int j = 0; j < projected_school_list[i].projected_professors.size(); j++) {
  //   //   cout << "Professor " << j <<"\n";
  //   // }

  //   cout << "======\n";
  // }

  // vector<Matching> provisional_matching; // o ID no vetor representa a escola, que é o mesmo que o atributo school_id
  // // Inicialmente, todos os professores estão livres. A quantidade de professores é o tamanho do professor_graph
  // while(professor_graph.size() > 0) {
  //   for(int i = 0; i < professor_graph.size(); i++) {
  //     Matching current_matching;
  //     current_matching = apply(i, professor_graph[i].intentions[0], 0);
  //   }
  // }
  return test;
}

/*
  Entrada:
    professor_id -> id do professor aplicando para aquela escola
    school_id -> id da escola para onde o professor está aplicando
    vacancy_id -> id da vaga para a qual está aplicando (0 ou 1, para primeira ou segunda vaga)

  Retorno:
    retorna um objeto do tipo `Matching`
*/
Matching apply(int professor_id, int school_id, int vacancy_id) {
  Matching matching;
  matching.school_id = school_id;
  matching.professors_id.insert(matching.professors_id.begin() + vacancy_id, professor_id);
  return matching;
}