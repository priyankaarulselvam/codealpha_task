#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50]; // FIXED: Changed from char to a character array string
    float gpa;
} Student;

// Using a standard local name. If on mobile, it creates it in the app workspace folder.
const char* FILE_NAME = "students.dat";

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    while(1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n2. Display All Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input type!\n");
            break;
        }
        
        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void addStudent() {
    // "ab+" creates the file automatically if it does not exist, preventing opening errors
    FILE *fp = fopen(FILE_NAME, "ab+");
    if (!fp) { 
        printf("Error: Cannot open or create data file! Check app folder permissions.\n"); 
        return; 
    }
    
    Student s;
    printf("Enter ID: "); scanf("%d", &s.id);
    printf("Enter Name: "); scanf(" %[^\n]s", s.name);
    printf("Enter GPA: "); scanf("%f", &s.gpa);
    
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student record added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { 
        printf("No records found! (Add a student first to generate the file).\n"); 
        return; 
    }
    
    Student s;
    printf("\nID\tName\t\tGPA\n");
    printf("----------------------------------\n");
    while(fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%d\t%-15s\t%.2f\n", s.id, s.name, s.gpa);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found!\n"); return; }
    
    int id, found = 0;
    printf("Enter Student ID to search: "); scanf("%d", &id);
    
    Student s;
    while(fread(&s, sizeof(Student), 1, fp) == 1) {
        if(s.id == id) {
            printf("\nRecord Found!\nID: %d\nName: %s\nGPA: %.2f\n", s.id, s.name, s.gpa);
            found = 1;
            break;
        }
    }
    if(!found) printf("Student record not found.\n");
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) { printf("No records found to update!\n"); return; }
    
    int id, found = 0;
    printf("Enter Student ID to update: "); scanf("%d", &id);
    
    Student s;
    while(fread(&s, sizeof(Student), 1, fp) == 1) {
        if(s.id == id) {
            printf("Enter New Name: "); scanf(" %[^\n]s", s.name);
            printf("Enter New GPA: "); scanf("%f", &s.gpa);
            
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            printf("Record updated successfully!\n");
            break;
        }
    }
    if(!found) printf("Student record not found.\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found to delete!\n"); return; }
    
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) { 
        printf("Error creating temporary system file.\n"); 
        fclose(fp); 
        return; 
    }
    
    int id, found = 0;
    printf("Enter Student ID to delete: "); scanf("%d", &id);
    
    Student s;
    while(fread(&s, sizeof(Student), 1, fp) == 1) {
        if(s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    
    if(found) printf("Record deleted successfully!\n");
    else printf("Student record not found.\n");
}