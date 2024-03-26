#include <stdio.h>
#include <stdlib.h>

#define FILENAME "employee_data.dat"
#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[50];
    float salary;
};

void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    struct Employee newEmployee;

    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.id);

    printf("Enter Employee Name: ");
    scanf("%s", newEmployee.name);

    printf("Enter Employee Salary: ");
    scanf("%f", &newEmployee.salary);

    fwrite(&newEmployee, sizeof(struct Employee), 1, file);

    fclose(file);

    printf("Employee added successfully.\n");
}

void displayAllEmployees() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    struct Employee employee;

    printf("\nAll Employees:\n");
    printf("ID\tName\tSalary\n");

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("%d\t%s\t%.2f\n", employee.id, employee.name, employee.salary);
    }

    fclose(file);
}

void searchEmployeeByID() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    int searchID;
    struct Employee employee;
    int found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &searchID);

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.id == searchID) {
            printf("\nEmployee Found:\n");
            printf("ID\tName\tSalary\n");
            printf("%d\t%s\t%.2f\n", employee.id, employee.name, employee.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", searchID);
    }

    fclose(file);
}

void updateEmployeeByID() {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        perror("Error opening file for reading and writing");
        exit(EXIT_FAILURE);
    }

    int updateID;
    struct Employee employee;
    int found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &updateID);

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.id == updateID) {
            printf("\nEnter new details for Employee ID %d:\n", updateID);

            printf("Enter new Employee Name: ");
            scanf("%s", employee.name);

            printf("Enter new Employee Salary: ");
            scanf("%f", &employee.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&employee, sizeof(struct Employee), 1, file);
            found = 1;
            printf("Employee with ID %d updated successfully.\n", updateID);
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", updateID);
    }

    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Database Operations:\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;

            case 2:
                displayAllEmployees();
                break;

            case 3:
                searchEmployeeByID();
                break;

            case 4:
                updateEmployeeByID();
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}