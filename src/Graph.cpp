#include "../include/Graph.hpp"
#include "../include/Path.hpp"
#include "../include/HeapQueue.hpp"

/**
 * @brief This method is used to insert a new Vertex.
 * I will only do so if the ID is not already taken.
 * @param label ID of the vertex
 */
void Graph::addVertex(std::string label) {
    GraphNode * temp = this->getVertex(label);
    if(temp == nullptr) {
        this->nodes[label] = new GraphNode(label);
    }
}



/**
 * @brief Removes a vertex from the graph, and removes all references to it.
 * Also removes the pointer from Memory.
 * @param label 
 */
void Graph::removeVertex(std::string label) {
    GraphNode * temp = this->getVertex(label);
    if (temp != nullptr) {
        for (auto it = temp->edges.begin(); it != temp->edges.end(); ++it) {
            GraphNode* other = it->second->to;
            if (other!= nullptr) {
                other->edges[label] = nullptr;
                other->edges.erase(label);
            }
        }
        this->nodes[label] = nullptr;
        this->nodes.erase(label);
        delete temp;
    }
}
/**
 * @brief Method ensures both Nodes exist and then links them together.
 * 
 * @param label1 ID of node a
 * @param label2 ID of node b
 * @param weight weight of their connection
 */
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    GraphNode* a = getVertex(label1);
    GraphNode* b = getVertex(label2);

    if (a!= nullptr && b!= nullptr) {
        this->createLink(a, b, weight);
    }
}

/**
 * @brief Removes a link from the graph
 * 
 * @param label1 of Node a
 * @param label2 of Node b
 */
void Graph::removeEdge(std::string label1, std::string label2) {
    GraphNode* a = getVertex(label1);
    GraphNode* b = getVertex(label2);
    if (a!= nullptr && b!= nullptr) {
        a->edges[b->id] = nullptr;
        b->edges[a->id] = nullptr;
        a->edges.erase(b->id);
        b->edges.erase(a->id);
    }
}


unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    GraphNode* startingNode = this->getVertex(startLabel);
    GraphNode* endingNode = this->getVertex(endLabel);
    /* node does not exist in list */
    if (startingNode == nullptr || endingNode == nullptr) return INFINITY; 

    HeapQueue<Path*, Path::PathComparer> paths;
    std::map<std::string, unsigned long> dijkstraKey;
    for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it) {
        if (it->first != startLabel) {
            dijkstraKey[it->first] = INFINITY;
        }
    }
    dijkstraKey[startLabel] = 0;
    paths.insert(new Path(startingNode));
    while (paths.min()->current()->id != endLabel) {
        Path* shortestPath = paths.min(); /*Potential Memory LEak?*/
        paths.removeMin();
        for (auto const& [currID, currLink]: shortestPath->pathsFrom()) {
            if (! shortestPath->nodeVisited(currID) ) {
                Path* newLocation = new Path(*shortestPath);
                newLocation->visit(currLink->to);
                unsigned long previousDistance = dijkstraKey.find(currID)->second;
                dijkstraKey[currID] = MIN(previousDistance, newLocation->pathWeight());
                /* Dont Revisit old nodes*/
                paths.insert(newLocation);
            }
        }/* Needs Dijkstras keys to be updated along the way */
    }
    Path* finalPath = paths.min();
    paths.removeMin();
    path = finalPath->toString();
    return finalPath->pathWeight();
}

/**
 * @brief Destroy the Graph:: Graph object
 * 
 */
Graph::~Graph() {
    for (auto it = this->nodes.begin(); it!= this->nodes.end(); ++it) {
        GraphNode * temp = this->getVertex(it->first);
        if (temp != nullptr) {
            this->removeVertex(temp->id);
        }
    }   
}

/* Default Constructor */
Graph::Graph() {}
/* Private Helper Methods for Graph */
void Graph::createLink(GraphNode& a, GraphNode& b, unsigned long weight) {
  a.edges[b.id] = new GraphNode::Linkage(&b, weight);
  b.edges[a.id] = new GraphNode::Linkage(&a, weight);
}

void Graph::createLink(GraphNode* a, GraphNode* b, unsigned long weight) {
  Graph::createLink(*a, *b, weight);
}

GraphNode* Graph::getVertex(std::string label) {
  auto temp = this->nodes.find(label);
  if (temp == this->nodes.end()) {/* did not find it */
    return nullptr;
  }
  else return temp->second;
}