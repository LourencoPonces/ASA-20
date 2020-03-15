#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//class Student(int id, int grade);
class Student {
    private:
        int id;
        int grade;
        vector<Student> friends;

    public:
        Student(){
            id = -1;
            grade = -1;
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
        }

        void addFriend(Student newFriend){
            friends.push_back(newFriend);
        }

        vector<Student> getFriends(){
            return friends;
        }

        int getNFriends(){
            friends.size();
        }

};

// class Friends {
//     private: 
//         Student student;
//         vector<Student> friends;
//         int nFriends;

//     public:
//         Friends(){
//             nFriends = 0;
//         }

//         void addFriend(Student newFriend){
//             friends.insert(newFriend);
//         }
// };

int main(){
    int nStudents, nRelations;
    
    //Input
    ifstream input("input");
    char comma;
    input >> nStudents;
    input >> comma;
    input >> nRelations;
    cout << "There are " << nStudents << " students, and " << nRelations << " relations" << endl << endl;

    Student students[nStudents];
    int grade;
    for (int i = 0; i < nStudents; i++){
        input >> grade;
        students[i].setId(i+1);
        students[i].setGrade(grade);

        cout << "Student: " << i + 1 << endl;
        cout << "Grade: " << grade << endl << endl;
    }

    int studentId;
    int newFriendId;
    for (int i = 0; i < nRelations; i++){
        input >> studentId;
        input >> newFriendId;
        students[studentId-1].addFriend(students[newFriendId-1]);
    }

    for (int i = 0; i < nStudents; i++){
        Student curr = students[i];
        int nFriends = curr.getNFriends();
        
        cout << "Student " << curr.getId() << " has " << nFriends << " friends:" << endl;
        
        vector<Student> friends = curr.getFriends();
        for (int i = 0; i < nFriends; i++){
            cout << friends[i].getId() << " ";
        } 
        cout << endl;
    }
    return 0;
}

