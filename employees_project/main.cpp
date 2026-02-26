#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100;

struct Employee {
    char surname[50];
    char position[50];
    int salary;
};

Employee employees[MAX];
int countEmployees = 0;

void loadFromFile() {
    FILE* file = fopen("employees.txt", "r");

    if (file == NULL)
        return;

    while (fscanf(file, "%s %s %d",
        employees[countEmployees].surname,
        employees[countEmployees].position,
        &employees[countEmployees].salary) == 3) {
        countEmployees++;
    }

    fclose(file);
}

void saveToFile() {
    FILE* file = fopen("employees.txt", "w");

    if (file == NULL) {
        cout << "Error opening file!\n";
        return;
    }

    for (int i = 0; i < countEmployees; i++) {
        fprintf(file, "%s %s %d\n",
            employees[i].surname,
            employees[i].position,
            employees[i].salary);
    }

    fclose(file);
    cout << "Data saved to file.\n";
}

void addEmployee() {
    if (countEmployees >= MAX) {
        cout << "Employee list is full!\n";
        return;
    }

    cout << "Surname: ";
    cin >> employees[countEmployees].surname;

    cout << "Position: ";
    cin >> employees[countEmployees].position;

    cout << "Salary: ";
    cin >> employees[countEmployees].salary;

    countEmployees++;
    cout << "Employee added!\n";
}

void showAll() {
    if (countEmployees == 0) {
        cout << "Employee list is empty.\n";
        return;
    }

    for (int i = 0; i < countEmployees; i++) {
        cout << employees[i].surname << " | "
            << employees[i].position << " | "
            << employees[i].salary << endl;
    }
}

void findEmployee() {
    char surname[50];
    cout << "Enter surname to search: ";
    cin >> surname;

    for (int i = 0; i < countEmployees; i++) {
        if (strcmp(employees[i].surname, surname) == 0) {
            cout << employees[i].surname << " | "
                << employees[i].position << " | "
                << employees[i].salary << endl;
            return;
        }
    }

    cout << "Employee not found.\n";
}

void deleteEmployee() {
    char surname[50];
    cout << "Enter surname to delete: ";
    cin >> surname;

    for (int i = 0; i < countEmployees; i++) {
        if (strcmp(employees[i].surname, surname) == 0) {
            for (int j = i; j < countEmployees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            countEmployees--;
            cout << "Employee deleted.\n";
            return;
        }
    }

    cout << "Employee not found.\n";
}

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Add employee\n";
        cout << "2 - Show all employees\n";
        cout << "3 - Find employee\n";
        cout << "4 - Delete employee\n";
        cout << "5 - Save to file\n";
        cout << "0 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: showAll(); break;
        case 3: findEmployee(); break;
        case 4: deleteEmployee(); break;
        case 5: saveToFile(); break;
        case 0: saveToFile(); break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}