#include <vector>
#include <iostream>
#include "User.cpp"
using namespace std;


class PasswordManager {
private:
    vector<User*> users;
    User* currentUser;

public:
    // Initializes with default admin (admin/admin123)
    PasswordManager() {
        currentUser = nullptr;
        // Default admin
        users.push_back(new User("admin", "admin123", true));
    }

    // Registers new user if username is unique
    bool registerUser(string username, string password) {
        for (auto user : users) {
            if (user->getUsername() == username) {
                return false;
            }
        }
        users.push_back(new User(username, password, false));
        return true;
    }

    // Logs in user if credentials match
    bool login(string username, string password) {
        for (auto user : users) {
            if (user->getUsername() == username && user->verifyPassword(password)) {
                currentUser = user;
                return true;
            }
        }
        return false;
    }

    // Logs out current user
    void logout() {
        currentUser = nullptr;
    }

    // Get current user
    User* getCurrentUser() {
        return currentUser;
    }

    // Admin-only: lists all usernames with role
    void viewAllUsers() {
        if (currentUser && currentUser->getIsAdmin()) {
            cout << "\n=== ALL USERS ===" << endl;
            for (auto user : users) {
                cout << "- " << user->getUsername()
                     << (user->getIsAdmin() ? " (Admin)" : " (User)") << endl;
            }
        }
    }
};