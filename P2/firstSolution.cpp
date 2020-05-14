#include <iostream>
#include <vector>

using namespace std;
class Crossing;

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

        bool setUsedA_B(bool state) { usedA_B = state; }

        bool getUsedB_A() { return usedB_A; }

        bool setUsedB_A(bool state) { usedB_A = state; }
};

class Crossing {
    private:
        int ave, str;
        bool person, store;
        vector<Edge*> edges;

    public:
        Crossing() {}

        Crossing(int _ave, int _str, int _maxAve, int _maxStr) {
            person = false;
            store = false;
            ave = _ave;
            str = _str;
        }
    
    int getAve() { return ave; }

    int getStr() { return str; }

    bool getPerson() { return person; }

    void setPerson() { person = true; }

    bool getStore() { return store; }

    void setStore() { store = true; }

    vector<Edge*> getEdges() { return edges; }

    void addEdge(Edge* edge) { edges.push_back(edge); }
};

int main() {
    int avenues, streets, stores, people, curStr, curAve;
    vector<Crossing> storesArr;
    vector<Crossing> peopleArr;

    cin >> avenues;
    cin >> streets;
    cin >> stores;
    cin >> people;

    Crossing crossings[streets][avenues];
    vector<Edge> edges;

    for (curAve = 0; curAve < avenues; curAve++) {
        for (curStr = 0; curStr < streets; curStr++) {
            crossings[curStr][curAve] = Crossing(curAve, curStr, avenues, streets);

            if ( curAve > 0) {
                edges.push_back(Edge(&crossings[curStr][curAve - 1], &crossings[curStr][curAve]));
                crossings[curStr][curAve - 1].addEdge(&edges.back());
                crossings[curStr][curAve].addEdge(&edges.back());
            }
            if (curStr > 0) {
                edges.push_back(Edge(&crossings[curStr - 1][curAve], &crossings[curStr][curAve]));
                crossings[curStr][curAve - 1].addEdge(&edges.back());
                crossings[curStr][curAve].addEdge(&edges.back());
            }
        }
    }

    for (int l = 0; l < crossings[0][0].getEdges().size(); l++){
     cout << endl << "(" 
        << crossings[0][0].getEdges().at(l)->getCrossA()->getAve() + 1 << ","
        << crossings[0][0].getEdges().at(l)->getCrossA()->getStr() + 1 << ") ("
        << crossings[0][0].getEdges().at(l)->getCrossB()->getAve() + 1 << ","
        << crossings[0][0].getEdges().at(l)->getCrossB()->getStr() + 1 << ")"
        << endl;
    }




    for (int i = 0; i < stores; i++) {
        cin >> curAve;
        cin >> curStr;
        crossings[curStr-1][curAve-1].setStore();
        storesArr.push_back(crossings[curStr-1][curAve-1]);
    }
    for (int i = 0; i < people; i++) {
        cin >> curAve; 
        cin >> curStr;
        crossings[curStr-1][curAve-1].setPerson();
        peopleArr.push_back(crossings[curStr-1][curAve-1]);
    }







    // Print Map
    cout << "Ave:" << avenues << endl;
    cout << "Str:" << streets << endl;
    cout << "Stores:" << stores << endl;
    cout << "People:" << people << endl << endl;

    Crossing currCross;
    vector<Edge*> currEdges; 
    for (int i = 0; i < avenues; i++) {
        for (int j = 0; j < streets; j++) {
            currCross = crossings[j][i];
            cout << "Ave: " << i + 1 << " Str: " << j + 1 << endl;
            cout << "Store: " << currCross.getStore() << endl;
            cout << "Person: " << currCross.getPerson() << endl;
            cout << "Edges with:" << endl;

            currEdges = currCross.getEdges();
            for (int k = 0; k < currEdges.size(); k++) {
                cout << "A: ("
                    << currEdges[k]->getCrossA()->getAve() + 1 << "," 
                    << currEdges[k]->getCrossA()->getStr() + 1 << ") ";
                cout << "B: ("
                    << currEdges[k]->getCrossB()->getAve() + 1 << "," 
                    << currEdges[k]->getCrossB()->getStr() + 1 << ")"
                    << endl;
            }
            cout << endl;
        } 
    }

    // Print Stores
    for (int i = 0; i < storesArr.size(); i++) {
        cout << "Ave: " << storesArr[i].getAve() + 1 << endl;
        cout << "Str: " << storesArr[i].getStr() + 1 << endl << endl;
    }

    // Print Edges for each Crossing
  

    return 0;
}