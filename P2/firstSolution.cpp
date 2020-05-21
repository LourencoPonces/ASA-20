#include <iostream>
#include <queue>
#include <vector>

using namespace std;
class Edge;

class Crossing {
    private:
        int ave, str;
        bool person, store, used, sink;
        vector<Edge*> edges;

    public:
        Crossing() {}

        Crossing(bool _sink) { 
            ave = -1;
            str = -1;
            person = false;
            store = false;
            used = false;
            sink = _sink; 
        }

        Crossing(int _ave, int _str, int _maxAve, int _maxStr) {
            ave = _ave;
            str = _str;
            person = false;
            store = false;
            used = false;
            sink = false;
        }
    
    int getAve() { return ave; }

    int getStr() { return str; }

    bool getPerson() { return person; }

    void setPerson() { person = true; }

    bool getStore() { return store; }

    void setStore() { store = true; }

    bool getUsed() { return used; }

    void setUsed(){ used = true; }

    bool isSink() { return sink; }

    vector<Edge*> getEdges() { return edges; }

    void addEdge(Edge* edge) { edges.push_back(edge); }
};

class Edge {
    private:
        Crossing* crossA;
        Crossing* crossB;
        bool usedA_B, usedB_A;

    public:
        Edge() {}

        Edge(Crossing* _crossA, Crossing* _crossB) {
            crossA = _crossA;
            crossB = _crossB;
            usedA_B = false;
            usedB_A = false;
        }

        Crossing* getCrossA() { return crossA; }

        Crossing* getCrossB() { return crossB; }

        bool getUsedA_B() { return usedA_B; }

        bool setUsedA_B() { 
            usedA_B = true; 
            usedB_A = false;
        }

        bool getUsedB_A() { return usedB_A; }

        bool setUsedB_A() { 
            usedB_A = true; 
            usedA_B = false;
        }

        bool cmpCrossA(Crossing* cross) { 
            return crossA->getAve() == cross->getAve() &&
                    crossA->getStr() == cross->getStr();
        }
};

// class Path {
//     private:
//     vector<*Edge> edges;

//     public:
//     Path() {

//     }

//     void addEdge(Edge* edge) { edges.push_back(edge); }


// };


// int callDFS(Crossing* source) {

//     return -1;
// }

// int DFS() {
//     return -1;
// }













int main() {
    int avenues, streets, stores, people, curStr, curAve;
    vector<Crossing*> peopleArr;
    vector<Crossing*> storesArr;

    cin >> avenues;
    cin >> streets;
    cin >> stores;
    cin >> people;

    Edge edges[2*avenues*streets-avenues-streets+stores+people];
    int curEdge = 0;
    Crossing crossings[streets][avenues];

    for (curStr = 0; curStr < streets; curStr++) {
        for (curAve = 0; curAve < avenues; curAve++) {
            crossings[curStr][curAve] = Crossing(curAve, curStr, avenues, streets);
            if (curAve > 0) {
                edges[curEdge] = Edge(&crossings[curStr][curAve - 1], &crossings[curStr][curAve]);
                crossings[curStr][curAve - 1].addEdge(&edges[curEdge]);
                crossings[curStr][curAve].addEdge(&edges[curEdge]);
                curEdge++;
            }
            if (curStr > 0) {
                edges[curEdge] = Edge(&crossings[curStr - 1][curAve], &crossings[curStr][curAve]);
                crossings[curStr - 1][curAve].addEdge(&edges[curEdge]);
                crossings[curStr][curAve].addEdge(&edges[curEdge]);
                curEdge++;
            }
        }
    }


    for (int i = 0; i < stores; i++) {
        cin >> curAve;
        cin >> curStr;
        crossings[curStr-1][curAve-1].setStore();
        storesArr.push_back(&crossings[curStr-1][curAve-1]);
    }
    for (int i = 0; i < people; i++) {
        cin >> curAve; 
        cin >> curStr;
        crossings[curStr-1][curAve-1].setPerson();
        peopleArr.push_back(&crossings[curStr-1][curAve-1]);
    }


    Crossing superSource = Crossing(false);
    Crossing superSink = Crossing(true);

    for (int curPer = 0; curPer < people; curPer++) {
        edges[curEdge] = Edge(&superSource, peopleArr[curPer]);
        superSource.addEdge(&edges[curEdge]);
        curEdge++;
    }

    for (int curSto = 0; curSto < stores; curSto++) {
        edges[curEdge] = Edge(storesArr[curSto], &superSink);
        superSink.addEdge(&edges[curEdge]);
        curEdge++;
    }

    


    // Solving the problem

    // DFS

    vector<Crossing*> crosses;
    crosses.push_back(&superSource);

    Crossing* curCross;
    vector<Edge*> curEdges;

    while (crosses.size() > 0) {
        curCross = crosses.back();
        crosses.pop_back();

        curEdges = curCross->getEdges();
        
        for (int edge = 0; edge < curEdges.size(); edge++) {
            if (curEdges[edge]->cmpCrossA(curCross)) {
                if (!curEdges[edge]->getUsedA_B() && !curEdges[edge]->getCrossB()->getUsed()) {
                    crosses.push_back(curEdges[edge]->getCrossB());
                }
            }
            else {
                if (curEdges[edge]->getUsedA_B()) {
                    queue.push(curEdges[edge]->getCrossA());
                }
            }
        }
    }


    // Recurive
    //callDFS(&superSource);


    // BFS
    // queue<Crossing*> queue; 
    // queue.push(&superSource);
    // Crossing* curCross;
    // vector<Edge*> curEdges;
    // int result = 0;
 
    // while (queue.size() != 0) {
    //     curCross = queue.front();
    //     queue.pop();

    //     curEdges = curCross->getEdges();

    //     if (curCross->isSink()) {
    //         result++;
    //     }
    //     else {
    //         for (int edge = 0; edge < curEdges.size(); edge++) {
    //             if (curEdges[edge]->cmpCrossA(curCross)) {
    //                 if (!curEdges[edge]->getUsedA_B()) {
    //                     //curEdges[edge]->setUsedA_B();
    //                     queue.push(curEdges[edge]->getCrossB());
    //                 }
    //             }
    //             else {
    //                 if (curEdges[edge]->getUsedA_B()) {
    //                     queue.push(curEdges[edge]->getCrossA());
    //                 }
    //             }
                    
    //         }
    //     }
    // }

    cout << result << endl;

    // // Print Map
    // cout << "Ave:" << avenues << endl;
    // cout << "Str:" << streets << endl;
    // cout << "Stores:" << stores << endl;
    // cout << "People:" << people << endl << endl;

    // Crossing currCross;
    // vector<Edge*> currEdges; 
    // for (int curStr = 0; curStr < streets; curStr++) {
    //     for (int curAve = 0; curAve < avenues; curAve++) {
    //         currCross = crossings[curStr][curAve];
    //         cout << "Ave: " << curAve + 1 << " Str: " << curStr + 1 << endl;
    //         cout << "Store: " << currCross.getStore() << endl;
    //         cout << "Person: " << currCross.getPerson() << endl;
    //         cout << "Edges with" << endl;

    //         currEdges = currCross.getEdges();
    //         for (int edge = 0; edge < currEdges.size(); edge++) {
    //             cout << "A: ("
    //                 << currEdges[edge]->getCrossA()->getAve() + 1 << "," 
    //                 << currEdges[edge]->getCrossA()->getStr() + 1 << ") ";
    //             cout << "B: ("
    //                 << currEdges[edge]->getCrossB()->getAve() + 1 << "," 
    //                 << currEdges[edge]->getCrossB()->getStr() + 1 << ")"
    //                 << endl;
    //         }
    //         cout << endl;
    //     } 
    // }

    // // Print People
    // cout << endl << "People: " << endl;
    // for (int i = 0; i < storesArr.size(); i++) {
    //     cout << "Ave: " << peopleArr[i]->getAve() + 1 << " Str: " << peopleArr[i]->getStr() + 1 << endl << endl;
    // }

    // // Print Stores
    //  cout << endl << "Stores: " << endl;
    // for (int i = 0; i < storesArr.size(); i++) {
    //     cout << "Ave: " << storesArr[i]->getAve() + 1 << " Str: " << storesArr[i]->getStr() + 1 << endl << endl;
    // }

    // // Print edges of super source
    // cout << endl << "Source edges: " << endl;
    // for (int i = 0; i < superSource.getEdges().size(); i++){
    //     Edge curEdge = *superSource.getEdges()[i];
    //     cout << "A: " << curEdge.getCrossA()->getAve() + 1 << ":" << curEdge.getCrossA()->getStr() + 1 << endl;
    //     cout << "B: " << curEdge.getCrossB()->getAve() + 1 << ":" << curEdge.getCrossB()->getStr() + 1 << endl << endl;
    // }

    // // Print edges of super sink
    //  cout << endl << "Sink edges: " << endl;
    //  for (int i = 0; i < superSink.getEdges().size(); i++){
    //     Edge curEdge = *superSink.getEdges()[i];
    //     cout << "A: " << curEdge.getCrossA()->getAve() + 1 << ":" << curEdge.getCrossA()->getStr() + 1 << endl;
    //     cout << "B: " << curEdge.getCrossB()->getAve() + 1 << ":" << curEdge.getCrossB()->getStr() + 1 << endl << endl;
    // }

    return 0;
}