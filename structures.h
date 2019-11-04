#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>

using namespace std;

struct Vertex{
    int qualification;
    vector <int> intentions;
};

struct VacancyInfo{

    int teacher_alocated;
    int qualification;
    /* data */
};

struct VertexSchool{
    //0 representa a primeira vaga e 1 a segunda. O valor detro representa a qualificação minima necessário
    vector <VacancyInfo> vacancy;
};



struct FreeProfessor{

    bool esgotou_intentions = false;
    int professor_id;
    int count_intention = 0;
    bool alocated = false;


};
struct Matching {
    int school_id;
    vector <int> professors_id;
};

struct ListSchool {
    int school_id;
    vector <int> projected_professors;
};

#endif