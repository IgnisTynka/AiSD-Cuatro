#pragma once

#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <fstream>

class Graph {
public:
    Graph(int nodes): _nodes(nodes), _list(std::vector<std::set<int>>(nodes)){}

    void createHamilton(int nodes, float saturation);
    void createNonHamilton(int nodes);

    void print();
    void exportToTikz();

    std::vector<int> hamiltonPath();
    std::vector<int> eulerPath();

protected:
    int _nodes;
    std::vector<std::set<int>> _list;

private:
    // void shuffle(std::vector<int> &v);
    bool _isConnected();
    bool _hamiltonPath(std::vector<int> &path, std::vector<bool> &visited, int startNode);
    void _eulerPath(std::vector<std::set<int>> &list, std::vector<int> &path, std::vector<int> &visited);
};
