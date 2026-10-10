#include <iostream>
#include <limits>
#include "PasswordGenerator.cpp"
#include "PasswordManager.cpp"
using namespace std;

// Displays main menu: Login, Register, Exit
void displayMainMenu() {
    cout << "\n======================================" << endl;
    cout << "   PASSWORD MANAGER SYSTEM" << endl;
    cout << "======================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "======================================" << endl;
    cout << "Enter choice: ";
}

// Displays user dashboard menu: shows admin option if isAdmin=true
void displayUserMenu(bool isAdmin) {
    cout << "\n======================================" << endl;
    cout << "   USER DASHBOARD" << endl;
    cout << "======================================" << endl;
    cout << "1. Add Credential" << endl;
    cout << "2. View All Credentials" << endl;
    cout << "3. Search Credentials" << endl;
    cout << "4. Edit Credential" << endl;
    cout << "5. Delete Credential" << endl;
    if (isAdmin) cout << "6. View All Users (Admin)" << endl;
    cout << "0. Logout" << endl;
    cout << "======================================" << endl;
    cout << "Enter choice: ";
}

// Add new credential with manual or generated password
void addCredentialMenu(User* user) {
    string name, username, password, category;
    int choice;

    cout << "\n=== ADD NEW CREDENTIAL ===" << endl;
    cout << "Enter name/website: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter username: ";
    getline(cin, username);

    cout << "1. Enter password manually\n2. Generate random password\nChoice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 2) {
        password = PasswordGenerator::generate(12);
        cout << "Generated password: " << password << endl;
    } else {
        cout << "Enter password: ";
        getline(cin, password);
    }

    cout << "Category (website/desktop/game): ";
    getline(cin, category);

    string encrypted = Encryption::encrypt(password);
    user->addCredential(new Credential(name, username, encrypted, category));

    cout << "\nCredential added successfully!" << endl;
}

// Lists all credentials sorted by last updated
// Revealing password by ID
void viewCredentialsMenu(User* user) {
    vector<Credential*>& creds = user->getCredentials();

    if (creds.empty()) {
        cout << "\nNo credentials stored." << endl;
        return;
    }

    user->sortByLastUpdated();

    cout << "\n=== YOUR CREDENTIALS (Sorted by Last Updated) ===" << endl;
    for (auto cred : creds) {
        cred->display(false);
    }

    cout << "\nEnter credential ID to reveal password (0 to go back): ";
    int id;
    cin >> id;

    if (id == 0) return;

    for (auto cred : creds) {
        if (cred->getId() == id) {
            cred->display(true);
            return;
        }
    }

    cout << "\nCredential not found." << endl;
}

// Searches credentials by partial name match
void searchCredentialsMenu(User* user) {
    string searchName;
    cout << "\nEnter name to search: ";
    cin.ignore();
    getline(cin, searchName);

    vector<Credential*> results = user->searchCredentials(searchName);

    if (results.empty()) {
        cout << "\nNo credentials found." << endl;
        return;
    }

    cout << "\n=== SEARCH RESULTS ===" << endl;
    for (auto cred : results) {
        cred->display(false);
    }
}

// Edits username, password, or category of a credential by ID
void editCredentialMenu(User* user) {
    int id;
    cout << "\nEnter credential ID to edit: ";
    cin >> id;
    cin.ignore();

    auto& creds = user->getCredentials();
    Credential* cred = nullptr;
    for (auto c : creds) {
        if (c->getId() == id) {
            cred = c;
            break;
        }
    }

    if (!cred) {
        cout << "\nCredential not found." << endl;
        return;
    }

    cout << "\n1. Edit username\n2. Edit password\n3. Edit category\nChoice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    string newValue;
    switch (choice) {
        case 1:
            cout << "Enter new username: ";
            getline(cin, newValue);
            cred->setUsername(newValue);
            break;
        case 2:
            cout << "Enter new password: ";
            getline(cin, newValue);
            cred->setPassword(Encryption::encrypt(newValue));
            break;
        case 3:
            cout << "Enter new category: ";
            getline(cin, newValue);
            cred->setCategory(newValue);
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    cout << "\nCredential updated successfully!" << endl;
}

// Deletes credential by ID
void deleteCredentialMenu(User* user) {
    int id;
    cout << "\nEnter credential ID to delete: ";
    cin >> id;

    if (user->deleteCredentialById(id)) {
        cout << "\nCredential deleted successfully!" << endl;
    } else {
        cout << "\nCredential not found." << endl;
    }
}