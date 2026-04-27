# Virus Outbreak Tracker
A menu-driven C++ program that simulates a virus outbreak 
management system. It helps track patients, manage testing, 
trace contacts, and view patient summaries.

## Data Structures Used
- Struct        : stores patient information
- Linked List   : manages patient records dynamically
- Stack         : contact tracing (LIFO)
- Queue         : testing center line (FIFO)
- Array         : used for sorting and searching
- Bubble Sort   : sorts patients by severity
- Binary Search : finds patient by ID

## How to Run
1. Open the file in VS Code or any online C++ compiler
2. Compile and run
3. Use the menu to interact with the program

## Menu Options
1.  Register Patient
2.  View All Patients
3.  Add to Testing Queue
4.  View Testing Queue
5.  Process Next Test
6.  Add Contact (Stack Push)
7.  Remove Last Contact (Stack Pop)
8.  View Contact Trace List
9.  Sort by Severity
10. Search Patient by ID
11. Update Patient Status
12. Remove Patient
13. Patient Summary
14. Exit

## Notes
- Patient ID must be unique
- Severity levels: 1=Mild, 2=Moderate, 3=Severe, 4=Critical
- Status options: Active, Recovered, Deceased
- Each patient can store up to 10 contacts in their stack
- Testing queue can hold up to 50 patients
