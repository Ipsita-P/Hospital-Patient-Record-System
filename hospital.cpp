#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Patient {
public:
    int id;
    char name[50];
    int age;
    char disease[50];

    void input() {
        cout << "Enter Patient ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Disease: ";
        cin >> disease;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nDisease: " << disease << endl;
    }
};



// ➤ ADD RECORD
void addRecord() {
    Patient p;
    ofstream file("patients.dat", ios::binary | ios::app);

    p.input();
    file.write((char*)&p, sizeof(p));

    file.close();
    cout << "Record Added Successfully!\n";
}



// ➤ VIEW RECORDS
void viewRecords() {
    Patient p;
    ifstream file("patients.dat", ios::binary);

    cout << "\n--- Patient Records ---\n";

    while (file.read((char*)&p, sizeof(p))) {
        p.display();
        cout << "-----------------------";
    }

    file.close();
}



// ➤ SEARCH RECORD (New Feature)
void searchRecord() {
    int searchID;
    bool found = false;

    cout << "Enter Patient ID to Search: ";
    cin >> searchID;

    Patient p;
    ifstream file("patients.dat", ios::binary);

    while (file.read((char*)&p, sizeof(p))) {
        if (p.id == searchID) {
            cout << "\nRecord Found:\n";
            p.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record Not Found!\n";
    }

    file.close();
}



// ➤ MAIN MENU
int main() {
    int choice;

    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Record\n";
        cout << "2. View Records\n";
        cout << "3. Search Record\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}