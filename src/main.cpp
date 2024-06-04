#include "graph.h"
#include "functions.h"

#include <iostream>

int main(int argc, const char* argv[]){

    std::string mode = std::string(argv[1]);
    Graph* graph;

    if (mode == "--hamilton") {
        int nodes;
        float saturation;
        std::cout << "Enter the number of nodes: ";
        std::cin >> nodes;
        std::cout << nodes << std::endl;
        std::cout << "Enter the saturation: ";
        std::cin >> saturation;
        std::cout << saturation << std::endl;
        graph->createHamilton(nodes, saturation);
    } else if (mode == "--non-hamilton") { 
        int nodes;
        std::cout << "Enter the number of nodes: ";
        std::cin >> nodes;
        std::cout << nodes << std::endl;
        graph->createNonHamilton(nodes);
    } else {
        std::cout << "Invalid mode" << std::endl;
        return 1;
    }

    menu(graph);

    return 0;
}
