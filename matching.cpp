#include <bits/stdc++.h> 
#include "structures.h"
#include "graph.h"
#include <algorithm>

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

bool check_professor_intentions(vector<FreeProfessor> free_professores) {

  for(int i  = 0; i < free_professores.size(); i++) {

    if(!free_professores[i].alocated && !free_professores[i].esgotou_intentions) {
      return true;
    }
  }

  return false;
}

/*
  Entrada:
    professor_id -> id do professor aplicando para aquela escola
    school_id -> id da escola para onde o professor está aplicando

  Retorno:
    retorna um objeto do tipo `Matching`
*/
Matching apply(int professor_id, int school_id) {
  Matching matching;
  matching.school_id = school_id;
  matching.professors_id.push_back(professor_id);
  return matching;
}

int check_worst_candidate(Matching current_matching, GraphSchool school_graph, Graph professor_graph) {
  int worst_candidate = current_matching.professors_id[0];

  for(int i = 0; i < current_matching.professors_id.size(); i++) {
    worst_candidate = current_matching.professors_id[i];

    if(professor_graph[current_matching.professors_id[i]].qualification < professor_graph[worst_candidate].qualification ) {
      worst_candidate = current_matching.professors_id[i];
    }
  }

  return worst_candidate;
}

/*
  Deleta a escola school_id das listas de preferências dos professores cujas qualificações
  sejam menores do que as qualificações do pior candidato para aquela vaga.
*/
void del(Graph &professor_graph, int worst_candidate_score, int school_id) {
  // cout << "PARA A ESCOLA " << school_id << "\n";
  for(int i = 0; i < professor_graph.size(); i++) {
    for(int j = 0; j < professor_graph[i].intentions.size(); j++) {
      if(professor_graph[i].intentions[j] == school_id) {
        if(professor_graph[i].qualification <= worst_candidate_score) {
          // cout << "Escola de número " << school_id << "\n";
          // cout << "intenções antes: ";
          // for(int m = 0; m < professor_graph[i].intentions.size(); m++) {
          //   cout << professor_graph[i].intentions[m] << " ";
          // }
          // cout << "\n";
          professor_graph[i].intentions.erase(std::remove(professor_graph[i].intentions.begin(), \
            professor_graph[i].intentions.end(), school_id), professor_graph[i].intentions.end());

          // cout << "intenções depois: ";
          // for(int m = 0; m < professor_graph[i].intentions.size(); m++) {
          //   cout << professor_graph[i].intentions[m] << " ";
          // }
          // cout << "\n";
        }
      }
    }
  }
  // cout << "======== \n";
}

/*
  Função principal que realiza o matching entre escolas e professores. Recebe os grafos
  de professores e escolas e retorna um objeto do tipo `Matching`.
*/
void matching(Graph professor_graph, GraphSchool &school_graph) {
  
  vector<FreeProfessor> free_professores;

  for(int i = 0; i < 100; i++) {
    FreeProfessor professor;
    professor.professor_id = i;
    free_professores.push_back(professor);
  }
  while(check_professor_intentions(free_professores)){
      
      for(int i = 0; i < free_professores.size(); i++){
          bool prof_approved = false;
          if(!free_professores[i].esgotou_intentions && !free_professores[i].alocated){
            
            int index_graph_professor = free_professores[i].professor_id;
            int intention_actived = free_professores[i].count_intention;
            int qualification_professor = professor_graph[index_graph_professor].qualification;
            int index_graph_prof_alocated;

            //retorna o indice da escola da intenção atual do professor
            int school_intention = professor_graph[index_graph_professor].intentions[intention_actived] -1;
            

            for(int q = 0; q <school_graph[school_intention].vacancy.size() ; q++){
              if(!prof_approved){
                // cout <<"aproved" << endl;
                int vaga_qualification = school_graph[school_intention].vacancy[q].qualification;
                index_graph_prof_alocated = school_graph[school_intention].vacancy[q].teacher_alocated;
                //if para saber se o professor tem a qualificação necessária para a vaga
                if(qualification_professor >= vaga_qualification ){
                  // if para saber se a vaga esta ocupada : -1 representa que a vaga esta desocupada
                  if(index_graph_prof_alocated == -1){

                    school_graph[school_intention].vacancy[q].teacher_alocated = index_graph_professor;
                    prof_approved = true;

                  }else{
                    int qualification_prof_alocated = professor_graph[index_graph_prof_alocated].qualification;
                    if(qualification_professor == vaga_qualification){ /*condição para saber se ele merece mais a vaga que o outro professor alocado*/
                      
                      // if para saber se o professor tem exatamente a qualificação esperada pela vaga
                      if(qualification_prof_alocated == vaga_qualification){
                        // if para saber a prioridade de intenção de cada professor e fornecer a vaga para aquele que preferiu a vaga antes
                        if(free_professores[index_graph_professor].count_intention <= free_professores[index_graph_prof_alocated].count_intention){
                          
                          school_graph[school_intention].vacancy[q].teacher_alocated = index_graph_professor;
                          prof_approved = true;
                        }
                      }else{ /* caso não tenha exatamente a qualificação da vaga, o novo professor fica com a vaga*/
                        school_graph[school_intention].vacancy[q].teacher_alocated = index_graph_professor;
                        prof_approved = true;

                      }
                    }else if(qualification_prof_alocated == vaga_qualification){

                      prof_approved = false;
                      
                    }else if(free_professores[index_graph_professor].count_intention <= free_professores[index_graph_prof_alocated].count_intention){
                          
                      school_graph[school_intention].vacancy[q].teacher_alocated = index_graph_professor;
                      prof_approved = true;

                    }
                  }
                }
              }
              
            }


            if(prof_approved){
              if (index_graph_prof_alocated != -1){
                free_professores[index_graph_prof_alocated].alocated = false;
                free_professores[index_graph_prof_alocated].count_intention = free_professores[index_graph_prof_alocated].count_intention + 1;
                
                if(free_professores[index_graph_prof_alocated].count_intention >= professor_graph[index_graph_prof_alocated].intentions.size()){
                  free_professores[index_graph_prof_alocated].esgotou_intentions = true;
                }
              }

              free_professores[index_graph_professor].alocated = true;
            }else{
              free_professores[index_graph_professor].count_intention = free_professores[index_graph_professor].count_intention + 1;
              if(free_professores[index_graph_professor].count_intention >= professor_graph[index_graph_professor].intentions.size()){
                free_professores[index_graph_professor].esgotou_intentions = true;
              }
            }
          }
      }
  }
}


/*
  Função principal que realiza o matching entre escolas e professores. Recebe os grafos
  de professores e escolas e retorna um objeto do tipo `Matching`.
*/
// vector<Matching> matching(Graph professor_graph, GraphSchool school_graph) {
//   vector<ListSchool> projected_school_list;
//   vector<Matching> matching;
//   vector<int> free_professors;
//   for(int i = 0; i < 100; i++) {
//     free_professors.push_back(i+1);
//   }
//   // inicializar matching
//   for(int i = 0; i < school_graph.size(); i++) {
//     Matching match;
//     matching.push_back(match);
//   }
//   projected_school_list = build_school_list(professor_graph, school_graph);

//   // Função de DEBUG para ver como está a lista de professores nas filas das escolas
//   // for(int i = 0; i < projected_school_list.size(); i++) {
//   //   cout << "ESCOLA NUMERO " << i + 1 << "\n";
//   //   cout << "PROFESSORES NA FILA: \n";
//   //   for(int j = 0; j < projected_school_list[i].projected_professors.size(); j++) {
//   //     cout << "Professor " << projected_school_list[i].projected_professors[j] << "\n";
//   //   }
//   //   cout << "===== \n";
//   // }

//   while(free_professors.size() > 0 && check_professor_intentions(professor_graph)) {
//     for(int i = 0; i < free_professors.size(); i++) {
//       int index_graph_professor = free_professors[i] -1;
//       int current_school = professor_graph[index_graph_professor].intentions[0] -1;
//       // cout << "Professor " << i+1 << " aplicou para a escola " << professor_graph[i].intentions[0] << "\n";

//       matching[current_school].school_id = current_school + 1;
//       matching[current_school].professors_id.push_back(free_professors[i]);
//       free_professors.erase(std::remove(free_professors.begin(), free_professors.end(), free_professors[i]), free_professors.end());  

//       // professor_graph[i].intentions.erase(std::remove(professor_graph[i].intentions.begin(), \
//       //       professor_graph[i].intentions.end(), current_school + 1), professor_graph[i].intentions.end());

//       // escola tem mais candidatos aplicando do que vagas
//       if(matching[current_school].professors_id.size() > school_graph[current_school].vacancy.size()) {
//         int worst_candidate = check_worst_candidate(matching[current_school], school_graph, professor_graph);

//         // cout << "O pior candidato para a escola " << current_school << " é o professor " << worst_candidate << "\n";
//         matching[current_school].professors_id.erase(std::remove(matching[current_school].professors_id.begin(), \
//           matching[current_school].professors_id.end(), worst_candidate), matching[current_school].professors_id.end());

//         free_professors.push_back(worst_candidate);
//         professor_graph[worst_candidate].intentions.erase(std::remove(professor_graph[worst_candidate].intentions.begin(), \
//             professor_graph[worst_candidate].intentions.end(), current_school), professor_graph[worst_candidate].intentions.end());
//       }

//       // se a escola já está com as vagas cheias
//       // if(matching[current_school].professors_id.size() == school_graph[current_school].vacancy.size()) {
//       //   int worst_candidate = check_worst_candidate(matching[current_school], school_graph, professor_graph);

//       //   // exclui a escola atual das listas de preferências de todos os professores piores que o worst_candidate
//       //   // del(professor_graph, professor_graph[worst_candidate].qualification, current_school);
//       //   professor_graph[free_professors[i]].intentions.erase(std::remove(professor_graph[i].intentions.begin(), \
//       //       professor_graph[i].intentions.end(), current_school), professor_graph[i].intentions.end());
//       // }
//     }
//   }

//   return matching;
// }