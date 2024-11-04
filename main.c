#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_ADMISSIONS 100

// Structure definitions
typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[15];
    int academicScore;  // Represented by percentage
    int entranceExamScore; // Represented by score
} Student;

typedef struct {
    int id;
    char specialization[50];
    char eligibility[100];
    char admissionRequirements[100];
    char importantDates[50];
} Program;

typedef struct {
    int studentId;
    int programId;
    char status[20];  // Applied, Processing, Selected, Rejected
    int finalScore;
} Admission;

// Global variables
Student students[MAX_STUDENTS];
Program programs[5];
Admission admissions[MAX_ADMISSIONS];
int studentCount = 0;
int admissionCount = 0;

// Function prototypes
void registerStudent();
void viewPrograms();
void applyForAdmission();
void processApplication();
void calculateFinalScore();
void admissionCommitteeReview();
void notifyApplicant();

// Main menu function
void displayMenu() {
    int choice;
    do {
        printf("\n=== B.Tech Admission System ===\n");
        printf("1. Register Student\n");
        printf("2. View Programs\n");
        printf("3. Apply for Admission\n");
        printf("4. Process Applications\n");
        printf("5. Admission Committee Review\n");
        printf("6. Notify Applicant\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewPrograms(); break;
            case 3: applyForAdmission(); break;
            case 4: processApplication(); break;
            case 5: admissionCommitteeReview(); break;
            case 6: notifyApplicant(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
}

// Function implementations

// 1. Register Student
void registerStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student registration limit reached.\n");
        return;
    }

    Student s;
    s.id = studentCount + 1;
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter email: ");
    scanf(" %[^\n]", s.email);
    printf("Enter phone: ");
    scanf(" %[^\n]", s.phone);
    printf("Enter academic score (percentage): ");
    scanf("%d", &s.academicScore);
    printf("Enter entrance exam score: ");
    scanf("%d", &s.entranceExamScore);

    students[studentCount++] = s;
    printf("Student registered successfully! ID: %d\n", s.id);
}

// 2. View Programs
void viewPrograms() {
    printf("\n=== B.Tech Programs ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Program ID: %d\n", programs[i].id);
        printf("Specialization: %s\n", programs[i].specialization);
        printf("Eligibility: %s\n", programs[i].eligibility);
        printf("Admission Requirements: %s\n", programs[i].admissionRequirements);
        printf("Important Dates: %s\n", programs[i].importantDates);
        printf("---------------------------------\n");
    }
}

// 3. Apply for Admission
void applyForAdmission() {
    int studentId, programId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);
    printf("Enter Program ID: ");
    scanf("%d", &programId);

    // Check if the student is eligible for the program
    Admission admission = {studentId, programId, "Applied", 0};
    admissions[admissionCount++] = admission;

    printf("Application submitted successfully!\n");
}

// 4. Process Application
void processApplication() {
    for (int i = 0; i < admissionCount; i++) {
        if (strcmp(admissions[i].status, "Applied") == 0) {
            // Simple validation (check if scores are available)
            int studentIndex = admissions[i].studentId - 1;
            if (students[studentIndex].academicScore > 0 && students[studentIndex].entranceExamScore > 0) {
                strcpy(admissions[i].status, "Processing");
                printf("Application ID %d is now being processed.\n", i + 1);
            }
        }
    }
}

// 5. Admission Committee Review
void admissionCommitteeReview() {
    for (int i = 0; i < admissionCount; i++) {
        if (strcmp(admissions[i].status, "Processing") == 0) {
            calculateFinalScore(&admissions[i]);
            strcpy(admissions[i].status, (admissions[i].finalScore >= 70) ? "Selected" : "Rejected");
            printf("Application ID %d reviewed. Status: %s\n", i + 1, admissions[i].status);
        }
    }
}

// Helper function to calculate final score
void calculateFinalScore(Admission* admission) {
    int studentIndex = admission->studentId - 1;
    Student student = students[studentIndex];
    admission->finalScore = (student.academicScore * 0.5) + (student.entranceExamScore * 0.5);
}

// 6. Notify Applicant
void notifyApplicant() {
    int studentId;
    printf("Enter Student ID to check status: ");
    scanf("%d", &studentId);

    for (int i = 0; i < admissionCount; i++) {
        if (admissions[i].studentId == studentId) {
            printf("Application Status: %s\n", admissions[i].status);
            return;
        }
    }
    printf("No application found for the given Student ID.\n");
}

// Main function
int main() {
    // Sample data for programs
    for (int i = 0; i < 5; i++) {
        programs[i].id = i + 1;
        sprintf(programs[i].specialization, "Specialization %d", i + 1);
        sprintf(programs[i].eligibility, "Eligibility criteria for Spec %d", i + 1);
        sprintf(programs[i].admissionRequirements, "Requirements for Spec %d", i + 1);
        sprintf(programs[i].importantDates, "Dates for Spec %d", i + 1);
    }

    displayMenu();
    return 0;
}
