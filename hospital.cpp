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

    while(file.read((char*)&p, sizeof(p))) {
        p.display();
        cout << "-------------------";
    }

    file.close();
}


// ➤ SEARCH RECORD
void searchRecord() {
    int searchID;
    bool found = false;

    cout << "Enter Patient ID to Search: ";
    cin >> searchID;

    Patient p;
    ifstream file("patients.dat", ios::binary);

    while(file.read((char*)&p, sizeof(p))) {
        if(p.id == searchID) {
            cout << "\nRecord Found:\n";
            p.display();
            found = true;
            break;
        }
    }

    if(!found)
        cout << "Record Not Found!\n";

    file.close();
}


// ➤ DELETE RECORD
void deleteRecord() {
    int deleteID;
    bool found = false;

    cout << "Enter Patient ID to Delete: ";
    cin >> deleteID;

    Patient p;
    ifstream file("patients.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while(file.read((char*)&p, sizeof(p))) {
        if(p.id != deleteID)
            temp.write((char*)&p, sizeof(p));
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if(found)
        cout << "Record Deleted!\n";
    else
        cout << "Record Not Found!\n";
}


// ➤ UPDATE RECORD
void updateRecord() {
    int updateID;
    bool found = false;

    cout << "Enter Patient ID to Update: ";
    cin >> updateID;

    fstream file("patients.dat", ios::binary | ios::in | ios::out);
    Patient p;

    while(file.read((char*)&p, sizeof(p))) {
        if(p.id == updateID) {
            cout << "Enter New Details:\n";
            p.input();

            file.seekp(-sizeof(p), ios::cur);
            file.write((char*)&p, sizeof(p));

            found = true;
            break;
        }
    }

    if(found)
        cout << "Record Updated!\n";
    else
        cout << "Record Not Found!\n";

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
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}