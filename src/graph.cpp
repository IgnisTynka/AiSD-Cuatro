#include "graph.h"

void Graph::createHamilton(int nodes, float saturation) {
    _nodes = nodes;
    _list.resize(_nodes);

    for (int i = 0; i < _nodes; i++) {
        _list[i].insert((i+1)%_nodes);
        _list[(i+1)%_nodes].insert(i);
        int j = i + 1;
        if (saturation == 0.f) {
            continue;
        }
        for (int k = j; k < _nodes-1; k++) {
            float p = (float)rand() / RAND_MAX;
            if (p <= saturation) {
                _list[i].insert(k);
                _list[k].insert(i);
            }
        }
    }
    
    for (int i = 0; i < _nodes; i++) {
        if (_list[i].size() % 2 != 0) {
            for (int j = i +1 ; j < _nodes; j++) {
                if(_list[i].find(j) == _list[i].end() && _list[j].size() % 2 != 0) {
                    _list[i].insert(j);
                    _list[j].insert(i);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < _nodes-1; i++) {
        if (_list[i].size() % 2 != 0) {
            _list[i].insert(_nodes-1);
            _list[_nodes-1].insert(i);
        }
    }
}

void Graph::createNonHamilton(int nodes) {
    float saturation = 0.5;
    _nodes = nodes;
    _list.resize(_nodes);  

    for (int i = 0; i < _nodes-1; i++) {
        _list[i].insert((i+1)%(_nodes-1));
        _list[(i+1)%(_nodes-1)].insert(i);
        int j = i + 1;
        if (saturation == 0.f) {
            continue;
        }
        for (int k = j; k < _nodes-1; k++) {
            float p = (float)rand() / RAND_MAX;
            if (p <= saturation) {
                _list[i].insert(k);
                _list[k].insert(i);
            }
        }
    }
    
    for (int i = 0; i < _nodes-1; i++) {
        if (_list[i].size() % 2 != 0) {
            for (int j = i +1 ; j < _nodes-1; j++) {
                if(_list[i].find(j) == _list[i].end() && _list[j].size() % 2 != 0) {
                    _list[i].insert(j);
                    _list[j].insert(i);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < _nodes-2; i++) {
        if (_list[i].size() % 2 != 0) {
            _list[i].insert(_nodes-2);
            _list[_nodes-2].insert(i);
        }
    } 
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

void Graph::exportToTikz() {
    std::cout << "Exporting to tikz..." << std::endl;
     std::fstream file("export/graph.tex", std::ios::out);

    if(!file.is_open()){
        std::cout << "Error opening file" << std::endl;
        return;
    }

    file << "\\begin{tikzpicture}" << std::endl;
    file << "\t[level distance=10mm," << std::endl;
    file << "\t>={Stealth[black]}," << std::endl;
    file << "\tevery node/.style={fill=blue!30,circle,inner sep=1pt, minimum size=8mm}," << std::endl;
    file << "\tevery edge/.style={draw=black!60,very thick}]" << std::endl;

    double radius = 3.0;
    for(int i = 0; i < _nodes; i++){
        double angle = 2 * 3.14 * i / _nodes;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        file << "\t\\node[shape=circle] (" << i + 1 << ") at (" << x << "," << y << ") {" << i + 1 << "};" << std::endl;
    }

    for(int i = 0; i < _nodes; i++){
        for(int j : _list[i]){
            file << "\t\\path [-](" << i + 1 << ") edge (" << j + 1 << ");" << std::endl;
        }
    }

    file << "\\end{tikzpicture}" << std::endl;   
    file.close();

    std::cout << "Exported to export/graph.tex" << std::endl;
}

std::vector<int> Graph::hamiltonPath() {
    std::vector<int> path;
    std::vector<bool> visited = std::vector<bool>(_nodes, false);

    if (!_hamiltonPath(path, visited, 0)) {
        path.clear();
    }

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

bool Graph::_hamiltonPath(std::vector<int> &path, std::vector<bool> &visited, int startNode) {
    visited[startNode] = true;
    path.push_back(startNode);

    for (int neighbor : _list[startNode]) {
        if (neighbor == path[0] && path.size() == _nodes) {
            path.push_back(neighbor);
            return true;
        }
        if (!visited[neighbor]) {
            if (_hamiltonPath(path, visited, neighbor)) {
                return true;
            }
        }
    }

    visited[startNode] = false;
    path.pop_back();
    return false;
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