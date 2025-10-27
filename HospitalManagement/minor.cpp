#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

// ---------- User System ----------
struct User {
    string username, password, role;
};

// Register any username, password, and role
bool registerUser() {
    User u;
    cout << "\n=== Register User ===\n";
    cout << "Enter new username: ";
    cin >> u.username;
    cout << "Enter new password: ";
    cin >> u.password;
    cout << "Enter role (Admin/Doctor/Receptionist): ";
    cin >> u.role;
    ofstream file("users.txt", ios::app);
    file << u.username << " " << u.password << " " << u.role << endl;
    file.close();
    cout << "Registration successful!\n";
    return true;
}

// Login: match username and password with no restrictions
bool login(User &user) {
    cout << "\n=== Login ===\nUsername: ";
    cin >> user.username;
    cout << "Password: ";
    cin >> user.password;

    ifstream file("users.txt");
    string u, p, r;
    while (file >> u >> p >> r) {
        if (u == user.username && p == user.password) {
            user.role = r;
            cout << "Logged in as " << user.role << "!\n";
            return true;
        }
    }
    cout << "Invalid username or password!\n";
    return false;
}

// ---------- Patient System ----------
class Patient {
    string id, name, disease;
    int age;
    static map<string, int> diseaseCount;

public:
    void input() {
        cout << "\n--- Add New Patient ---\n";
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Disease (General/Heart/Lung/Plastic): ";
        getline(cin, disease);
        diseaseCount[disease]++;
        id = disease.substr(0, 3);
        for (auto &c : id) c = toupper(c);
        id += to_string(diseaseCount[disease]);
    }
    void save() {
        ofstream file("hospital.txt", ios::app);
        file << id << "," << name << "," << age << "," << disease << endl;
        file.close();
        cout << "Patient record saved successfully.\n";
    }
    static void showAll() {
        ifstream file("hospital.txt");
        if (!file) {
            cout << "No records found.\n";
            return;
        }
        cout << "\n--- Patient Records ---\n";
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Age"
             << setw(20) << "Disease" << endl;
        cout << string(60, '-') << endl;
        string id, name, age, disease;
        while (getline(file, id, ',') &&
               getline(file, name, ',') &&
               getline(file, age, ',') &&
               getline(file, disease)) {
            cout << left << setw(10) << id
                 << setw(20) << name
                 << setw(10) << age
                 << setw(20) << disease << endl;
        }
        file.close();
    }
    static void search(const string &pid) {
        ifstream file("hospital.txt");
        string id, name, age, disease;
        bool found = false;
        while (getline(file, id, ',') &&
               getline(file, name, ',') &&
               getline(file, age, ',') &&
               getline(file, disease)) {
            if (id == pid) {
                cout << "\n--- Record Found ---\n";
                cout << "ID: " << id << "\nName: " << name
                     << "\nAge: " << age << "\nDisease: " << disease << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "Patient not found!\n";
        file.close();
    }
    static void remove(const string &pid) {
        ifstream file("hospital.txt");
        ofstream temp("temp.txt");
        string id, name, age, disease;
        bool found = false;
        while (getline(file, id, ',') &&
               getline(file, name, ',') &&
               getline(file, age, ',') &&
               getline(file, disease)) {
            if (id == pid) {
                found = true; // skip writing this patient (delete)
            } else {
                temp << id << "," << name << "," << age << "," << disease << endl;
            }
        }
        file.close();
        temp.close();
        remove("hospital.txt");
        rename("temp.txt", "hospital.txt");
        if (found) {
            cout << "Patient '" << pid << "' removed successfully.\n";
        } else {
            cout << "Patient not found!\n";
        }
    }
};
map<string, int> Patient::diseaseCount;

// ---------- Menus ----------
void adminMenu() {
    int choice;
    Patient p;
    do {
        cout << "\n=== ADMIN MENU ===";
        cout << "\n1. Add Patient";
        cout << "\n2. View All Patients";
        cout << "\n3. Search Patient by ID";
        cout << "\n4. Delete Patient by ID";
        cout << "\n5. Logout";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: p.input(); p.save(); break;
        case 2: Patient::showAll(); break;
        case 3: {
            string id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            Patient::search(id); break;
        }
        case 4: {
            string id;
            cout << "Enter Patient ID to delete: ";
            cin >> id;
            Patient::remove(id); break;
        }
        case 5: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}
void doctorMenu() {
    int choice;
    do {
        cout << "\n=== DOCTOR MENU ===";
        cout << "\n1. View All Patients";
        cout << "\n2. Search Patient by ID";
        cout << "\n3. Logout";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: Patient::showAll(); break;
        case 2: {
            string id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            Patient::search(id); break;
        }
        case 3: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}
void receptionistMenu() {
    int choice;
    Patient p;
    do {
        cout << "\n=== RECEPTIONIST MENU ===";
        cout << "\n1. Add New Patient";
        cout << "\n2. View All Patients";
        cout << "\n3. Logout";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: p.input(); p.save(); break;
        case 2: Patient::showAll(); break;
        case 3: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// ---------- Main ----------
int main() {
    int mode;
    cout << "1. Register user\n2. Login\nEnter choice: ";
    cin >> mode;

    User user;
    if (mode == 1) {
        registerUser();
    } else if (mode == 2) {
        if (login(user)) {
            // Optional: convert role to lowercase for easy compare
            string role = user.role;
            for (auto &c : role) c = tolower(c);
            if (role == "admin") adminMenu();
            else if (role == "doctor") doctorMenu();
            else if (role == "receptionist") receptionistMenu();
            else cout << "Unknown role access denied!\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
    cout << "Program terminated.\n";
    return 0;
}
