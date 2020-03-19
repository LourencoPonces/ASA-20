#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Scc;

class Student {
    private:
        int id;
        int grade;
        bool visited;
        vector<Student*> friends;
        Scc* myScc;

    
        int d;
        int low;

    public:
        Student(int id, int grade){
            this->id = id;
            this->grade = grade;
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

        void setGrade(int newGrade){
            if (newGrade > grade) grade = newGrade;
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



void tarjanVisit(vector<Student>* students, Student* u, vector<Student*>* stack, int* visited, vector<Scc*>* sccGroup, Student* parent){
    u->setD(*visited);
    u->setLow(*visited);
    stack->push_back(u);
    *visited = *visited + 1;
    vector<Scc*> scc; 

    bool isInStack;
    //cout << "Student: " << u->getId() << endl;

    

    for (size_t i = 0; i < u->getNFriends(); i++){
        isInStack = false;
        //cout << "Friend: " << u->getFriends()[i]->getId() << endl;

        //cout << "Student " << u->getId() << " atualizou no primeiro if para " << u->getFriends()[i]->getGrade() << endl;
        u->setGrade(u->getFriends()[i]->getGrade());
        //Reduzir na procura da stack
        //Criar outro vetor que guarda so boleans
        for (size_t j = 0; j < stack->size(); j++){
            if ((*stack)[j]->getId() == u->getFriends()[i]->getId())
                isInStack = true;
        }
        if (u->getFriends()[i]->getD() == -1 || isInStack){
            //cout << "Entra if 1" << endl;
            if (u->getFriends()[i]->getD() == -1){
                //cout << "Entra if 2" << endl;
                tarjanVisit(students, u->getFriends()[i], stack, visited, sccGroup, u);
            }
            u->setLow(min(u->getLow(), u->getFriends()[i]->getLow()));
            //cout << "Student " << u->getId() << " atualizou low: " << u->getLow() << endl;

        }
    }
    //  cout << "Student " << u->getId() << " stack: " << endl;
    //  for (size_t i = 0; i < stack->size(); i++){
    //     //cout << (*stack)[i]->getId() << " ";
    //  }
    //  cout << endl;
    
    Student* v;
    if (u->getD() == u->getLow()){
        //cout << "Entra if 3" << endl;
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
            //cout << "-----------------Student: " << (*students)[i].getId() << endl;
            tarjanVisit(students, &(*students)[i], &stack, &visited, &sccGroup, 0);
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
        cout << students[i].getGrade() << endl;
    }

    return 0;
}
