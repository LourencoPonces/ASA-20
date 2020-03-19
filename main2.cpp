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

        Scc* getMyScc(){
            return myScc;
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



void tarjanVisit(vector<Student>* students, Student* u, vector<Student*>* stack, int* visited, vector<Scc*>* sccGroup, vector<Student*>* parents, Student* parent){
    u->setD(*visited);
    u->setLow(*visited);
    stack->push_back(u);
    *visited = *visited + 1;
    vector<Scc*> scc; 
    bool isInStack = false;
    
    for (size_t i = 0; i < u->getNFriends(); i++){
        isInStack = false;
        for (size_t j = 0; j < stack->size(); j++){
            if ((*stack)[j]->getId() == u->getFriends()[i]->getId())
                isInStack = true;
        }
        if (u->getFriends()[i]->getD() == -1 || isInStack){
            if (u->getFriends()[i]->getD() == -1){
                tarjanVisit(students, u->getFriends()[i], stack, visited, sccGroup, parents, u);
            }
            u->setLow(min(u->getLow(), u->getFriends()[i]->getLow()));

        }
    }
    
    Student* v;
    if (u->getD() == u->getLow()){
        Scc* currScc = new Scc();
        
        do {
            v = stack->back();
            stack->pop_back(); 
            v->setMyScc(currScc);
            currScc->addMember(v);
            
        } while (u->getId() != v->getId());
        if (parent != 0){
            parents->push_back(parent);
            parent->addScc(currScc);
        }

        sccGroup->push_back(currScc);
        currScc->updateGrades();
        
    }
}

void sccTarjan(vector<Student>* students){
    int visited = 0;
    vector<Student*> stack;
    vector<Scc*> sccGroup;
    Scc currScc = Scc();
    vector<Student*> parents;


    for (size_t i = 0; i < students->size(); i++){
        if ((*students)[i].getD() == -1){
            tarjanVisit(students, &(*students)[i], &stack, &visited, &sccGroup, &parents, 0);
        }
    }
    
    //Printing Scc Information
    // cout << "Tamanho do group scc: " << sccGroup.size() << endl;
    // for (size_t i = 0; i < sccGroup.size(); i++){
    //     cout << "Group " << i << endl;
    //     cout << "Numero de membros: " << sccGroup[i]->getNMembers()<< endl;
    //     cout << "Max: " << sccGroup[i]->getMax() << endl;
    //     for (size_t j = 0; j < sccGroup[i]->getNMembers(); j++){
    //         cout << sccGroup[i]->getMembers()[j]->getId() << " ";
    //     }
    //     cout << endl << endl;
    // }
    


    for (size_t i = 0; i < parents.size(); i++){
        for (size_t j = 0; j < parents[i]->getNScc(); j++){
            if (parents[i]->getMaxGrade() < parents[i]->getScc()[j]->getMax()){
                parents[i]->getMyScc()->setMax(parents[i]->getScc()[j]->getMax());
            }
        }
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
