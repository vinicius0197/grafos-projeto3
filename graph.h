#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>
#include "structures.h"

using namespace std;

typedef vector <Vertex> Graph;

Graph init(int verttex, int weight);
Graph add_edge(Graph graph, int origem, int destino, int weight);
int findIndex(Graph graph, int origems);
void display_graph(Graph graph);
vector<int> find_all_vertex(Graph graph);

#endif