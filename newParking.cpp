#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    //O(1)
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList{
public:
    Node* head;

public:

    //O(1)
    LinkedList() {
        this->head = nullptr;
    }
    //O(m)
    ~LinkedList() {
        clear();
    }

    //O(1)
    void addFirst(int data){
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    //O(m)
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
    
    //O(1)
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
    
    //O(1)
    int getFirst() {
        if (head == nullptr) {
            return -1;  // Or throw exception
        }
        return head->data;
    }

    //O(m)
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    //O(m)
    Node* findMiddle(Node* head) {
        if (head == nullptr) return head;
        
        Node* slow = head;
        Node* fast = head->next;
        
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
    
    //O(m)
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << "-";
            temp = temp->next;
        }
        cout << " - NULL" << endl;
    }

};

class Stack{
    private:
    LinkedList list;
    int capacity;
    int size;

    public:
    //O(1)
    Stack(int c){
        capacity = c;
        size = 0;
    }
    //O(1)
    bool isEmpty(){
        if (size==0) return true;
        else return false;
    }
    //O(1)
    bool isFull(){
        if(size == capacity) return true;
        else return false;
    }

    // Push: Add car to stack (park car)
    //O(1)
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

    //O(1)
    // Pop: Remove car from top of stack
    int pop(){
        if (isEmpty()){
            cout << "stack is empty." <<endl;
            return -1;}
        else{
            int carID = list.getFirst();
            list.removeFirst();
            size --;
            return carID;
        }
    }

    //O(1)
    // Peek: See top car without removing
    int peek(){
        if (isEmpty()){ 
            return -1;}
        else{
            int carID = list.head->data;
            return carID;
        }
    }

    void sort() {
        // فراخوانی مرج‌سورت روی LinkedList
        list.mergeSort();
    }
    
    //O(m)
    // نمایش Stack (از بالا به پایین)
    void display() {
        if (list.head == nullptr) {
            cout << "Stack is empty." << endl;
            return;
        }
        
        cout << "Top - ";
        list.display();
    }
};

class Queue {
private:
    LinkedList list;
public:
// ورورد ماشین به صف ورودی پارکینگ که به آخر صف اضافه می شود
    void enqueue(int carID) {
        list.addEnd(carID);
    }
// پیچیدگی زمانی: چون از کلاس 
//linkedlist ارث بری کرده
// میشه O(n) 

    // خارج کردن اولین ماشین از صف (dequeue)
    //وقتی ماشین از صف ورودی، وارد پارکینگ می شود

    int dequeue() {
        if (list.head == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }

        int carID = list.getFirst();   // شماره پلاک اولین ماشین را می خواند 
        list.removeFirst();            // اولین Node را حذف می‌کنه
        return carID;                  // شماره ماشین رو برمی‌گردونه تا داخل استک گذاشته بشه 
    }

    // فقط نگاه کردن به اولین ماشین بدون حذف
    int peek() {
        if (list.head == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return list.getFirst();
    }

    // چک کردن خالی بودن صف
    bool isEmpty() {
        return list.head == nullptr;
    }

    // نمایش تمام ماشین‌های تو صف ورودی (از اول تا آخر) 
    void display() {
        if (list.head == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }
        
        cout << "Queue: ";
        Node* temp = list.head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class Parking{
    private:
    vector<Stack> columns;
    int numbersOfColumn;
    int columnCapacity;
    Queue inputQueue;

    public:
    //O(n)
    Parking(int n, int m) : numbersOfColumn(n), columnCapacity(m){
        for (int i=0; i < numbersOfColumn; i++)  columns.push_back(Stack(columnCapacity));
        cout << "Parking created with " << numbersOfColumn
             << " columns, each have " << columnCapacity << " capacity." << endl;
    }

    // تابع ورود خودرو به پارکینگ 
    // ماشین از صف ورودی وارد اولین استک خالی می شود 
    int input(int carID) {
        // ماشین وارد صف ورودی میشه (enqueue)
        inputQueue.enqueue(carID);
        // اولین ماشین صف را برداشته و میگذاریم در پارکینگ (dequeue)
        int car = inputQueue.dequeue();

        // می‌گردیم دنبال اولین استک خالی  
        for (int i = 0; i < numbersOfColumn; i++) {
        if (!columns[i].isFull()) {
            columns[i].push(car);
            cout << "Car " << car << " parked in column " << i << endl;
            return i;  // شماره ستون که ماشین پارک شده را بر می گرداند 
        }
    }

    // اگر همه استک ها پر باشند
    cout << "Parking is full." << endl;
    
    // ماشین رو برمی‌گردونیم به صف چون پارکینگ پر بوده 
    inputQueue.enqueue(car);

    return -1;  // یعنی پارکینگ پر بود و ماشین پارک نشد
}

    // ورود به Stack مشخص (شماره i توسط کاربر تعیین می‌شه)
    void input(int carID, int i) {
         // ماشین وارد صف ورودی میشه (enqueue)
        inputQueue.enqueue(carID);
        // اولین ماشین صف را برداشته و میگذاریم در پارکینگ (dequeue)
        int car = inputQueue.dequeue();

        // چک می‌کنیم آیا شماره استک معتبره (i باید بین 0 تا n-1 باشه)
        if (i < 0 || i >= numbersOfColumn) {
            cout << "Invalid column number." << endl;
            // ماشین رو برمی‌گردونیم به صف چون استک نامعتبر بود
            inputQueue.enqueue(car);
            return;
        }

        // چک می‌کنیم آیا استک پره یا نه
        if (columns[i].isFull()) {
            cout << "Column " << i << " is full." << endl;
            // برمی‌گردونیم به صف ورودی
            inputQueue.enqueue(car);
            return;
        }

        // ماشین رو می‌ذاریم تو استک شماره i
        columns[i].push(car);
        cout << "Car " << car << " parked in column " << i << endl;
    }
    
    // تابع find - جستجوی ماشین در تمام استک‌ها
    int find(int carID) {
        for (int col = 0; col < numbersOfColumn; col++) {
            vector<int> temp;          // برای نگه داشتن ماشین‌های خارج شده
            int position = 1;          // موقعیت از 1 شروع می‌شه (top = 1)

            // همه ماشین‌های این ستون رو موقتاً خارج می‌کنیم
            while (!columns[col].isEmpty()) {
                int currentCar = columns[col].pop();
                temp.push_back(currentCar);

                if (currentCar == carID) {
                    // پیدا شد!
                    cout << "Car " << carID << " found in column " << col 
                         << " at position " << position << " from top." << endl;

                    // حالا بقیه ماشین‌های خارج شده رو برمی‌گردونیم (ترتیب حفظ می‌شه)
                    // اول ماشین‌های زیرش رو برمی‌گردونیم، بعد خودش رو (چون خودش الان top جدیده)
                    for (int k = temp.size() - 1; k >= 0; k--) {
                        if (temp[k] != carID) {  // خودش رو دوباره push نمی‌کنیم (چون پیدا شده و نمی‌خوایم حذفش کنیم)
                            columns[col].push(temp[k]);
                        }
                    }
                    // خود ماشین پیدا شده رو هم برمی‌گردونیم بالای همه
                    columns[col].push(carID);

                    return col;  // شماره ستون رو برمی‌گردونیم
                }

                position++;
            }

            // اگر تا اینجا پیدا نشد → همه ماشین‌های خارج شده رو دقیقاً با همان ترتیب قبلی برمی‌گردونیم
            for (int k = temp.size() - 1; k >= 0; k--) {
                columns[col].push(temp[k]);
            }
        }

        // اگر هیچ جا پیدا نشد
        cout << "Car " << carID << " not found." << endl;
        return -1;
    }

    //O(n)
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

    //O(m*n)
    void displacement(int i, int j){
        if(i==j) return;
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
        if (i < 0 || i >= numbersOfColumn) {
            cout << "stack number is invalid." << endl;
            return;
        }
        
        if (columns[i].isEmpty()) {
            cout << " Stack " << i << "is empty." << endl;
            return;
        }
        
        // ۳. فراخوانی تابع sort روی Stack
        columns[i].sort();
    }
    
    //O(m)
    void display(int i) {
        if (i < 0 || i >= numbersOfColumn) {
            cout << "stack number is invalid." << endl;
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
    Parking myParking(n,m);
    myParking.display(i);
}