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
        vector<Student> friends;

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

        bool wasVisited(){
            return visited;
        }

        void setVisited(){
            visited = true;
        }

        void setMaxGrade(int maxGrade){
            this->maxGrade = maxGrade;
        }

        void addFriend(Student newFriend){
            friends.push_back(newFriend);
        }

        vector<Student> getFriends(){
            return friends;
        }

        int getNFriends(){
            return friends.size();
        }

};

// int algorithm(vector<Student> &students, Student &student){
//    cout << "Entrou em: " << student.getId() << endl;
//     if (student.wasVisited()){   
//         return student.getMaxGrade();
//     }
//     else {
//         cout << "Numero de Amigos: " << student.getNFriends() << endl;
//         cout << "Nota: " <<student.getMaxGrade() << endl;
//         student.setVisited();
//         for (int i = 0; i < student.getNFriends(); i++){;
//             cout << "Numero de amigos do amigo: " << student.getFriends()[i].getNFriends() << endl << endl;
            
//             if (student.getMaxGrade() < algorithm(students, student.getFriends()[i])){
//                 cout << "Mudou em: " << student.getId() << endl;
//                 cout << "Amigo: " << student.getFriends()[i].getId() << endl << endl;
//                 student.setMaxGrade(student.getFriends()[i].getMaxGrade());
//             }
//         }
//     }
// }

// void algorithm(vector<Student> &students){
//     for (int i = 0; i < students.size(); i++){
//         Student& curr = students[i];
//         for (int j = 0; j < curr.getNFriends(); j++){
//             if (curr.getFriends()[j].getMaxGrade() > curr.getMaxGrade()){
//                 curr.setMaxGrade(curr.getFriends()[j].getMaxGrade());
//             }

//         }
//     }
// }

int main(){
    int nStudents, nRelations;
    
    //Input
    ifstream input("input");
    char comma;
    input >> nStudents;
    input >> comma;
    input >> nRelations;
    cout << "There are " << nStudents << " students, and " << nRelations << " relations" << endl << endl;

    vector<Student> students;
    int grade;
    for (int i = 0; i < nStudents; i++){
        input >> grade;
        Student newStudent = Student(i + 1, grade);
        students.push_back(newStudent);
    }

    int studentId;
    int newFriendId;
    for (int i = 0; i < nRelations; i++){
        input >> studentId;
        input >> newFriendId;
        students[studentId-1].addFriend(students[newFriendId-1]);
    }

    // for (int i = 0; i < nStudents; i++){
    //     Student curr = students[i];
    //     int nFriends = curr.getNFriends();
        
    //     cout << "Student " << curr.getId() << endl;
    //     cout << "Grade " << curr.getGrade() << endl;
    //     cout << "Has " << nFriends << " friends:" << endl;
        
    //     vector<Student>* friends = curr.getFriends();
    //     for (int i = 0; i < nFriends; i++){
    //         cout << friends[i].getId() << " ";
    //     } 
    //     cout << endl << endl;
    // }

    //algorithm(students, students[0]);
    

    cout << "Output: " << endl;
    for(int i = 0; i < nStudents; i++){
        cout << students[i].getMaxGrade() << endl;
    }

    return 0;
}

