#pragma once

#include <iostream>
#include <vector>
#include <set>

class Graph {
public:
    Graph();
    ~Graph();

    void print();
    void createHamilton(int nodes, float saturation);
    void createNonHamilton(int nodes);
    std::vector<int> hamiltonPath();
    std::vector<int> eulerPath();

protected:
    int _nodes;
    std::vector<std::set<int>> _list;

private:
};
