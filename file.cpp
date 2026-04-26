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

    //constructor - to set default values for patient
    Patient(){
        id = 0;
        age = 0;
        severity = 1;
        status = "Active";
        tested = false;
        isPositive = false;
        stackTop = -1; // as stack is empty in start
    }
};

//linked list node for patient

struct Node{
    Patient data;
    Node* next;

    Node(Patient p){
        data = p;
        next = nullptr; //as in start there is no next node
    }
};

//testing center queue 
struct TestingQueue{
    //storing patient ids in the queue
    int patientIds[50]; 
    int front;          
    int rear;           
    int count; //patient count in the queue

//constructor to initialize the queue
    TestingQueue()
    {
        front = 0;
        rear = -1; //as rear starts before the first element
        count = 0;
    }

//adding patients in quueue -> using enqueue 
void enqueue(int patientId){
    if(count==50){
        cout << "Testing queue is full. Please wait." << endl;
        return;
    }
    rear++; //create space for new patient by moving rear forward
    //storing patient id in queue
    patientIds[rear] = patientId;
    count++; 
    cout<<"Patient ID: "<<patientId<<" is added to the testing queue."<<endl;
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
    //moving front pointer forward so that next patient becomes the front
    count--;
     //decreasing count
    return id; 
    //return the dequeued patient id so that we can update their status in linked list after testing
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
    //using for loop going from front to rear
    for(int i=front; i<=rear; i++){
        cout<<"ID: "<<patientIds[i];
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
    int size; //counter for nummber

    LinkedList(){
        head= nullptr; //as in start there is no patient
        size = 0;
    }

//adding patient to linked list
void addPatient(Patient p){
    Node* newNode = new Node(p);

    if(head == nullptr){
        head = newNode;
    }
    else{
        Node* temp= head;
        while(temp->next != nullptr){
            temp= temp->next;
        }
        temp->next = newNode;
    }
    size++;
    cout<<"Patient "<<p.name<<" added with ID "<<p.id<<endl;
}

//finding patient by id in linked list
Node* findPatient(int id)
{
    Node *temp= head;
    while (temp != nullptr)
    {
        if (temp->data.id == id)
            return temp; //returning temp and not data so we have the original thing to update after testing
        temp= temp->next;
    }
    return nullptr;
}

//removing patient from linked list
void removePatient(int id)
{
    if (head==nullptr)
    {
        cout << "No patients found." << endl;
        return;
    }
//case 1 - when patient is at head of linked list
    if (head->data.id == id)
    {
        Node *Delete = head;
        head = head->next;
        delete Delete;
        size--;
        cout << "Patient removed." << endl;
        return;
    }
//case 2 - when patient is in middle or end of linked list
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
        temp= temp->next;
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
    int num = 1; //just for numbering the patients in display

    while (temp != nullptr)
    {
        string sev= ""; //making temporary string to display severity in words instead of numbers
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

//if patient is tested then only we will show the result
        if (temp->data.tested)
            cout << " Result: " << (temp->data.isPositive ? "Positive" : "Negative");

        cout << endl;
        temp = temp->next; //sending temp to next patient 
        num++;
    }
    cout << "Total: " << size << " patients" << endl;
}
//to copy patient data from linked list to array for sorting and searching
int copyToArray(Patient arr[])
{
    Node *temp = head;
    int i = 0;
    while (temp != nullptr)
    {
        arr[i] = temp->data; //puts the patient data in array and then moves to next patient in linked list
        i++;
        temp = temp->next;
    }
    return i; // number of patients copied to array
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
};

// contact tracing : using stack for contact details of patients - uses LIFO 

void pushContact(Patient &p, string contactName)
{
    if (p.stackTop == 9)
    {
        cout << "Contact stack is full." << endl;
        return;
    }
    p.stackTop++;
    p.contactStack[p.stackTop] = contactName;
    cout << "Contact added: " << contactName << endl;
}

void popContact(Patient &p)
{
    if(p.stackTop==-1)
    {
        cout<<"No contacts to remove."<<endl;
        return;
    }
    cout<<"Removed contact is- "<<p.contactStack[p.stackTop]<<endl;
    p.stackTop--;
}

void displayContacts(Patient &p)
{
    if (p.stackTop==-1)
    {
        cout << "No contacts traced." << endl;
        return;
    }
    cout << "Contact Trace (Latest First):" << endl;
    for (int i = p.stackTop; i >= 0; i--)
    {
        cout << "  - " << p.contactStack[i] << endl;
    }
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

    



//process testing queue and update patient status by dequeueing patients and marking them as tested with results

void processTestingQueue(TestingQueue &tq, LinkedList &list)
{
    if (tq.isEmpty())
    {
        cout << "Testing queue is empty." << endl;
        return;
    }

    int id = tq.dequeue();
    Node *node = list.findPatient(id);

    if (node == nullptr)
    {
        cout << "The patient is not found in records." << endl;
        return;
    }

    cout << "Testing: " << node->data.name << " (ID: " <<id<< ")" << endl;
    node->data.tested = true;

    int res;
    cout << "Enter result (1=Positive, 0=Negative): ";
    cin >> res;
    node->data.isPositive = (res == 1);

    if (node->data.isPositive)
    {
        cout << "Result: POSITIVE - Isolation required!" << endl;
    }
    else
    {
        cout << "Result: Negative - Patient cleared." << endl;
        node->data.status = "Recovered";
    }

}

//main funtion and menu will be here - 
