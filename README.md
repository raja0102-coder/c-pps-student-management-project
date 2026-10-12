# Student Record Management System (PPS Capstone Project)

A complete Semester 1 Programming for Problem Solving (PPS) C application providing a menu-driven database system for managing student records with permanent file persistence.

## PPS Concepts Integrated
* **Structures (`struct`)**: Encapsulating student attributes (Roll Number, Name, GPA).
* **File Stream Handling (`fopen`, `fprintf`, `fscanf`, `fclose`)**: Disk persistence ensuring data survives program termination.
* **CRUD Operations**: Create (append), Read (scan display), Search (targeted lookup), and Delete (temp file filtering).
* **Control Flow & Loops**: Interactive `while(1)` menu loops combined with `switch-case` dispatchers.

## How to Compile & Run
```bash
gcc main.c -o student_system
./student_system
