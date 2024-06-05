#pragma once

#include <vector>
#include <set>
#include <stack>

class Graph {
public:
    Graph(int nodes): _nodes(nodes), _list(std::vector<std::set<int>>(nodes)){}

    void createHamilton(int nodes, float saturation);
    void createNonHamilton(int nodes);

    void print();
    
    std::vector<int> hamiltonPath();
    std::vector<int> eulerPath();

protected:
    int _nodes;
    std::vector<std::set<int>> _list;

private:
    bool _isConnected();
    void _eulerPath(std::vector<std::set<int>> &list, std::vector<int> &path, std::vector<int> &visited);
};
