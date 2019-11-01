#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>

using namespace std;

struct Vertex{
    int code;
    int weight;
    vector <int> adjacents;
};

struct distanceArray {
  int code;
  int distance;
  vector<int> path;
};