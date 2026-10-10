#include <string>
#include <ctime>
#include <iostream>
#include "Encryption.cpp"
using namespace std;


class Credential {
private:
    static int nextId;
    int id;
    string name;
    string username;
    string password;
    string category;
    time_t dateCreated;
    time_t lastUpdated;

public:
    // Constructor: assigns ID, sets fields, records creation time
    Credential(string n, string u, string p, string c) {
        id = nextId++;
        name = n;
        username = u;
        password = p;
        category = c;
        dateCreated = time(0);
        lastUpdated = time(0);
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getCategory() const { return category; }
    time_t getLastUpdated() const { return lastUpdated; }

    // Display credential information
    void display(bool showPassword = false, bool isDecrypted = false) const {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;

        if (showPassword) {
            cout << "Password: " << Encryption::decrypt(password) << endl;
        } else {
            string masked = string(Encryption::decrypt(password).length(), '*');
            cout << "Password: " << masked << endl;
        }

        cout << "Category: " << category << endl;
        cout << "Created: " << ctime(&dateCreated);
        cout << "Last Updated: " << ctime(&lastUpdated);
        cout << "----------------------------------------" << endl;
    }

    // Updates username and lastUpdated time
    void setUsername(string u) {
        username = u;
        lastUpdated = time(0);
    }

    // Updates encrypted password and lastUpdated time
    void setPassword(string p) {
        password = p;
        lastUpdated = time(0);
    }

    // Updates category and lastUpdated time
    void setCategory(string c) {
        category = c;
        lastUpdated = time(0);
    }
};

// Initialize static variable
int Credential::nextId = 1;