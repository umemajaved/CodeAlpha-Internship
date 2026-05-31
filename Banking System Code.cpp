#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// -------------------- Account Class --------------------
class Account {
private:
    int accountNumber;
    double balance;

public:
    Account(int accNo = 0, double bal = 0) {
        accountNumber = accNo;
        balance = bal;
    }

    int getAccNo() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        saveTransaction("Deposit", amount);
        cout << "Deposit Successful!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return;
        }
        balance -= amount;
        saveTransaction("Withdraw", amount);
        cout << "Withdrawal Successful!\n";
    }

    void saveTransaction(string type, double amount) {
        ofstream file("transactions.txt", ios::app);
        file << "Account: " << accountNumber << " | "
             << type << " | Amount: " << amount << endl;
        file.close();
    }

    void showTransactions() {
        ifstream file("transactions.txt");
        string line;
        cout << "\n--- Transaction History ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

// -------------------- Login System --------------------
bool registerUser() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration Successful!\n";
    return true;
}

bool loginUser() {
    string username, password, u, p;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p) {
        if (u == username && p == password) {
            cout << "Login Successful!\n";
            return true;
        }
    }

    cout << "Invalid Credentials!\n";
    return false;
}

// -------------------- Main --------------------
int main() {
    int choice;

    cout << "1. Register\n2. Login\nChoose: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    }

    if (!loginUser()) {
        return 0;
    }

    Account acc(1001);
    int option;
    double amount;

    do {
        cout << "\n--- BANK MENU ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Show Balance\n4. Transactions\n5. Exit\n";
        cout << "Choose: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Enter Amount: ";
            cin >> amount;
            acc.deposit(amount);
            break;

        case 2:
            cout << "Enter Amount: ";
            cin >> amount;
            acc.withdraw(amount);
            break;

        case 3:
            cout << "Balance: " << acc.getBalance() << endl;
            break;

        case 4:
            acc.showTransactions();
            break;
        }

    } while (option != 5);

    return 0;
}
