#ifndef PATH_H
#define PATH_H

#include "Deque.hpp"
#include "Graph.hpp"
#include <string>
#include <map>


class Path {
    private:
        Deque<GraphNode> path;
        size_t pWeight;
        std::vector<std::string> pPath;
    public:
        Path() {}
        ~Path() {
            path.Destroy();        
        }
        
        Path(GraphNode* start);

        Path(const Path& _ot);
        unsigned int size() const { return this->path.getLength(); }
        GraphNode* current() const {return this->path.peekRight();}
        size_t pathWeight() const {return this->pWeight;}
        void visit(GraphNode* next);

        bool nodeVisited(std::string id) {
            for (auto& str : this->pPath) {
                if (str == id) return true;
            }
            return false;
        }

        std::map<std::string, GraphNode::Linkage*> pathsFrom() const {
            return this->current()->edges;
        }

        std::vector<std::string> toString() const {return this->pPath;}
        
        class PathComparer {
            private:
            bool lt;
            public:
            PathComparer(bool lt = true) : lt(lt) {}
            bool operator()(const Path &p1, const Path &p2) const {
                return this->lt ? p1.pWeight < p2.pWeight : p1.pWeight >= p2.pWeight;
            }
            bool operator()(const Path* p1, const Path* p2) const {
                return operator()(*p1, *p2);
            }
        };
};

Path::Path(GraphNode* start) { 
    this->path.pushRight(start);
    this->pWeight = 0;
    this->pPath.push_back(start->id);
}


Path::Path(const Path& _ot) {
    this->path = Deque<GraphNode>(_ot.path);
    this->pWeight = _ot.pWeight;
    // for (Deque<GraphNode>::Iterator i = this->path.start(); i != nullptr; ++i) {
    //     this->pPath.push_back(i->id);
    // }
    Node<GraphNode>* pathPtr = this->path.start();
    if (this->path.getLength() == 1) this->pPath.push_back(this->path.start()->getData()->id);
    else while(pathPtr != nullptr) {
        this->pPath.push_back(pathPtr->getData()->id);
        pathPtr = pathPtr->next;
    }
}


void Path::visit(GraphNode* next) {
    GraphNode* lastVisited = this->current();
    if (lastVisited == nullptr) { /* Empty Path */
        path.pushRight(next);
        pPath.push_back(next->id);
        return;
    }
    /* Verifies this node to be in the last nodes connections */
    bool verified = false;
    size_t linkWeight = 0;
    auto refNext = lastVisited->edges.find(next->id);
    if (refNext != lastVisited->edges.end() && next != nullptr) {
        verified = true;
        linkWeight = refNext->second->weight;
    }
    
    if (verified) {
        path.pushRight(next);
        pPath.push_back(next->id);
        this->pWeight+=linkWeight;
    }
}

#endif