#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Edge {
    private:
    int source, sink, cap;

    public:
    Edge() {}

    Edge(int _source, int _sink, int _cap) {
        source = _source;
        sink = _sink;
        cap = _cap;
    }

    int getSource() { return source; }
    
    int getSink() { return sink; }

    int getCap() { return cap; }

    void setCap(int _cap) { cap = _cap; }
};


bool bfs( vector<vector<Edge*>> nodes, vector<Edge*>* source, int* _before, int _nodesSize) {
    queue<int> queue;
    vector<Edge*> currNodeEdges;
    Edge* currEdge;
    int currNode, newNode;
        
    for (int i = 0; i < _nodesSize + 1; i++) {
        _before[i] = -2;
    }
    
    for (size_t i = 0; i < source->size(); i++) {
        currEdge = source->at(i);
        
        if (currEdge->getCap() != 0) {
            newNode = currEdge->getSink();
            _before[newNode] = -1;
            queue.push(newNode);
        }
    }
    
    while (queue.size() != 0) {
        currNode = queue.front();
        queue.pop();

        currNodeEdges = nodes[currNode - 1];
            
        for (size_t i = 0; i < currNodeEdges.size(); i++) {
            currEdge = currNodeEdges.at(i);

            if (currEdge->getCap() != 0) {
                newNode = currNodeEdges.at(i)->getSink(); 

                if (_before[newNode] == -2) {
                    _before[newNode] = currNode;
                    if (newNode == 0) {
                        return true;
                    }
                    queue.push(newNode);
                }
            
            }
        }
    }
    return false;
}


int main() {
    int avenues, streets, stores, people;

    cin >> avenues;
    cin >> streets;
    cin >> stores;
    cin >> people;

    int nodesSize = 2 * avenues * streets;

    vector<vector<Edge*>> nodes(nodesSize);


    int indexIn = -2, indexOut, curAve, curStr;
    for (curStr = 0; curStr < streets; curStr++) {
        for (curAve = 0; curAve < avenues; curAve++) {
            indexIn = 2 * (curStr * avenues + curAve) + 1;
            indexOut = indexIn + 1;

            int up = indexIn - (avenues * 2);
            int down = indexIn + (avenues * 2);
            int right = indexIn + 2;
            int left = indexIn - 2;

            vector<Edge*> inEdges;
            vector<Edge*> outEdges;
            Edge* newEdge;

            // Out 
            newEdge = new Edge(indexOut, indexIn, 0);
            nodes[indexOut - 1].push_back(newEdge);
            if (up > 0 && up <= nodesSize) {
                newEdge = new Edge(indexOut, up, 1);
                nodes[indexOut - 1].push_back(newEdge);
            }
            if (down > 0 && down <= nodesSize) {
                newEdge = new Edge(indexOut, down, 1);
                nodes[indexOut - 1].push_back(newEdge);
            }
            if (right > 0 && right <= nodesSize && indexOut % (avenues * 2) != 0) {
                newEdge = new Edge(indexOut, right, 1);
                nodes[indexOut - 1].push_back(newEdge);
            }
            if (left > 0 && left <= nodesSize && (left + 1) % (avenues * 2) != 0) {
                newEdge = new Edge(indexOut, left, 1);
                nodes[indexOut - 1].push_back(newEdge);
            }
            
            up++;
            down++;
            right++;
            left++;
            // In 
            newEdge = new Edge(indexIn, indexOut, 1);
            nodes[indexIn - 1].push_back(newEdge);
            if (up > 0 && up < nodesSize) {
                newEdge = new Edge(indexIn, up, 0);
                nodes[indexIn - 1].push_back(newEdge);
            }
            if (down > 0 && down < nodesSize) {
                newEdge = new Edge(indexIn, down, 0);
                nodes[indexIn - 1].push_back(newEdge);
            }
            if (right > 0 && right < nodesSize && (indexIn + 1) % (avenues * 2) != 0) {
                newEdge = new Edge(indexIn, right, 0);
                nodes[indexIn - 1].push_back(newEdge);
            }
            if (left > 0 && left < nodesSize && left % (avenues * 2) != 0) {
                newEdge = new Edge(indexIn, left, 0);
                nodes[indexIn - 1].push_back(newEdge);
            }

        }
    }
    
    vector<Edge*> source;

    for (int i = 0; i < stores; i++) {
        cin >> curAve;
        cin >> curStr;

        indexOut = 2 * ((curStr - 1) * avenues + curAve - 1) + 2;

        Edge* newEdge = new Edge(indexIn, 0, 1);
        nodes[indexOut - 1].push_back(newEdge); 
    }
    for (int i = 0; i < people; i++) {
        cin >> curAve; 
        cin >> curStr;

        indexIn = 2 * ((curStr  - 1)* avenues + curAve - 1) + 1;
        Edge* newEdge = new Edge(-1, indexIn, 1);
        source.push_back(newEdge);
    }


    int before[nodesSize + 1];
    int maxFlow = 0;

    while (true) {
        if (!bfs(nodes, &source, before, nodesSize)) {
            break;
        }

        maxFlow++;
        int currNode = 0;
        int previousNode = before[currNode];

        while (currNode != -1) {
            
            if (previousNode == -1) {
                for (size_t i = 0; i < source.size(); i++) {
                    if (source.at(i)->getSink() == currNode) {
                        source.at(i)->setCap(0);
                        break;
                    }
                }
                for (size_t i = 0; i < nodes[currNode - 1].size(); i++) {
                    if (nodes[currNode - 1].at(i)->getSink() == -1) {
                        nodes[currNode - 1].at(i)->setCap(1);
                    }
                }
            }
            else {
                for (auto edge: nodes[previousNode - 1]) {
                    if (edge->getSink() == currNode) {       
                        edge->setCap(0);
                    }
                }
                if (currNode != 0) {
                    for (auto edge: nodes[currNode - 1]) {
                        if (edge->getSink() == previousNode) {
                            edge->setCap(1);
                        }
                    }
                }
            }
            
            currNode = previousNode;
            previousNode = before[previousNode];
        }
    }

    


    // Prints
    // cout << endl << endl;
    // for (int i = 0; i < nodesSize; i++) {
    //     cout << i + 1 << ":";
    //     for (size_t j = 0; j < nodes[i].size(); j++) {
    //         cout << nodes[i].at(j)->getSink() << ",";
    //     }
    //     cout << endl;
    // }
    
    cout << maxFlow << endl;

    return 0;
}