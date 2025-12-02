#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList{
public:
    Node* head;

public:

    LinkedList() {
        this->head = nullptr;
    }

    ~LinkedList() {
        clear();
    }

    void addFirst(int data){
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    void addEnd(int data){
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    bool removeFirst() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return false;  
        }
        
        Node* temp = head;
        head = head->next;
        delete temp; 
        return true;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Stack{
    private:
    LinkedList list;
    int capacity;
    int size;

    public:
    Stack(int c){
        capacity = c;
        size = 0;
    }
    bool isEmpty(){
        if (size==0) return true;
        else return false;
    }
    bool isFull(){
        if(size == capacity) return true;
        else return false;
    }
    void push(int carID){
        if (isFull) cout << "stack is full."<< endl;
        else{
            Node* newNode = new Node(carID);
            list.addFirst(carID);
            size ++;
        }
        
    }
    int pop(){
        if (isEmpty) cout << "stack is empty." <<endl;
        else{
            list.removeFirst();
            size --;
            int carID = list.head->data;
            return carID;
        }
    }

    int peek(){
        if (isEmpty) cout << "stack is empty." <<endl;
        else{
            int carID = list.head->data;
            return carID;
        }
    }
};

class Queue{};

class Parking{
    private:

    //Node car;
    vector<Stack> column;
    int numbersOfColumn,columnCapacity;

    public:
    // Constructor
    Parking(int n, int m) : numbersOfColumn(n), columnCapacity(m){
        for (int i=0; i<=numbersOfColumn; i++)  column.push_back(Stack(columnCapacity));
        cout << "Parking created with " << numbersOfColumn
             << " columns, each of capacity " << columnCapacity << endl;
    }
};

class Car{
    int carID;
    Node* car;

    public:
    
    Car(int ci) : carID(ci) {
        car = new Node(carID); 
        cout << "Car created with ID: " << carID << endl;
    }
};

int main(){}