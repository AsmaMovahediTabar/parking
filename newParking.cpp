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
        if (isEmpty()){ 
            cout << "stack is empty." <<endl;
            return 0;}
        else{
            int carID = list.head->data;
            return carID;
        }
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
    Parking(int n, int m) : numbersOfColumn(n), columnCapacity(m){
        for (int i=0; i < numbersOfColumn; i++)  columns.push_back(Stack(columnCapacity));
        cout << "Parking created with " << numbersOfColumn
             << " columns, each of capacity " << columnCapacity << endl;
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

     void ordering(int i) {

        if (columns[i].isEmpty()) {
            cout << "Column " << i << " is empty!" << endl;
            return;
        }
        
        // Step 1: Extract all cars from stack to array
        vector<int> cars;
        while (!columns[i].isEmpty()) {
            cars.push_back(columns[i].pop());
        }
        
        // Step 2: Apply merge sort recursively
        mergeSort(cars, 0, cars.size() - 1);
        
        // Step 3: Push sorted cars back to stack
        // Push in reverse to get ascending order from top
        for (int j = cars.size() - 1; j >= 0; j--) {
            columns[i].push(cars[j]);
        }
        
        cout << "✓ Merge sort completed for column " << i << endl;
    }

    // Recursive merge sort for vector
    void mergeSort(vector<int>& arr, int left, int right) {
        /*
        ████ RECURSIVE CONTROL FLOW ████
        
        Base case: Single element
        if (left >= right) return;
        
        Divide: Find middle point
        int mid = left + (right - left) / 2;
        
        Conquer: Sort both halves recursively
        mergeSort(arr, left, mid);      // Left half
        mergeSort(arr, mid + 1, right); // Right half
        
        Combine: Merge sorted halves
        merge(arr, left, mid, right);
        */
        
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        
        // Recursively sort left and right halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
    
    // Merge two sorted subarrays
    void merge(vector<int>& arr, int left, int mid, int right) {
        /*
        ████ MERGE PROCESS VISUALIZATION ████
        
        Example: arr = [27, 38, 43, 3, 9]
                 left=0, mid=2, right=4
        
        Step 1: Create temporary arrays
            leftArr = [27, 38, 43] (size = 3)
            rightArr = [3, 9] (size = 2)
        
        Step 2: Merge with two-pointer technique
            i=0, j=0, k=left=0
            Compare leftArr[0]=27 vs rightArr[0]=3 → 27>3 → arr[0]=3
            i=0, j=1, k=1
            Compare 27 vs 9 → 27>9 → arr[1]=9
            i=0, j=2 (end), copy remaining leftArr
            arr[2]=27, arr[3]=38, arr[4]=43
        
        Result: arr = [3, 9, 27, 38, 43]
        */
        
        int n1 = mid - left + 1;  // Size of left subarray
        int n2 = right - mid;     // Size of right subarray
        
        // Create temporary arrays
        vector<int> leftArr(n1);
        vector<int> rightArr(n2);
        
        // Copy data to temp arrays
        for (int p = 0; p < n1; p++)
            leftArr[p] = arr[left + p];
        for (int q = 0; q < n2; q++)
            rightArr[q] = arr[mid + 1 + q];
        
        // Merge the temp arrays back
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements of leftArr
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        // Copy remaining elements of rightArr
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
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

int main(){
    int n, m;
    cin>>n>>m;
    Parking(n,m);
}