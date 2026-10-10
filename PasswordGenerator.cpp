#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class PasswordGenerator {
public:
    // Generates random password of specified length from letters, digits, symbols
    static string generate(int length = 12) {
        const string chars =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "!@#$%^&*";

        string password = "";
        srand(time(0));

        for (int i = 0; i < length; i++) {
            password += chars[rand() % chars.length()];
        }

        return password;
    }
};