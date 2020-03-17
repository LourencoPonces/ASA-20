#include <iostream>
#include <vector>

using namespace std;

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
            maxGrade = 0;
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

int algorithmRecursive(vector<Student>* students, Student* student){
    if (student->getMaxGrade() == 0){
        if (!student->wasVisited()){
            student->setVisited();
            for (size_t i = 0; i < student->getNFriends(); i++){; 
                if (student->getGrade() < algorithmRecursive(students, student->getFriends()[i])){
                    student->setGrade(student->getFriends()[i]->getGrade());
                }
            }
            student->setNotVisited();
        }
        return student->getGrade();
    }
    else {
        return student->getMaxGrade();
    }
}

void algorithm(vector<Student>* students){
    for (size_t i = 0; i < students->size(); i++){
       //Alteracao no max grade
       (*students)[i].setMaxGrade(algorithmRecursive(students, &(*students)[i]));
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
    //     cout << endl << endl;
    // }

    algorithm(&students);
    
    for(int i = 0; i < nStudents; i++){
        cout << students[i].getMaxGrade() << endl;
    }

    return 0;
}
