#include <iostream>
using namespace std;

void deCryption(string ma, int key) {
    string result = "";
    for (char k : ma) {
        if ('a' <= k && k <= 'z') {
            result += (char) ('a' + (k - 'a' - key + 26) % 26);
        } 
        else if ('A' <= k && k <= 'Z') {
            result += (char) ('A' + (k - 'A' - key + 26) % 26);
        } 
        else {
            result += k; 
        }
    }
    cout << "Decrypted result: " << result << endl;
}

void deCryption(string ma) {
    string result = "";
    for (int key = 1; key <= 25; key++) {
        result = "";
        for (char k : ma) {
            if ('a' <= k && k <= 'z') {
                result += (char) ('a' + (k - 'a' - key + 26) % 26);
            } 
            else if ('A' <= k && k <= 'Z') {
                result += (char) ('A' + (k - 'A' - key + 26) % 26);
            } 
            else {
                result += k;
            }
        }
        cout << "Key: " << key << " -> " << result << "\n";
    }
}

void enCryption(string text, int key) {
    string result = "";
    for (char k : text) {
        if ('a' <= k && k <= 'z') {
            result += (char) ('a' + (k - 'a' + key) % 26);
        } 
        else if ('A' <= k && k <= 'Z') {
            result += (char) ('A' + (k - 'A' + key) % 26);
        } 
        else {
            result += k;
        }
    }
    cout << "Encrypted result: " << result << endl;
}

int main() {
    string text = "I like apple"; 
    int key = 12;                
    // enCryption(text, key);
    deCryption(" PAPZYHPUPUN");//key =7 it is raning

    return 0;
}
