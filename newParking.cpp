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
    
     int getFirst() {
        if (head == nullptr) {
            return -1;  // Or throw exception
        }
        return head->data;
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
    bool push(int carID){
        if (isFull()){
            cout << "stack is full."<< endl;
            return false;}
        else{
            list.addFirst(carID);
            size ++;
            return true;
        }
        
    }
    int pop(){
        if (isEmpty()) cout << "stack is empty." <<endl;
        else{
            int carID = list.getFirst();
            list.removeFirst();
            size --;
            return carID;
        }
    }

    int peek(){
        if (isEmpty){ 
            cout << "stack is empty." <<endl;
            return 0;}
        else{
            int carID = list.head->data;
            return carID;
        }
    }
};

class Queue{};

class Parking{
    private:
    vector<Stack> columns;
    int numbersOfColumn;
    int columnCapacity;

    public:
    Parking(int n, int m) : numbersOfColumn(n), columnCapacity(m){
        for (int i=0; i < numbersOfColumn; i++)  columns.push_back(Stack(columnCapacity));
        cout << "Parking created with " << numbersOfColumn
             << " columns, each of capacity " << columnCapacity << endl;
    }

    
    int input(int carID){

    }

    void input(int carID,int i){

    }

    int find(int carID){

    }

    bool output(int carID){
        for(int i=0; i<=numbersOfColumn; i++){
            if(carID == columns[i].peek()){
                columns[i].pop();
                cout << "Car " << carID << " removed from column " << i << endl;
                return true;
            }
        }
        cout << "Car " << carID << " is not at top." << endl;
        return false;
    }

    void ordering(int i){

    }

    void displacement(int i, int j){
        int d = j;
        int r=0,s=0;
        while(columns[i].isEmpty()!= true){
            if (columns[d].isFull() && d != numbersOfColumn-1){
                d++;
                s++;
                continue;
            }
            if (columns[d].isFull() && d == numbersOfColumn-1){
                d=0;
                continue;
                s++;
            }
            if (columns[d].isFull() && d == i){
                d++;
                continue;
            }
            if(s == numbersOfColumn-2){
                cout << "i try all of stacks and we didnt have enough empty space." << endl;
                break;
            }
            columns[j].push(columns[i].pop());
        }
        if (columns[i].peek()==0) cout << "displacement done." <<endl;
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

void inputCar(Parking& parking, int carID, int column);
int findCar(Parking& parking, int carID);
bool outputCar(Parking& parking, int carID);
void orderColumn(Parking& parking, int column);
void displaceCars(Parking& parking, int fromCol, int toCol);

int main(){
    int n, m;
    cin>>n>>m;
    Parking(n,m);

    
}