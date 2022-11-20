#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"

#include <vector>
#include <map>
#include <string>

#define INFINITY 0x3f3f3f3f
#define MIN(a,b) ((a) < (b) ? (a) : (b))

struct GraphNode {

  struct Linkage {
    unsigned long weight; /* Weighted Graph Implementation */
    GraphNode* to;
    Linkage(GraphNode* _to, const unsigned long& _weight) : weight(_weight) {
      this->to = _to;
    }
    Linkage(const Linkage& _link):  weight(_link.weight) {
      this->to = _link.to;
    }
    ~Linkage() {}
  };

  std::string id;
  /*Maps an ID to a Link */
  std::map<std::string, Linkage*> edges;

  GraphNode(std::string _id) : id(_id) {}
  GraphNode(const GraphNode& _node) : id(_node.id) {
    this->edges = _node.edges;
  }
};

class Graph : GraphBase {
  private:
  std::map<std::string, GraphNode*> nodes;
  GraphNode* getVertex(std::string label);
  public:
  Graph();
  ~Graph();
  static void createLink(GraphNode& a, GraphNode& b, unsigned long weight);
  static void createLink(GraphNode* a, GraphNode* b, unsigned long weight);
  void addVertex(std::string label);
  void removeVertex(std::string label);
  void addEdge(std::string label1, std::string label2, unsigned long weight);
  void removeEdge(std::string label1, std::string label2);
  unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};



#endif 