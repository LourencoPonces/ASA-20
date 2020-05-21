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


bool bfs( vector<Edge*> nodes[], vector<Edge*>* source, int* _before, int _nodesSize) {
    queue<int> queue;
    vector<Edge*> currNodeEdges;
    Edge* currEdge;
    int currNode, newNode;
        
    for (int i = 0; i < _nodesSize; i++) {
        _before[i] = -2;
    }
    
    for (int i = 0; i < source->size(); i++) {
        newNode = source->at(i)->getSink();
        _before[newNode] = -1;
        queue.push(newNode);
    }
    
    while (queue.size() != 0) {
        currNode = queue.front();
        queue.pop();

        currNodeEdges = nodes[currNode - 1];

        for (int i = 0; i < currNodeEdges.size(); i++) {
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

    vector<Edge*> nodes[nodesSize];

    int indexIn, indexOut, curAve, curStr;
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
            
            // In 
            newEdge = new Edge(indexIn, indexOut, 1);
            inEdges.push_back(newEdge);
            nodes[indexIn - 1] = inEdges;

            // Out 
            newEdge = new Edge(indexOut, indexIn, 1);
            outEdges.push_back(newEdge);

            if (up > 0 && up <= nodesSize) {
                newEdge = new Edge(indexOut, up, 1);
                outEdges.push_back(newEdge);
            }
            if (down > 0 && down <= nodesSize) {
                newEdge = new Edge(indexOut, down, 1);
                outEdges.push_back(newEdge);
            }
            if (right > 0 && right <= nodesSize && indexOut % (avenues * 2) != 0) {
                newEdge = new Edge(indexOut, right, 1);
                outEdges.push_back(newEdge);
            }
            if (left > 0 && left <= nodesSize && left % (avenues * 2) != 0) {
                newEdge = new Edge(indexOut, left, 1);
                outEdges.push_back(newEdge);
            }
            nodes[indexOut - 1] =  outEdges;
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
    


    
    bool existsPath  = true;
    int before[nodesSize];
    
    int maxFlow = 0;

    while (true) {
        if (!bfs(nodes, &source, before, nodesSize)) {
            break;
        }
        maxFlow++;

        cout << "maxFlow: " << maxFlow << endl;

        int currNode = 0;
        int previousNode = before[currNode];
        while (currNode != -1) {
            
            cout << "previousNode: " << previousNode << endl;

            if (previousNode == -1) {
                for (int i = 0; i < source.size(); i++) {
                    if (source.at(i)->getSink() == currNode) {
                        source.at(i)->setCap(0);
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < nodes[previousNode - 1].size(); i++) {
                    if (nodes[previousNode - 1].at(i)->getSink() == currNode) {
                        nodes[previousNode - 1].at(i)->setCap(0);
                        break;
                    }
                }
                for (int i = 0; i < nodes[currNode - 1].size(); i++) {
                    if (nodes[currNode - 1].at(i)->get) {

                    } 
                }
            }
            

            currNode = previousNode;
            previousNode = before[previousNode];
        }

        

    }

    


    // Prints
    cout << endl << endl;
    for (int i = 0; i < nodesSize; i++) {
        cout << i + 1 << ":";
        for (int j = 0; j < nodes[i].size(); j++) {
            cout << nodes[i].at(j)->getSink() << ",";
        }
        cout << endl;
    }

    return maxFlow;
}