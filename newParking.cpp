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

    // O(m) - جستجوی ماشین
    int findPosition(int carID) {
    if (isEmpty()) return -1;  // خالی است
    
    Node* temp = list.head;
    int position = 1;  // موقعیت از بالا شروع می‌شود
    
    while (temp != nullptr) {
        if (temp->data == carID) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;  // پیدا نشد
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

    // O(1)
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

    // O(1)
    // فقط نگاه کردن به اولین ماشین بدون حذف
    int peek() {
        if (list.head == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return list.getFirst();
    }

    // O(1)
    // چک کردن خالی بودن صف
    bool isEmpty() {
        return list.head == nullptr;
    }

    // O(N)
    //n تعداد ماشین های در صف 
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

class Parking {
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
    // O(N)
    //  که n تعداد ستون هاست 
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
    // O(1)
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

    // O(n * m) - جستجوی ماشین بدون تغییر ترتیب
    int find(int carID) {
    for (int col = 0; col < numbersOfColumn; col++) {
        int position = columns[col].findPosition(carID);
        
        if (position != -1) {
            // پیدا شد!
            cout << "Car " << carID << " found in column " << col 
                 << " at position " << position << " from top." << endl;
            return col;  // شماره ستون را برمی‌گرداند
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
    void displacement(int i, int j) {
    // بررسی صحت اندیس‌ها
    if (i < 0 || i >= numbersOfColumn || j < 0 || j >= numbersOfColumn) {
        cout << "Invalid stack indices!" << endl;
        return;
    }
    
    // اگر منبع و مقصد یکی باشند
    if (i == j) {
        cout << "Source and destination are the same!" << endl;
        return;
    }
    
    // اگر ستون منبع خالی باشد
    if (columns[i].isEmpty()) {
        cout << "Source stack " << i << " is empty!" << endl;
        return;
    }
    
    cout << "\n=== Displacing cars from Stack " << i << " to Stack " << j << " ===" << endl;
    
    int destination = j;  // ستون مقصد فعلی
    int attempts = 0;     // تعداد تلاش‌ها برای یافتن ستون خالی
    int carsMoved = 0;    // تعداد ماشین‌های جابجا شده
    
    // تا زمانی که ستون i خالی نشده است
    while (!columns[i].isEmpty()) {
        // اگر ستون مقصد فعلی پر باشد یا همان ستون مبدا باشد
        if (columns[destination].isFull() || destination == i) {
            // ذخیره نقطه شروع جستجو
            int startSearch = destination;
            bool foundSpace = false;
            
            // جستجوی دورانی برای یافتن ستون با فضای خالی
            do {
                destination = (destination + 1) % numbersOfColumn;  // حرکت به ستون بعدی (دورانی)
                attempts++;
                
                // اگر به نقطه شروع بازگشتیم (تمام ستون‌ها را بررسی کردیم)
                if (destination == startSearch) {
                    cout << "✗ Checked all " << numbersOfColumn << " stacks, no available space found!" << endl;
                    break;
                }
                
                // اگر ستون مقصد i نباشد و پر هم نباشد
                if (destination != i && !columns[destination].isFull()) {
                    foundSpace = true;
                    cout << "  Found space in Stack " << destination << endl;
                    break;
                }
                
            } while (true);
            
            // اگر جای خالی پیدا نشد، عملیات را متوقف کن
            if (!foundSpace) {
                break;
            }
        }
        
        // جابجایی یک ماشین
        int carID = columns[i].pop();
        columns[destination].push(carID);
        carsMoved++;
        
        cout << "  Car " << carID << " moved: Stack " << i << " → Stack " << destination << endl;
        
    }}

    // O(M log M)
    void ordering(int i){
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

    void displayInputQueue() {
    cout << "Input Queue status:" << endl;
    inputQueue.display();
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

int main() {
    // تعریف تعداد ستون‌ها (n) و ظرفیت هر ستون (m) 
    int n = 2;  // تعداد ستون‌ها
    int m = 2;  // ظرفیت هر ستون

    // ایجاد پارکینگ
    Parking myParking(n, m);

    // تست ایجاد ماشین‌ها
    Car car1(101);
    Car car2(202);
    Car car3(303);
    Car car4(404);
    Car car5(505);
    Car car6(606);
    Car car7(707);

    // تست ورودی اولیه: پارک کردن ماشین‌ها تا پر شدن پارکینگ
    cout << "\nTesting initial inputs:" << endl;
    myParking.input(101);  // باید به ستون 0 برود
    myParking.input(202);  // ستون 0 (پر می‌شود)
    myParking.input(303);  // ستون 1
    myParking.input(404);  // ستون 1 (پر می‌شود)

    // نمایش وضعیت پارکینگ پس از پر شدن
    cout << "\nInitial parking status (parking full):" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }

    // تست صف: ورودی وقتی پارکینگ پر است (باید به صف بروند)
    cout << "\nTesting input when parking is full (cars should go to queue):" << endl;
    myParking.input(505);  // به صف می‌رود
    myParking.input(606);  // به صف می‌رود

    // نمایش وضعیت صف (باید 505 606 نشان دهد)
    myParking.displayInputQueue();

    // تست خارج کردن ماشین برای خالی کردن فضا و چک dequeue
    cout << "\nFreeing space by outputting a car and re-inputting:" << endl;
    myParking.output(202);  // حذف از بالای ستون 0 (فرض کنید 202 در top است)

    // حالا ورودی جدید: باید از صف dequeue کند و پارک کند
    myParking.input(707);  // 707 enqueue می‌شود, اما اول 505 dequeue و پارک می‌شود

    // نمایش وضعیت پارکینگ و صف پس از این عملیات (صف باید 606 707 داشته باشد)
    cout << "\nParking status after re-input:" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }
    myParking.displayInputQueue();

    // تست‌های دیگر برای کامل بودن
    // تست جستجو
    cout << "\nTesting find for car 303:" << endl;
    myParking.find(303);

    // نمایش پس از جستجو
    cout << "\nParking status after find" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }

    // تست خروجی
    cout << "\nTesting output for car 303:" << endl;
    myParking.output(303);

    // نمایش پس از خروجی
    cout << "\nParking status after output:" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }

    // تست مرتب سازی
    cout << "\nTesting ordering for column 0:" << endl;
    myParking.ordering(0);

    // نمایش پس از مرتب سازی
    cout << "\nParking status after ordering column 0:" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }

    // تست جابجایی
    cout << "\nTesting displacement from column 0 to column 1:" << endl;
    myParking.displacement(0, 1);

    // نمایش پس از جابجایی
    cout << "\nParking status after displacement:" << endl;
    for (int i = 0; i < n; i++) {
        myParking.display(i);
    }

    // نمایش نهایی صف
    myParking.displayInputQueue();

    return 0;
}