#include "functions.h"

#include <iostream>
#include <vector>

void menu(Graph* graph) {
    std::string option;

    while (true) {
        std::cout << "action> ";
        std::cin >> option;
        std::cout << option << std::endl;

        if (option == "help"){
            std::cout << "Commands:" << std::endl;
            std::cout << "help \t\t Show this message" << std::endl;
            std::cout << "print \t\t Print the graph" << std::endl;
            std::cout << "find_euler \t\t Check if euler path exist in graph" << std::endl;
            std::cout << "find_hamilton \t\t Check if hamilton path exist in graph" << std::endl;
            std::cout << "export \t\t Export the graph to tikz" << std::endl;
    }
        else if (option == "print") {
            graph->print();
        }
        else if (option == "find_euler") {
            std::vector<int> path = graph->eulerPath();
            if (path.size() == 0) {
                std::cout << "No euler path found" << std::endl;
            } else {
                std::cout << "Euler path found: ";
                for (int node : path) {
                    std::cout << node + 1 << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (option == "find_hamilton") {
            std::vector<int> path = graph->hamiltonPath();
            if (path.size() == 0) {
                std::cout << "No hamilton path found" << std::endl;
            } else {
                std::cout << "Hamilton path found: ";
                for (int node : path) {
                    std::cout << node + 1 << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (option == "export_tikz") {
            exportToTikz(graph);
        }
        else if (option == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}