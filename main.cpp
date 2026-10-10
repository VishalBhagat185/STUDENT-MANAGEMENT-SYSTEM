

// ========== STUDENT MANAGEMENT SYSTEM ==========

// 1. Add Student
// 2. Search Student
// 3. Update Student
// 4. Delete Student
// 5. Display All Students
// 0. Exit

// Enter your choice: 1

// Enter Student ID: 101
// Enter Name: Rahul
// Enter Age: 22

// Student added successfully!

// ==========  ==========


#include <bits/stdc++.h>
using namespace std;

// 1. Student model
class Student {
private:
    int id;
    string name;
    int age;

public:
    Student(int id, string name, int age)
        : id(id), name(name), age(age) {}

    int getId() const {
        return id;
    }

    void update(string newName, int newAge) {
        name = newName;
        age = newAge;
    }

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age << '\n';
    }
};

// 2. Repository: manages storage
class StudentRepository {
private:
    unordered_map<int, Student> students;

public:
    bool addStudent(int id, string name, int age) {
        if (students.find(id) != students.end())
            return false;

        students.emplace(
            piecewise_construct,
            forward_as_tuple(id),
            forward_as_tuple(id, name, age)
        );
        return true;
    }

    Student* findStudent(int id) {
        auto it = students.find(id);

        if (it == students.end())
            return nullptr;

        return &it->second;
    }

    bool deleteStudent(int id) {
        return students.erase(id) > 0;
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No students found.\n";
            return;
        }

        for (const auto& entry : students)
            entry.second.display();
    }
};

// 3. Service: application operations
class StudentService {
private:
    StudentRepository repository;

public:
    void addStudent() {
        int id, age;
        string name;

        cout << "Enter ID: ";
        cin >> id;

        cout << "Enter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Age: ";
        cin >> age;

        if (age < 0) {
            cout << "Invalid age.\n";
            return;
        }

        if (repository.addStudent(id, name, age))
            cout << "Student added successfully!\n";
        else
            cout << "Student ID already exists.\n";
    }

    void searchStudent() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        Student* student = repository.findStudent(id);

        if (student)
            student->display();
        else
            cout << "Student not found.\n";
    }

    void updateStudent() {
        int id, age;
        string name;

        cout << "Enter ID: ";
        cin >> id;

        Student* student = repository.findStudent(id);

        if (!student) {
            cout << "Student not found.\n";
            return;
        }

        cout << "Enter new name: ";
        getline(cin >> ws, name);

        cout << "Enter new age: ";
        cin >> age;

        if (age < 0) {
            cout << "Invalid age.\n";
            return;
        }

        student->update(name, age);
        cout << "Student updated successfully!\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        if (repository.deleteStudent(id))
            cout << "Student deleted successfully!\n";
        else
            cout << "Student not found.\n";
    }

    void displayAll() {
        repository.displayAll();
    }
};

// 4. Main application
int main() {
    StudentService service;
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT =====\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Display All\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        switch (choice) {
            case 1: service.addStudent(); break;
            case 2: service.searchStudent(); break;
            case 3: service.updateStudent(); break;
            case 4: service.deleteStudent(); break;
            case 5: service.displayAll(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
