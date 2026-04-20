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
    

};