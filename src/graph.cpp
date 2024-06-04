#include "graph.h"

void Graph::print() {
    for (int i = 0; i < _nodes; i++) {
        std::cout << i + 1 << " -> ";
        for (int node : _list[i]) {
            std::cout << node + 1 << " ";
        }
        std::cout << std::endl;
    }
}
