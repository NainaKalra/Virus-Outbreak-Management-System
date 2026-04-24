#include <iostream>
#include <string>
using namespace std;

struct Patient{
    int id;
    string name;
    int age;
    string location;
    string symptoms;
    int severity;
    string status;
    bool tested;
    bool isPositive;
    

    //making a stack for contact tracing

    string contactStack[10];
    int stackTop;

    //constructor 
    Patient(){
        id = 0;
        age = 0;
        severity = 1;
        status = "Active";
        tested = false;
        isPositive = false;
        stackTop = -1; // stack is empty in start
    }
};

//linked list node for patient

struct Node{
    Patient data;
    Node* next;

    Node(Patient p){
        data = p;
        next = nullptr;
    }
};

//testing center queue 

struct TestingQueue{
    //storing patient ids in the queue
    int patientIds[50]; 
    int front;          
    int rear;           
    int count; //patient count in the queue

    TestingQueue()
    {
        front = 0;
        rear = -1;
        count = 0;
    }

//adding patients in quueue -> using enqueue 
void enqueue(int patientId){
    if(count == 50){
        cout << "Testing queue is full. Please wait." << endl;
        return;
    }
    rear++; //pointer forward 
    //storing patient id in queue
    patientIds[rear] = patientId;
    count++; 
    cout<<"Patient ID"<<patientId<<"added to the testing queue."<<endl;
}
//dequeue - to remoeve patients after testing from the quueue
int dequeue(){
    if(count == 0){
        cout << "Testing queue is empty." << endl;
        return -1; //empty queue 
    }
    int id = patientIds[front];
     //getting the front patient id
    front++; 
    //moving front pointer forward
    count--;
     //decreasing count
    return id; 
    //return the dequeued patient id
}
//to check if quqeue is empty - 
bool isEmpty(){
    return count == 0;
}
//display queue function
void display(){
    if(count==0){
        cout << "Testing queue is empty." << endl;
        return;
    }
    cout<<"Testing Queue: ";
    for(int i=front; i<=rear; i++){
        cout<<"ID - "<<patientIds[i];
        if(i!=rear){
            cout<<" -> ";
        }
        cout<<endl;
    }
}

};

//Linked list - to manage and add or remove patients 
struct LinkedList{
    Node *head;
    int size;

    LinkedList(){
        head = nullptr;
        size = 0;
    }

//adding patient to linked list
void addPatient(Patient p){
    Node* newNode = new Node(p);

    if(head == nullptr){
        head = newNode;
    }
    else{
        Node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
    cout<<"Patient "<<p.name<<" added with ID "<<p.id<<endl;
}

//finding patient by id in linked list
Node* findPatient(int id)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.id == id)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

//removing patient from linked list
void removePatient(int id)
{
    if (head == nullptr)
    {
        cout << "No patients found." << endl;
        return;
    }

    if (head->data.id == id)
    {
        Node *Delete = head;
        head = head->next;
        delete Delete;
        size--;
        cout << "Patient removed." << endl;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr)
    {
        if (temp->next->data.id == id)
        {
            Node *Delete = temp->next;
            temp->next = Delete->next;
            delete Delete;
            size--;
            cout << "Patient removed." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Patient not found." << endl;
}

//displaying all patients in linked list
void display()
{
    if (head == nullptr)
    {
        cout << "No patients registered." << endl;
        return;
    }

    cout << "\n-----All Patients------" << endl;
    Node *temp = head;
    int num = 1;

    while (temp != nullptr)
    {
        string sev = "";
        if (temp->data.severity == 1)
            sev = "Mild";
        else if (temp->data.severity == 2)
            sev = "Moderate";
        else if (temp->data.severity == 3)
            sev = "Severe";
        else
            sev = "Critical";

        cout << num << ". ID: " << temp->data.id
             << " Name: " << temp->data.name
             << " Age: " << temp->data.age
             << " City: " << temp->data.location
             << " Severity: " << sev
             << " Status: " << temp->data.status
             << " Tested: " << (temp->data.tested ? "Yes" : "No");

        if (temp->data.tested)
            cout << " Result: " << (temp->data.isPositive ? "Positive" : "Negative");

        cout << endl;
        temp = temp->next;
        num++;
    }
    cout << "Total: " << size << " patients" << endl;
}

// counting the number of nodes in linkedlist
int countNodes(Node* head){
    int count = 0;
    Node* temp = head;

    while (temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

//Making of array for bubble sort and binary search
struct Array{
    int length;
    int size;
    int* items;
}

Array(int arrsize){
    size = arrsize;
    length = 0;
    items = new int[arrsize];
}

void linkedList (Node* head, size, array){
    
    Node* temp = head;

    for (int i = 0; i <= size; i++){
        while (temp != nullptr){
            i = temp->data
            item[i];
            temp = temp->next;
        
    return arr;
}

    


hi
};
