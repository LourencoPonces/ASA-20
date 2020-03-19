#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Scc;

class Student {
    private:
        int id, grade, d, low;
        vector<Student*> friends;
        Scc* myScc;

    public:
        Student(int id, int grade){
            this->id = id;
            this->grade = grade;
            d = -1;
            low = -1;
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

        void setGrade(int newGrade){
            if (newGrade > grade) grade = newGrade;
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

        void setMyScc(Scc* myScc){
            this->myScc = myScc;
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
            int grade = newStudent->getGrade();
            if (grade > max){
                max = grade;
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
                members[i]->setGrade(max);
            }
        }
};



void tarjanVisit(vector<Student>* students, vector<Student*>* stack, Student* u,  Student* parent, int* visited, vector<Scc*>* sccGroup){
    u->setD(*visited);
    u->setLow(*visited);
    stack->push_back(u);
    *visited = *visited + 1;
    vector<Scc*> scc; 

    bool isInStack;
    for (size_t i = 0; i < u->getNFriends(); i++){
        isInStack = false;
        u->setGrade(u->getFriends()[i]->getGrade());
        for (size_t j = 0; j < stack->size(); j++){
            if ((*stack)[j]->getId() == u->getFriends()[i]->getId())
                isInStack = true;
        }
        if (u->getFriends()[i]->getD() == -1 || isInStack){
            if (u->getFriends()[i]->getD() == -1){
                tarjanVisit(students, stack, u->getFriends()[i], u, visited, sccGroup);
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
        currScc->updateGrades();
        if (parent != 0){
            parent->setGrade(currScc->getMax());
        }
    }
}

void sccTarjan(vector<Student>* students){
    int visited = 0;
    vector<Student*> stack;
    vector<Scc*> sccGroup;

    for (size_t i = 0; i < students->size(); i++){
        if ((*students)[i].getD() == -1){
            tarjanVisit(students, &stack, &(*students)[i], 0, &visited, &sccGroup);
        }
    }
}

int main(){
    int nStudents, nRelations, studentId, newFriendId, grade;
    char comma;
    vector<Student> students;
    
    cin >> nStudents;
    cin >> comma;
    cin >> nRelations;
    
    for (int i = 0; i < nStudents; i++){
        cin >> grade;
        Student newStudent = Student(i + 1, grade);
        students.push_back(newStudent);
    }

    Student* newFriend;
    for (int i = 0; i < nRelations; i++){
        cin >> studentId;
        cin >> newFriendId;

        newFriend = &students[newFriendId-1];
        students[studentId-1].addFriend(newFriend);
    }

    sccTarjan(&students);
    
    for(int i = 0; i < nStudents; i++){
        cout << students[i].getGrade() << endl;
    }

    return 0;
}
