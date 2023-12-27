#include <stdio.h>
#include <string.h>

// Define the struct
struct Student {
    int studentID;
    char name[50];
    float GPA;
};

// Function to create a new student
struct Student createStudent(int id, const char *name, float gpa) {
    struct Student newStudent;
    newStudent.studentID = id;
    strcpy(newStudent.name, name);
    newStudent.GPA = gpa;
    return newStudent;
}

// Function to get student ID
int getStudentID(struct Student *student) {
    return student->studentID;
}

// Function to get student name
const char *getStudentName(struct Student *student) {
    return student->name;
}

// Function to get student GPA
float getStudentGPA(struct Student *student) {
    return student->GPA;
}

// Function to set student ID
void setStudentID(struct Student *student, int id) {
    student->studentID = id;
}

// Function to set student name
void setStudentName(struct Student *student, const char *name) {
    strcpy(student->name, name);
}

// Function to set student GPA
void setStudentGPA(struct Student *student, float gpa) {
    student->GPA = gpa;
}

int main() {
    // Create a struct instance using initialization
    struct Student student1 = {101, "Alice", 3.8};

    // Use getter functions to retrieve values
    int student1ID = getStudentID(&student1);
    const char *student1Name = getStudentName(&student1);
    float student1GPA = getStudentGPA(&student1);

    // Print the struct values
    printf("Student1 ID: %d\n", student1ID);
    printf("Student1 Name: %s\n", student1Name);
    printf("Student1 GPA: %.2f\n", student1GPA);

    // Create another struct instance using a function
    struct Student student2 = createStudent(102, "Bob", 3.5);

    // Print the values of the second struct
    printf("Student2 ID: %d\n", getStudentID(&student2));
    printf("Student2 Name: %s\n", getStudentName(&student2));
    printf("Student2 GPA: %.2f\n", getStudentGPA(&student2));

    // Directly copy the name from student1 to a new array
    char name[50];
    strcpy(name, student1.name);
    printf("Copied Name: %s\n", name);

    // Use setter methods to modify struct values
    setStudentID(&student1, 103);
    setStudentName(&student1, "Charlie");
    setStudentGPA(&student1, 3.2);

    // Print the updated values of student1
    printf("Updated Student1 ID: %d\n", getStudentID(&student1));
    printf("Updated Student1 Name: %s\n", getStudentName(&student1));
    printf("Updated Student1 GPA: %.2f\n", getStudentGPA(&student1));

    return 0;
}

