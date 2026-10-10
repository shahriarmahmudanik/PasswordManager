#include <string>
using namespace std;

class Encryption {
private:
    static const int shift = 5;

public:
    // Encrypts text using Caesar cipher (shift +5)
    static string encrypt(string text) {
        string result = "";
        for (char c : text) {
            result += char(c + shift);
        }
        return result;
    }

    // Decrypts text using Caesar cipher (shift -5)
    static string decrypt(string text) {
        string result = "";
        for (char c : text) {
            result += char(c - shift);
        }
        return result;
    }
};