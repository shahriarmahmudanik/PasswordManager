#include <string>
#include <vector>
#include <algorithm>
#include "Credential.cpp"
using namespace std;


class User {
private:
    string username;
    string password;
    bool isAdmin;
    vector<Credential*> credentials;

public:
    // Constructor: sets username, password, admin status
    User(string u, string p, bool admin = false) {
        username = u;
        password = p;
        isAdmin = admin;
    }

    // Get user name
    string getUsername() const { return username; }
    
    // Get admin status
    bool getIsAdmin() const { return isAdmin; }

    // Verify password
    bool verifyPassword(string p) const {
        return password == p;
    }

    // Add credential
    void addCredential(Credential* cred) {
        credentials.push_back(cred);
    }

    // Get all credentials
    vector<Credential*>& getCredentials() {
        return credentials;
    }

    // Search credentials by name
    vector<Credential*> searchCredentials(string searchName) {
        vector<Credential*> results;
        for (auto cred : credentials) {
            if (cred->getName().find(searchName) != string::npos) {
                results.push_back(cred);
            }
        }
        return results;
    }

    // Delete credential by ID
    bool deleteCredentialById(int id) {
        for (size_t i = 0; i < credentials.size(); i++) {
            if (credentials[i]->getId() == id) {
                delete credentials[i];
                credentials.erase(credentials.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Sort credentials by last updated date
    void sortByLastUpdated() {
        sort(credentials.begin(), credentials.end(),
            [](Credential* a, Credential* b) {
                return a->getLastUpdated() > b->getLastUpdated();
            });
    }
};