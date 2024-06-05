#include "graph.h"

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <iterator>

void Graph::createHamilton(int nodes, float saturation) {
    _nodes = nodes;
    _list.resize(_nodes);

    std::vector<int> nodesList = std::vector<int>(_nodes);
    for (int i = 0; i < _nodes; i++) {
        nodesList[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(nodesList.begin(), nodesList.end(), rng);

    for (int i = 0; i < _nodes-1; i++) {
        _list[nodesList[i]].insert(nodesList[i+1]);
        _list[nodesList[i+1]].insert(nodesList[i]);
    }
    _list[nodesList[_nodes-1]].insert(nodesList[0]);
    _list[nodesList[0]].insert(nodesList[_nodes-1]);

}

void Graph::createNonHamilton(int nodes) {
    float saturation = 0.5;
}

void Graph::print() {
    for (int i = 0; i < _nodes; i++) {
        std::cout << i + 1 << " -> ";
        for (int node : _list[i]) {
            std::cout << node + 1 << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> Graph::hamiltonPath() {
    std::vector<int> path;
    std::vector<bool> visited = std::vector<bool>(_nodes, false);


    return path;
}

std::vector<int> Graph::eulerPath() {
    std::vector<std::set<int>> list = _list;
    std::vector<int> path;
    std::vector<int> visited;
    visited.push_back(0);

    if (!_isConnected()) {
        return path;
    }

    for (int i = 0; i < _nodes; i++) {
        if (list[i].size() % 2 != 0) {
            return path;
        }
    }

    _eulerPath(list, path, visited);

    return path;
    
}

bool Graph::_isConnected() {
    std::vector<int> visited = std::vector<int>(_nodes, 0);
    std::stack<int> stack;

    for (int i = 0; i < _nodes; i++) {
        if (_list[i].size() > 0) {
            stack.push(i);
            visited[i] = 1;
            break;
        }
    }

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        for (int neighbor : _list[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                stack.push(neighbor);
            }
        }
    }

    for (int i = 0; i < _nodes; i++) {
        if (!visited[i] && _list[i].size() > 0) {
            return false;
        }
    }

    return true;
}

void Graph::_eulerPath(std::vector<std::set<int>> &list, std::vector<int> &path, std::vector<int> &visited) {
    while (!visited.empty()) {
        int node = visited.back();
        if (list[node].empty()) {
            path.push_back(node);
            visited.pop_back();
        }else{
            int nextNode = *list[node].begin();
            list[node].erase(nextNode);
            list[nextNode].erase(node);
            visited.push_back(nextNode);
        }
        _eulerPath(list, path, visited);
    }
}