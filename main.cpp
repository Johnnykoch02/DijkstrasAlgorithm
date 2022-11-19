#include "Graph.hpp"

struct EdgeStruct { std::string a; std::string b; unsigned long w; };

#include <vector>
#include <string>
#include <tuple>
#include <iostream>

int main() {
    Graph g;

    
  std::vector<std::string> vertices1 { "1", "2", "3", "4", "5", "6" };
  std::vector<EdgeStruct> edges1 {
    {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
    {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9},
  };

  std::vector<std::string> vertices2 { 
    "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
  };
  std::vector<EdgeStruct> edges2 {
    {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
    {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
    {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
  };

  std::vector<std::string> vertices3 { 
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
  };
  std::vector<EdgeStruct> edges3 {
    {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1}, 
    {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1}, 
    {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}
  };
                          
    for (const auto label : vertices1) {
        std::cout << label << std::endl;
        g.addVertex(label);
    }
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path;
    std::cout <<"Path 1 to 5:" << g.shortestPath("1", "5", path) <<std::endl;
    for (const auto &e : path) std::cout <<" to " <<e <<std::endl;
    path.clear();

    std::cout <<"Path 3 to 6:" << g.shortestPath("3", "6", path) << std::endl;
    for (const auto &e : path) std::cout <<" to " <<e <<std::endl;
    std::cout <<"Path 5 to 12:" <<g.shortestPath("5", "2", path) << std::endl;
    for (const auto &e : path) std::cout <<" to " <<e <<std::endl;
    path.clear();


}