#include "StudentList.h"

// Constructor
StudentList::StudentList() {
    head = nullptr;
    tail = nullptr;
    numStudents = 0;
}

// Return the number of students
int StudentList::listSize() {
    return numStudents;
}

// Add a student to the front
void StudentList::addFront(Student s) {
    Node* newNode = new Node(s, head, nullptr);
    if (head != nullptr)
        head->prev = newNode;
    head = newNode;
    if (tail == nullptr)
        tail = newNode;
    numStudents++;
}

// Add a student to the back
void StudentList::addBack(Student s) {
    Node* newNode = new Node(s, nullptr, tail);
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    if (head == nullptr)
        head = newNode;
    numStudents++;
}

// Print list of student names
void StudentList::printList() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data.name;
        if (curr->next != nullptr) cout << " <-> ";
        curr = curr->next;
    }
    cout << endl;
}

// Remove student from front
void StudentList::popFront() {
    if (head == nullptr) {
        cout << "Error: List is empty, cannot popFront." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete temp;
    numStudents--;
}

// Remove student from back
void StudentList::popBack() {
    if (tail == nullptr) {
        cout << "Error: List is empty, cannot popBack." << endl;
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;
    delete temp;
    numStudents--;
}

// Insert student at index
void StudentList::insertStudent(Student s, int index) {
    if (index <= 0) {
        addFront(s);
        return;
    }
    if (index >= numStudents) {
        cout << "Index out of range. Adding to back instead." << endl;
        addBack(s);
        return;
    }
    Node* curr = head;
    for (int i = 0; i < index; i++) curr = curr->next;
    Node* newNode = new Node(s, curr, curr->prev);
    curr->prev->next = newNode;
    curr->prev = newNode;
    numStudents++;
}

// Retrieve student by ID
Student StudentList::retrieveStudent(int idNum) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.id == idNum)
            return curr->data;
        curr = curr->next;
    }
    cout << "No student with ID " << idNum << " found." << endl;
    return Student();
}

// Remove student by ID
void StudentList::removeStudentById(int idNum) {
    Node* curr = head;
    while (curr != nullptr && curr->data.id != idNum) curr = curr->next;
    if (curr == nullptr) {
        cout << "No student with ID " << idNum << " found." << endl;
        return;
    }
    if (curr == head)
        popFront();
    else if (curr == tail)
        popBack();
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        numStudents--;
    }
}

// Update GPA by ID
void StudentList::updateGPA(int idNum, float newGPA) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.id == idNum) {
            curr->data.GPA = newGPA;
            return;
        }
        curr = curr->next;
    }
    cout << "No student with ID " << idNum << " found." << endl;
}

// Merge another list into this list
void StudentList::mergeList(StudentList &otherList) {
    if (otherList.head == nullptr) return;
    if (head == nullptr) {
        head = otherList.head;
        tail = otherList.tail;
    } else {
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    }
    numStudents += otherList.numStudents;
    otherList.head = nullptr;
    otherList.tail = nullptr;
    otherList.numStudents = 0;
}

// Return a new list with students above min GPA
StudentList StudentList::honorRoll(float minGPA) {
    StudentList honors;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.GPA >= minGPA)
            honors.addBack(curr->data);
        curr = curr->next;
    }
    return honors;
}

// Remove all students below threshold GPA
void StudentList::removeBelowGPA(float threshold) {
    if (head == nullptr) {
        cout << "List is empty. Nothing to remove." << endl;
        return;
    }
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        if (curr->data.GPA < threshold) {
            if (curr == head)
                popFront();
            else if (curr == tail)
                popBack();
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                numStudents--;
            }
        }
        curr = nextNode;
    }
}
