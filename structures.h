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

struct VertexSchool{
    //0 representa a primeira vaga e 1 a segunda. O valor detro representa a qualificação minima necessária
    vector <int> vacancy;
};

struct Matching {
    int school_id;
    vector <int> teacher_id;
};

#endif