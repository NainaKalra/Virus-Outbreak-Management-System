#include <iostream>
#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string location;
    string symptoms;
    int severity;
    string status;
    bool tested;
    bool isPositive;

    // stack for contact tracing
    string contactStack[10];
    int stackTop;

    // constructor - default values
    Patient()
    {
        id = 0;
        age = 0;
        severity = 1;
        status = "Active";
        tested = false;
        isPositive = false;
        stackTop = -1;
    }
};

// linked list node
struct Node
{
    Patient data;
    Node *next;

    Node(Patient p)
    {
        data = p;
        next = nullptr;
    }
};

// testing center queue
struct TestingQueue
{
    int patientIds[50];
    int front;
    int rear;
    int count;

    TestingQueue()
    {
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(int patientId)
    {
        if (count == 50)
        {
            cout << "Testing queue is full. Please wait." << endl;
            return;
        }
        rear++;
        patientIds[rear] = patientId;
        count++;
        cout << "Patient ID: " << patientId << " added to the testing queue." << endl;
    }

    int dequeue()
    {
        if (count == 0)
        {
            cout << "Testing queue is empty." << endl;
            return -1;
        }
        int id = patientIds[front];
        front++;
        count--;
        return id;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "Testing queue is empty." << endl;
            return;
        }
        cout << "Testing Queue: ";
        for (int i = front; i <= rear; i++)
        {
            cout << "ID: " << patientIds[i];
            if (i != rear)
                cout << " -> ";
        }
        cout << endl;
    }
};

// linked list to manage patients
struct LinkedList
{
    Node *head;
    int size;

    LinkedList()
    {
        head = nullptr;
        size = 0;
    }

    void addPatient(Patient p)
    {
        Node *newNode = new Node(p);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
        cout << "Patient " << p.name << " added with ID " << p.id << endl;
    }

    Node *findPatient(int id)
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

    void removePatient(int id)
    {
        if (head == nullptr)
        {
            cout << "No patients found." << endl;
            return;
        }
        // case 1: patient is at head
        if (head->data.id == id)
        {
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            cout << "Patient removed." << endl;
            return;
        }
        // case 2: patient is in middle or end
        Node *temp = head;
        while (temp->next != nullptr)
        {
            if (temp->next->data.id == id)
            {
                Node *toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
                size--;
                cout << "Patient removed." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient not found." << endl;
    }

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
                 << " | Name: " << temp->data.name
                 << " | Age: " << temp->data.age
                 << " | City: " << temp->data.location
                 << " | Severity: " << sev
                 << " | Status: " << temp->data.status
                 << " | Tested: " << (temp->data.tested ? "Yes" : "No");

            if (temp->data.tested)
                cout << " | Result: " << (temp->data.isPositive ? "Positive" : "Negative");

            cout << endl;
            temp = temp->next;
            num++;
        }
        cout << "Total: " << size << " patients" << endl;
    }

    // copy linked list data into an array for sorting/searching
    // returns number of patients copied
    int copyToArray(Patient arr[])
    {
        Node *temp = head;
        int i = 0;
        while (temp != nullptr)
        {
            arr[i] = temp->data;
            i++;
            temp = temp->next;
        }
        return i;
    }

    // FIX: BubbleSort now correctly sorts Patient array by severity (high to low)
    void bubbleSort(Patient arr[], int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j].severity < arr[j + 1].severity)
                {
                    Patient temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // linear search by ID
    int searchById(Patient arr[], int n, int searchId)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i].id == searchId)
                return i;
        }
        return -1;
    }

    // sort by ID ascending — required before binary search
    void bubbleSortById(Patient arr[], int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j].id > arr[j + 1].id)
                {
                    Patient temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // binary search by ID (array must be sorted by ID first)
    // returns index if found, -1 if not found
    int binarySearchById(Patient arr[], int n, int searchId)
    {
        int low = 0;
        int high = n - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (arr[mid].id == searchId)
                return mid; // found
            else if (arr[mid].id < searchId)
                low = mid + 1; // search right half
            else
                high = mid - 1; // search left half
        }
        return -1; // not found
    }
};

// --- Contact Tracing (Stack) ---

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
    if (p.stackTop == -1)
    {
        cout << "No contacts to remove." << endl;
        return;
    }
    cout << "Removed contact: " << p.contactStack[p.stackTop] << endl;
    p.stackTop--;
}

void displayContacts(Patient &p)
{
    if (p.stackTop == -1)
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

// --- Testing Queue Processing ---

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
        cout << "Patient not found in records." << endl;
        return;
    }

    cout << "Testing: " << node->data.name << " (ID: " << id << ")" << endl;
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
        cout << "Result: NEGATIVE - Patient cleared." << endl;
        node->data.status = "Recovered";
    }
}

// --- Patient Summary ---

void patientSummary(LinkedList &list)
{
    if (list.size == 0)
    {
        cout << "No patients registered." << endl;
        return;
    }

    int active = 0, recovered = 0, deceased = 0, critical = 0, untested = 0;

    Node *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.status == "Active")
            active++;
        else if (temp->data.status == "Recovered")
            recovered++;
        else if (temp->data.status == "Deceased")
            deceased++;
        if (temp->data.severity == 4)
            critical++;
        if (!temp->data.tested)
            untested++;
        temp = temp->next;
    }

    cout << "\n------PATIENT SUMMARY-------" << endl;
    cout << "Total Patients : " << list.size << endl;
    cout << "Active         : " << active << endl;
    cout << "Recovered      : " << recovered << endl;
    cout << "Deceased       : " << deceased << endl;
    cout << "Critical       : " << critical << endl;
    cout << "Untested       : " << untested << endl;
    cout << "----------------------------" << endl;
}

// --- Main ---

int main()
{
    LinkedList patientList;
    TestingQueue testQueue;
    int choice;

    do
    {
        cout << "\n====== COVID PATIENT MANAGEMENT SYSTEM ======" << endl;
        cout << "1.  Add Patient" << endl;
        cout << "2.  Remove Patient" << endl;
        cout << "3.  Display All Patients" << endl;
        cout << "4.  Add Patient to Testing Queue" << endl;
        cout << "5.  Process Testing Queue" << endl;
        cout << "6.  Add Contact (Contact Tracing)" << endl;
        cout << "7.  Remove Last Contact" << endl;
        cout << "8.  Display Patient Contacts" << endl;
        cout << "9.  Patient Summary" << endl;
        cout << "10. Sort by Severity (Bubble Sort)" << endl;
        cout << "11. Search Patient by ID (Linear Search)" << endl;
        cout << "12. Search Patient by ID (Binary Search)" << endl;
        cout << "0.  Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Patient p;
            cout << "Enter ID: ";
            cin >> p.id;
            cin.ignore();

            // check for duplicate ID
            if (patientList.findPatient(p.id))
            {
                cout << "A patient with this ID already exists." << endl;
                continue;
            }

            cout << "Enter Name: ";
            getline(cin, p.name);

            cout << "Enter Age: ";
            cin >> p.age;
            cin.ignore();

            cout << "Enter City: ";
            getline(cin, p.location);

            cout << "Enter Symptoms: ";
            getline(cin, p.symptoms);

            cout << "Enter Severity (1=Mild, 2=Moderate, 3=Severe, 4=Critical): ";
            cin >> p.severity;

            patientList.addPatient(p);
        }

        else if (choice == 2)
        {
            int id;
            cout << "Enter Patient ID to remove: ";
            cin >> id;
            patientList.removePatient(id);
        }

        else if (choice == 3)
        {
            patientList.display();
        }

        else if (choice == 4)
        {
            int id;
            cout << "Enter Patient ID for testing: ";
            cin >> id;
            if (patientList.findPatient(id))
                testQueue.enqueue(id);
            else
                cout << "Patient not found." << endl;
        }

        else if (choice == 5)
        {
            processTestingQueue(testQueue, patientList);
        }

        else if (choice == 6)
        {
            int id;
            string contact;
            cout << "Enter Patient ID: ";
            cin >> id;
            cin.ignore();

            Node *n = patientList.findPatient(id);
            if (n)
            {
                cout << "Enter Contact Name: ";
                getline(cin, contact);
                pushContact(n->data, contact);
            }
            else
            {
                cout << "Patient not found." << endl;
            }
        }

        else if (choice == 7)
        {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;

            Node *n = patientList.findPatient(id);
            if (n)
                popContact(n->data);
            else
                cout << "Patient not found." << endl;
        }

        else if (choice == 8)
        {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;

            Node *n = patientList.findPatient(id);
            if (n)
                displayContacts(n->data);
            else
                cout << "Patient not found." << endl;
        }

        else if (choice == 9)
        {
            patientSummary(patientList);
        }

        else if (choice == 10)
        {
            // FIX: array refreshed here, not at program start
            Patient arr[50];
            int n = patientList.copyToArray(arr);

            if (n == 0)
            {
                cout << "No patients to sort." << endl;
                continue;
            }

            patientList.bubbleSort(arr, n);

            cout << "\nPatients Sorted by Severity (High to Low):" << endl;
            for (int i = 0; i < n; i++)
            {
                string sev = "";
                if (arr[i].severity == 1)
                    sev = "Mild";
                else if (arr[i].severity == 2)
                    sev = "Moderate";
                else if (arr[i].severity == 3)
                    sev = "Severe";
                else
                    sev = "Critical";

                cout << "ID: " << arr[i].id
                     << " | Name: " << arr[i].name
                     << " | Severity: " << sev << endl;
            }
        }

        else if (choice == 11)
        {
            // FIX: array refreshed here, not at program start
            Patient arr[50];
            int n = patientList.copyToArray(arr);

            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;

            int index = patientList.searchById(arr, n, id);

            if (index != -1)
            {
                string sev = "";
                if (arr[index].severity == 1)
                    sev = "Mild";
                else if (arr[index].severity == 2)
                    sev = "Moderate";
                else if (arr[index].severity == 3)
                    sev = "Severe";
                else
                    sev = "Critical";

                cout << "\nPatient Found!" << endl;
                cout << "ID       : " << arr[index].id << endl;
                cout << "Name     : " << arr[index].name << endl;
                cout << "Age      : " << arr[index].age << endl;
                cout << "City     : " << arr[index].location << endl;
                cout << "Severity : " << sev << endl;
                cout << "Status   : " << arr[index].status << endl;
                cout << "Tested   : " << (arr[index].tested ? "Yes" : "No") << endl;
                if (arr[index].tested)
                    cout << "Result   : " << (arr[index].isPositive ? "Positive" : "Negative") << endl;
            }
            else
            {
                cout << "Patient not found." << endl;
            }
        }

        else if (choice == 12)
        {
            Patient arr[50];
            int n = patientList.copyToArray(arr);

            if (n == 0)
            {
                cout << "No patients to search." << endl;
                continue;
            }

            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;

            // binary search requires sorted array — sort by ID first
            patientList.bubbleSortById(arr, n);

            int index = patientList.binarySearchById(arr, n, id);

            if (index != -1)
            {
                string sev = "";
                if (arr[index].severity == 1)
                    sev = "Mild";
                else if (arr[index].severity == 2)
                    sev = "Moderate";
                else if (arr[index].severity == 3)
                    sev = "Severe";
                else
                    sev = "Critical";

                cout << "\nPatient Found (Binary Search)!" << endl;
                cout << "ID       : " << arr[index].id << endl;
                cout << "Name     : " << arr[index].name << endl;
                cout << "Age      : " << arr[index].age << endl;
                cout << "City     : " << arr[index].location << endl;
                cout << "Severity : " << sev << endl;
                cout << "Status   : " << arr[index].status << endl;
                cout << "Tested   : " << (arr[index].tested ? "Yes" : "No") << endl;
                if (arr[index].tested)
                    cout << "Result   : " << (arr[index].isPositive ? "Positive" : "Negative") << endl;
            }
            else
            {
                cout << "Patient not found." << endl;
            }
        }

        else if (choice == 0)
        {
            cout << "Exiting system. Stay safe!" << endl;
        }

        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}