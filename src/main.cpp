#include "graph.h"
#include "menu.h"

#include <iostream>

int main(int argc, const char* argv[]){
    std::string mode = std::string(argv[1]);

    int nodes;
    std::cout << "nodes> ";
    std::cin >> nodes;
    std::cout << nodes << std::endl;

    while(nodes < 1){
        std::cout << "Number of nodes must be greater than 0" << std::endl;
        std::cout << "nodes> ";
        std::cin >> nodes;
        std::cout << nodes << std::endl;
    }
    
    Graph graph = Graph(nodes);

    if (mode == "--hamilton") {
        int saturation;
        std::cout << "saturation> ";
        std::cin >> saturation;
        std::cout << saturation << std::endl;

        while(saturation != 30 && saturation != 70){
            std::cout << "Saturation must be 30 or 10" << std::endl;
            std::cout << "saturation> ";
            std::cin >> saturation;
            std::cout << saturation << std::endl;
        }

        float saturationRatio = saturation/100.0;
        graph.createHamilton(nodes, saturationRatio);
    } else if (mode == "--non-hamilton") { 
        graph.createNonHamilton(nodes);
    } else {
        std::cout << "Invalid mode" << std::endl;
        return 1;
    }

    menu(&graph);

    return 0;
}
