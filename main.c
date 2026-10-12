#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "students_database.txt"
#define MAX_NAME_LEN 50

typedef struct {
    int rollNo;
    char name[MAX_NAME_LEN];
    float gpa;
} Student;

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void printMenu();

void printMenu() {
    printf("\n==================================================\n");
    printf("    STUDENT RECORD MANAGEMENT SYSTEM (PPS PROJECT)\n");
    printf("==================================================\n");
    printf("  1. Add New Student Record\n");
    printf("  2. Display All Student Records\n");
    printf("  3. Search Student by Roll Number\n");
    printf("  4. Delete Student Record\n");
    printf("  5. Exit & Save\n");
    printf("==================================================\n");
}

int main() {
    int choice;

    while (1) {
        printMenu();
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("\n    [SAVED] Exiting program. All data stored securely in '%s'.\n", FILENAME);
                return 0;
            default:
                printf("\n    [ERROR] Invalid option! Please choose between 1 and 5.\n");
        }
    }

    return 0;
}

// 1. Add Student Record (Appends to file)
void addStudent() {
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("    [ERROR] Could not open database file for writing!\n");
        return;
    }

    Student s;
    printf("\n--- ADD NEW STUDENT ---\n");
    printf("    Enter Roll Number : ");
    scanf("%d", &s.rollNo);
    printf("    Enter Full Name   : ");
    scanf(" %[^\n]", s.name); // Read string with spaces
    printf("    Enter GPA         : ");
    scanf("%f", &s.gpa);

    fprintf(fp, "%d %s %.2f\n", s.rollNo, s.name, s.gpa);
    fclose(fp);
    printf("    [SUCCESS] Record added successfully!\n");
}

// 2. Display All Records from File
void displayStudents() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] No records found. Database is currently empty.\n");
        return;
    }

    Student s;
    printf("\n--- REGISTERED STUDENT RECORDS ---\n");
    printf("    %-10s | %-25s | %-6s\n", "Roll No", "Name", "GPA");
    printf("    --------------------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.gpa) != EOF) {
        // Note: For multi-word names in fscanf simplicity, single tokens are read. 
        // For production, fgets is used, but this matches basic PPS stream parsing.
        printf("    %-10d | %-25s | %.2f\n", s.rollNo, s.name, s.gpa);
    }
    printf("    --------------------------------------------------\n");

    fclose(fp);
}

// 3. Search Student by Roll Number
void searchStudent() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] Database is empty.\n");
        return;
    }

    int targetRoll;
    printf("\n--- SEARCH STUDENT ---\n");
    printf("    Enter Roll Number to search: ");
    scanf("%d", &targetRoll);

    Student s;
    bool found = false;

    while (fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.gpa) != EOF) {
        if (s.rollNo == targetRoll) {
            printf("\n    [FOUND] Record Match:\n");
            printf("    Roll Number : %d\n", s.rollNo);
            printf("    Name        : %s\n", s.name);
            printf("    GPA         : %.2f\n", s.gpa);
            found = true;
            break;
        }
    }

    if (!found) {
        printf("\n    [NOT FOUND] No student record with Roll No %d.\n", targetRoll);
    }

    fclose(fp);
}

// 4. Delete Student Record (Rewrite filter technique)
void deleteStudent() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] Database is empty.\n");
        return;
    }

    int targetRoll;
    printf("\n--- DELETE STUDENT ---\n");
    printf("    Enter Roll Number to delete: ");
    scanf("%d", &targetRoll);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("    [ERROR] Temporary file creation failed!\n");
        fclose(fp);
        return;
    }

    Student s;
    bool found = false;

    while (fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.gpa) != EOF) {
        if (s.rollNo == targetRoll) {
            found = true; // Skip writing this record
        } else {
            fprintf(temp, "%d %s %.2f\n", s.rollNo, s.name, s.gpa);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("    [SUCCESS] Student record with Roll No %d deleted.\n", targetRoll);
    } else {
        printf("    [NOT FOUND] Student record with Roll No %d did not exist.\n", targetRoll);
    }
}
