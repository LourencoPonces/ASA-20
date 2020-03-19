#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Scc;

class Student {
    private:
        int id;
        int grade;
        int maxGrade;
        bool visited;
        vector<Student*> friends;
        vector<Scc*> sccChildren;
        Scc* myScc;

    
        int d;
        int low;

    public:
        Student(int id, int grade){
            this->id = id;
            this->grade = grade;
            maxGrade = 0;
            visited = false;
            d = -1;
            low = -1;
        }

        int getD(){
            return d;
        }

        void setD(int d){
            this->d = d;
        }

         int getLow(){
            return low;
        }

        void setLow(int low){
            this->low = low;
        }


        int getId(){
            return id;
        }

        void setId(int id){
            this->id = id;
        }

        int getGrade(){
            return grade;
        }

        void setGrade(int grade){
            this->grade = grade;
            maxGrade = grade;
        }

        int getMaxGrade(){
            return maxGrade; 
        }

        void setMaxGrade(int maxGrade){
            this->maxGrade = maxGrade;
        }

        void addScc(Scc* newScc){
            sccChildren.push_back(newScc);
        }
        
        vector<Scc*> getScc(){
            return sccChildren;
        }

        size_t getNScc(){
            return sccChildren.size();
        }

        void setMyScc(Scc* myScc){
            this->myScc = myScc;
        }

        bool wasVisited(){
            return visited;
        }

        void setVisited(){
            visited = true;
        }

        void setNotVisited(){
            visited = false;
        }

        void addFriend(Student* newFriend){
            friends.push_back(newFriend);
        }

        vector<Student*> getFriends(){
            return friends;
        }

        size_t getNFriends(){
            return friends.size();
        }
};

class Scc {
    private:
    vector<Student*> members;
    int max;

    public:
    Scc(){
        max = -1;
    }

    int getMax(){
        return max;
    }

    void setMax(int newMax){
        max = newMax;
        updateGrades();
    }

    void addMember(Student* newStudent){
        members.push_back(newStudent);

        if (newStudent->getGrade() > max){
            max = newStudent->getGrade();
        }
    }

    vector<Student*> getMembers(){
        return members;
    }

    size_t getNMembers(){
        return members.size();
    }

    void updateGrades(){
        for (size_t i = 0; i < members.size(); i++){
            members[i]->setMaxGrade(max);
        }
    }
};



void tarjanVisit(vector<Student>* students, Student* u, vector<Student*>* stack, int* visited, vector<Scc*>* sccGroup){
    u->setD(*visited);
    u->setLow(*visited);
    stack->push_back(u);
    *visited = *visited + 1;
    vector<Scc*> scc; 
    bool isInStack = false;
    
    cout << endl << "Student: " << u->getId() << endl;
    for (size_t i = 0; i < u->getNFriends(); i++){
        cout << "Friend: " << u->getFriends()[i]->getId() << endl;
        isInStack = false;
        for (size_t j = 0; j < stack->size(); j++){
            if ((*stack)[j]->getId() == u->getFriends()[i]->getId())
                isInStack = true;
        }
        cout << "Esta na stack: " << isInStack << endl;
        if (u->getFriends()[i]->getD() == -1 || isInStack){
            cout << "Entra if 1" << endl;
            if (u->getFriends()[i]->getD() == -1){
                cout << "Entra if 2" << endl;
                tarjanVisit(students, u->getFriends()[i], stack, visited, sccGroup);
            }
            // cout << "Old low: " << u->getLow() << endl;
            // cout << "Low of Friend: " << u->getFriends()[i]->getId() << " : " << u->getFriends()[i]->getLow() << endl;
            // cout << "MIN: " << min(u->getLow(), u->getFriends()[i]->getLow()) << endl;
            //cout << "Old low " << u->getId() << " : " << u->getLow() << endl;
            u->setLow(min(u->getLow(), u->getFriends()[i]->getLow()));
            //cout << "New low " << u->getId() << " : " << u->getLow() << endl;
        }
    }
    // cout << "D: " << u->getD() << endl;
    // cout << "Low: " << u->getLow() << endl;
    
    Student* v;
    if (u->getD() == u->getLow()){
        cout << "Entrou if 3:" << u->getId() << endl;
        Scc* currScc = new Scc();
        
        cout << "Estamos no: " << u->getId() << endl;
        cout << "Novo Scc tem: " << currScc->getNMembers() << " membros" << endl;
        do {
            v = stack->back();
            stack->pop_back(); 
            cout << "adiciona a scc: " << v->getId() << endl;
            v->setMyScc(currScc);
            currScc->addMember(v);
            
        } while (u->getId() != v->getId());
        sccGroup->push_back(currScc);
        currScc->updateGrades();
        cout << "Novo Scc tem: " << currScc->getNMembers() << " membros" << endl;
        
    }
}

void sccTarjan(vector<Student>* students){
    int visited = 0;
    vector<Student*> stack;
    vector<Scc*> sccGroup;
    Scc currScc = Scc();

    for (size_t i = 0; i < students->size(); i++){
        cout << "-------------Student: " << (*students)[i].getId() << endl;
        if ((*students)[i].getD() == -1){
            tarjanVisit(students, &(*students)[i], &stack, &visited, &sccGroup);
        }
        cout << endl;
    }
    
    //Printing Scc Information
    cout << "Tamanho do group scc: " << sccGroup.size() << endl;
    for (size_t i = 0; i < sccGroup.size(); i++){
        cout << "Group " << i << endl;

        cout << "Numero de membros: " << sccGroup[i]->getNMembers()<< endl;
        cout << "Max: " << sccGroup[i]->getMax() << endl;
        for (size_t j = 0; j < sccGroup[i]->getNMembers(); j++){
            //vector<Student*>* aux = sccGroup[i]->getMembers();
            cout << sccGroup[i]->getMembers()[j]->getId() << " ";
        }
        cout << endl << endl;
    }

   
}

int main(){
    int nStudents, nRelations;
    char comma;
    cin >> nStudents;
    cin >> comma;
    cin >> nRelations;
    vector<Student> students;
    int grade;
    
    for (int i = 0; i < nStudents; i++){
        cin >> grade;
        Student newStudent = Student(i + 1, grade);
        students.push_back(newStudent);
    }

    int studentId;
    int newFriendId;
    Student* newFriend;
    for (int i = 0; i < nRelations; i++){
        cin >> studentId;
        cin >> newFriendId;

        newFriend = &students[newFriendId-1];
        students[studentId-1].addFriend(newFriend);
    }

    //Printing information
    // for (int i = 0; i < nStudents; i++){
    //     Student curr = students[i];
    //     int nFriends = curr.getNFriends();
        
    //     cout << "Student " << curr.getId() << endl;
    //     cout << "Grade " << curr.getGrade() << endl;
    //     cout << "Has " << nFriends << " friends:" << endl;
        
        
    //     vector<Student*> friends = curr.getFriends();
    //     for (int i = 0; i < nFriends; i++){
    //         cout << friends[i]->getId() << " ";
    //     } 
    //     cout << endl;
    //     cout << "D: " << curr.getD() << endl;
    //     cout << "Low: " << curr.getLow() << endl;
    //     cout << endl;
    // }

    sccTarjan(&students);
    
    for(int i = 0; i < nStudents; i++){
        cout << students[i].getMaxGrade() << endl;
    }

    return 0;
}
