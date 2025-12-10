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

    Node* findMiddle(Node* head) {
        if (head == nullptr) return head;
        
        Node* slow = head;
        Node* fast = head->next;
        
        /*
        حرکت اشاره‌گرها:
        slow: یک قدم در هر تکرار
        fast: دو قدم در هر تکرار
        
        وقتی fast به انتها رسید، slow در وسط است.
        
        مثال:
        List: [1]→[2]→[3]→[4]→[5]→NULL
        
        Step 1: slow→[1], fast→[2]
        Step 2: slow→[2], fast→[4]
        Step 3: slow→[3], fast→NULL (ایست)
        
        نتیجه: وسط = [3]
        */
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // ادغام دو لیست مرتب شده به صورت بازگشتی
    Node* mergeRecursive(Node* left, Node* right) {
        // حالت پایه
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        
        // انتخاب گره کوچک‌تر و ادامه بازگشتی
        if (left->data <= right->data) {
            left->next = mergeRecursive(left->next, right);
            return left;
        } else {
            right->next = mergeRecursive(left, right->next);
            return right;
        }
    }
    
    // مرج‌سورت بازگشتی اصلی
    Node* mergeSortRecursive(Node* head) {
        // حالت پایه: لیست خالی یا تک‌عنصری
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // ۱. پیدا کردن وسط لیست
        Node* middle = findMiddle(head);
        Node* nextOfMiddle = middle->next;
        
        // ۲. جدا کردن لیست به دو نیمه
        middle->next = nullptr;
        
        // ۳. مرتب‌سازی بازگشتی هر نیمه
        Node* left = mergeSortRecursive(head);
        Node* right = mergeSortRecursive(nextOfMiddle);
        
        // ۴. ادغام دو نیمه مرتب شده
        return mergeRecursive(left, right);
    }
    
    // فراخوانی اصلی مرج‌سورت
    void mergeSort() {
        head = mergeSortRecursive(head);
    }
    
    // نمایش لیست برای دیباگ
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " → ";
            temp = temp->next;
        }
        cout << " → NULL" << endl;
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

    // Push: Add car to stack (park car)
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
    // Pop: Remove car from top of stack
    int pop(){
        if (isEmpty()) cout << "stack is empty." <<endl;
        else{
            int carID = list.getFirst();
            list.removeFirst();
            size --;
            return carID;
        }
    }
    // Peek: See top car without removing
    int peek(){
        if (isEmpty){ 
            cout << "stack is empty." <<endl;
            return 0;}
        else{
            int carID = list.head->data;
            return carID;
        }
    }

    void sort() {
        cout << "مرتب‌سازی Stack با مرج‌سورت بازگشتی..." << endl;
        cout << "قبل از مرتب‌سازی: ";
        display();
        
        // فراخوانی مرج‌سورت روی LinkedList
        list.mergeSort();
        
        cout << "بعد از مرتب‌سازی: ";
        display();
        cout << "مرتب‌سازی تکمیل شد!" << endl;
    }
    
    // نمایش Stack (از بالا به پایین)
    void display() {
        if (list.head == nullptr) {
            cout << "Stack خالی است" << endl;
            return;
        }
        
        cout << "Top → ";
        list.display();
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
    void ordering(int i) {
        // ۱. بررسی معتبر بودن شماره Stack
        if (i < 0 || i >= numbersOfColumn) {
            cout << " شماره Stack نامعتبر!" << endl;
            return;
        }
        
        // ۲. بررسی خالی نبودن Stack
        if (columns[i].isEmpty()) {
            cout << " Stack " << i << " خالی است!" << endl;
            return;
        }
        
        cout << "\n" << string(60, '=') << endl;
        cout << "مرتب‌سازی Stack شماره " << i << " با مرج‌سورت بازگشتی" << endl;
        cout << string(60, '=') << endl;
        
        // ۳. فراخوانی تابع sort روی Stack
        columns[i].sort();
        
        cout << string(60, '=') << endl;
    }
    
    // تابع کمکی برای نمایش یک Stack
    void displayStack(int i) {
        if (i < 0 || i >= numbersOfColumn) {
            cout << " شماره Stack نامعتبر!" << endl;
            return;
        }
        
        cout << "Stack " << i << ": ";
        columns[i].display();
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

int main(){
    int n, m, i;
    cin>>n>>m;
    Parking myParking(n,m);
    cin>>i;
    myParking.display(i);
}