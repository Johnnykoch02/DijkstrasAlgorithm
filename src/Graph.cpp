#include "../include/Graph.hpp"
#include "../include/Path.hpp"
#include "../include/HeapQueue.hpp"

/**
 * @brief This method is used to insert a new Vertex.
 * I will only do so if the ID is not already taken.
 * @param label ID of the vertex
 * Time Complexity: Map Find and Map Insertion == O(log(N)) where N is the number of vertices
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
 * @param label ID of the vertex
 * Time Complexity: 
* O(Log(N)) where N is the number of vertices in the graph
+  O(Edges(n)) Where Edges(n) is the numbers of links the Node n contains in the graph
+ O(Log(N)) where N is the number of vertices in the graph
Which is Equivalent to ==> the MAX of ( O(Log(N)) and O(Edges(n)) )
 */
void Graph::removeVertex(std::string label) {
    GraphNode * temp = this->getVertex(label);
    if (temp != nullptr) {
        for (auto it = temp->edges.begin(); it != temp->edges.end(); ++it) {
            GraphNode* other = it->second->to;
            if (other != nullptr) {
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
 * @param label1 ID of node a
 * @param label2 ID of node b
 * @param weight weight of their connection
 * Time Complexity: O(log(N)) where N is the number of nodes in the Graph
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
 * @param label1 of Node a
 * @param label2 of Node b
 * Time Complexity: O(Log(N)) where N is the number of nodes in the Graph
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

/**
 * @brief Standard Dijkstra's Algorithm Implementation for an Adjecency List Graph.
 * @param startLabel Beginning Node
 * @param endLabel Ending Node
 * @param path Corresponding to the correct Path
 * @return unsigned long Weight
 * Time Complexity: O (N + E * Log(E)) where N is the number of nodes in the graph, and E is the number of edges in the Graph
 */
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    GraphNode* startingNode = this->getVertex(startLabel);
    GraphNode* endingNode = this->getVertex(endLabel);
    /* node does not exist in list */
    if (startingNode == nullptr || endingNode == nullptr) return INFINITY; 

    HeapQueue<Path*, Path::PathComparer> paths;
    std::map<std::string, unsigned long> dijkstraKey;
    for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it) { /* O(N)*/
        if (it->first != startLabel) {
            dijkstraKey[it->first] = INFINITY;
        }
    }
    dijkstraKey[startLabel] = 0;
    paths.insert(new Path(startingNode));
    while (paths.min()->current()->id != endLabel) {
        Path* shortestPath = paths.min(); 
        paths.removeMin(); /* */
        for (auto const& [currID, currLink]: shortestPath->pathsFrom()) { /* Each Edge in the Current Visiting Node O(Edges) */ 
            if (! shortestPath->nodeVisited(currID) ) {/* Dont Revisit old nodes*/
                Path* newLocation = new Path(*shortestPath); /* Copy the old Path */
                newLocation->visit(currLink->to); /* ... And visit the new Node for that Path  */
                unsigned long previousDistance = dijkstraKey[currID];
                /* Update the key along the way, and add the node if weve found a shorter path to another node. */
                if (newLocation->pathWeight() < previousDistance ) {
                dijkstraKey[currID] = newLocation->pathWeight();
                paths.insert(newLocation); /* O(log(E))*/
                }
            }
        }
    }
    Path* finalPath = paths.min();
    paths.removeMin();
    path = finalPath->toString();
    return dijkstraKey[endLabel];
}

/**
 * @brief Destroy the Graph:: Graph object
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

/**
 * @brief Creates a new link between two Nodes in a Graph
 */
void Graph::createLink(GraphNode* a, GraphNode* b, unsigned long weight) {
  Graph::createLink(*a, *b, weight);
}

/**
 * @brief Returns nullptr or the Node corresponding to Label lable in the Graph.
 * 
 * @param label for the ID of the node
 * @return GraphNode* to the Node with corresponding ID
 * Time Complexity: O(log(N)) where N is the number of nodes in the graph ==> RB Tree Find Method
 */
GraphNode* Graph::getVertex(std::string label) {
  auto temp = this->nodes.find(label);
  if (temp == this->nodes.end()) {/* did not find it */
    return nullptr;
  }
  else return temp->second;
}