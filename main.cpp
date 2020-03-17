#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//class Student(int id, int grade);
class Student {
    private:
        int id;
        int grade;
        int maxGrade;
        bool visited;
        vector<Student*> friends;

    public:
        Student(int id, int grade){
            this->id = id;
            this->grade = grade;
            maxGrade = grade;
            visited = false;
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

        bool wasVisited(){
            return visited;
        }

        void setVisited(){
            visited = true;
        }


        void addFriend(Student* newFriend){
            friends.push_back(newFriend);
        }

        vector<Student*> getFriends(){
            return friends;
        }

        int getNFriends(){
            return friends.size();
        }

};

int algorithm(vector<Student>* students, Student* student){
    
    // cout << "Entrou em: " << student->getId() << endl;
    
    if (!student->wasVisited()){
        // cout << "Numero de Amigos: " << student->getNFriends() << endl;
        // cout << "Nota: " <<student->getMaxGrade() << endl;
        
        student->setVisited();
        
        for (int i = 0; i < student->getNFriends(); i++){;
            //cout << "Numero de amigos do amigo: " << student->getFriends()[i]->getNFriends() << endl << endl;
            
            if (student->getMaxGrade() < algorithm(students, student->getFriends()[i])){
                // cout << "Mudou em: " << student.getId() << endl;
                // cout << "Amigo: " << student.getFriends()[i].getId() << endl << endl;
                student->setMaxGrade(student->getFriends()[i]->getMaxGrade());
            }
        }
    }
    // cout << "Student " << student->getId() << " retornou nota " << student->getMaxGrade() << endl << endl;
    return student->getMaxGrade();
}

int main(){
    int nStudents, nRelations;
    
    //Input
    ifstream input("input");
    char comma;
    input >> nStudents;
    input >> comma;
    input >> nRelations;
    //cout << "There are " << nStudents << " students, and " << nRelations << " relations" << endl << endl;

    //Adding Students
    vector<Student> students;
    int grade;
    for (int i = 0; i < nStudents; i++){
        input >> grade;
        Student newStudent = Student(i + 1, grade);
        students.push_back(newStudent);
    }

    //Adding Friends
    int studentId;
    int newFriendId;

    Student* newFriend;
    for (int i = 0; i < nRelations; i++){
        input >> studentId;
        input >> newFriendId;

        newFriend = &students[newFriendId-1];
        students[studentId-1].addFriend(newFriend);

        //students[studentId-1].addFriend(students[newFriendId-1]);
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
    //     cout << endl << endl;
    // }

    algorithm(&students, &students[0]);
    
    //cout << endl;

    //Output
    ofstream output("output");

    //cout << "Output: " << endl;
    int currGrade;
    for(int i = 0; i < nStudents; i++){
        currGrade = students[i].getMaxGrade();
        //cout << currGrade << endl;
        output << currGrade << endl;
    }

    return 0;
}

