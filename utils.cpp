#include <bits/stdc++.h> 
#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include "graph.h"

using namespace std;


vector<int> split(string input_string) {

  string buf;
  stringstream ss(input_string);
  vector<int> tokens;

  while (ss >> buf){
      tokens.push_back(stoi(buf));
  }
  return tokens;
}

void replaceLine(string &linha){

    std::replace(linha.begin(), linha.end(), '(', ' ');
    std::replace(linha.begin(), linha.end(), ')', ' ');
    std::replace(linha.begin(), linha.end(), ',', ' ');
    std::replace(linha.begin(), linha.end(), ':', ' ');
    std::replace(linha.begin(), linha.end(), 'E', ' ');

}