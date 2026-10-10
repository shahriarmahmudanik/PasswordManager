#include <iostream>
#include "MenuSystem.cpp"
using namespace std;

// Entry point: handling login/register and user menu navigation
int main() {
    PasswordManager pm;
    int choice;

    while (true) {
        if (pm.getCurrentUser() == nullptr) {
            displayMainMenu();
            cin >> choice;

            if (choice == 1) {
                string username, password;
                cout << "\nUsername: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (pm.login(username, password)) {
                    cout << "\nLogin successful! Welcome " << username << endl;
                } else {
                    cout << "\nInvalid credentials!" << endl;
                }
            } else if (choice == 2) {
                string username, password;
                int passChoice;
                cout << "\nNew Username: ";
                cin >> username;
                cout << "1. Enter password manually\n2. Generate random password\nChoice: ";
                cin >> passChoice;

                if (passChoice == 2) {
                    password = PasswordGenerator::generate(12);
                    cout << "Generated password: " << password << endl;
                } else {
                    cout << "New Password: ";
                    cin >> password;
                }

                if (pm.registerUser(username, password)) {
                    cout << "\nRegistration successful!" << endl;
                } else {
                    cout << "\nUsername already exists!" << endl;
                }
            } else if (choice == 3) {
                cout << "\nThank you for using Password Manager!" << endl;
                break;
            }
        } else {
            User* currentUser = pm.getCurrentUser();
            displayUserMenu(currentUser->getIsAdmin());
            cin >> choice;

            switch (choice) {
                case 1: addCredentialMenu(currentUser); break;
                case 2: viewCredentialsMenu(currentUser); break;
                case 3: searchCredentialsMenu(currentUser); break;
                case 4: editCredentialMenu(currentUser); break;
                case 5: deleteCredentialMenu(currentUser); break;
                case 6: if (currentUser->getIsAdmin()) pm.viewAllUsers(); break;
                case 0: pm.logout(); cout << "\nLogged out successfully!" << endl; break;
                default: cout << "\nInvalid choice!" << endl; break;
            }
        }
    }

    return 0;
}