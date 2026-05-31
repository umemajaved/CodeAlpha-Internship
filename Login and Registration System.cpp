#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple hash function (for learning purpose)
string hashPassword(string password) {
    string hashed = "";
    for (int i = 0; i < password.length(); i++) {
        hashed += char(password[i] + 2); // simple shift
    }
    return hashed;
}

// Check if user exists
bool isUserExists(string username) {
    ifstream file("users.txt");
    string user, pass;

    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Registration
void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";
    cout << "Enter Username: ";
    cin >> username;

    if (isUserExists(username)) {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter Password (min 4 characters): ";
    cin >> password;

    if (password.length() < 4) {
        cout << "Password too short!\n";
        return;
    }

    string hashedPass = hashPassword(password);

    ofstream file("users.txt", ios::app);
    file << username << " " << hashedPass << endl;
    file.close();

    cout << "Registration Successful!\n";
}

// Login
void loginUser() {
    string username, password;
    string user, pass;
    bool found = false;

    cout << "\n--- Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    string hashedPass = hashPassword(password);

    ifstream file("users.txt");

    while (file >> user >> pass) {
        if (user == username && pass == hashedPass) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Login Successful! Welcome, " << username << "!\n";
    } else {
        cout << "Invalid Username or Password!\n";
    }
}

// Admin Panel
void adminPanel() {
    string adminPass;

    cout << "\n--- Admin Panel ---\n";
    cout << "Enter Admin Password: ";
    cin >> adminPass;

    if (adminPass != "admin123") {
        cout << "Access Denied!\n";
        return;
    }

    ifstream file("users.txt");
    string user, pass;

    cout << "\nRegistered Users:\n";

    while (file >> user >> pass) {
        cout << "Username: " << user << endl;
    }

    file.close();
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                adminPanel();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}
