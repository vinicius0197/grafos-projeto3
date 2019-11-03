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
    for(int j = 0; j < professor_graph.size(); j++) {
      for(int k = 0; k < professor_graph[j].intentions.size(); k++) {
        if(professor_graph[j].intentions[k] == i) {
          ListSchool school_list;
          school_list.school_id = i;
          school_list.projected_professors.push_back(j);
          projected_school_list.push_back(school_list);
        }
      }
    }
  }
}

/*
  Função principal que realiza o matching entre escolas e professores. Recebe os grafos
  de professores e escolas e retorna um objeto do tipo `Matching`.
*/
vector<Matching> matching(Graph professor_graph, GraphSchool school_graph) {
  vector<ListSchool> projected_school_list;
  projected_school_list = build_school_list(professor_graph, school_graph);

  for(int i = 0; i < projected_school_list.size(); i++) {
    cout << "Escola de número " << i << "\n";
    cout << "Possíveis professores: \n";
    for(int j = 0; j < projected_school_list[i].projected_professors.size(); j++) {
      cout << "Professor " << j <<"\n";
    }

    cout << "======\n";
  }

  // vector<Matching> provisional_matching; // o ID no vetor representa a escola, que é o mesmo que o atributo school_id
  // // Inicialmente, todos os professores estão livres. A quantidade de professores é o tamanho do professor_graph
  // while(professor_graph.size() > 0) {
  //   for(int i = 0; i < professor_graph.size(); i++) {
  //     Matching current_matching;
  //     current_matching = apply(i, professor_graph[i].intentions[0], 0);
  //   }
  // }

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