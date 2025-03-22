
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// read file key.txt
void readCipherKey(string filename, map<char, char>& cipherMap, map<char, char>& decryptMap) {
    ifstream file(filename);

    if (!file) {
        cerr << "Không thể mở file " << filename << "!\n";
        return;
    }

    string original, encrypted;
    getline(file, original);   
    getline(file, encrypted);  
    file.close();

    // Tạo ánh xạ mã hóa và giải mã
    for (size_t i = 0; i < original.size(); i++) {
        cipherMap[original[i]] = encrypted[i];  // Mã hóa
        decryptMap[encrypted[i]] = original[i]; // Giải mã
    }
}

string encryptInvoice(string input, const map<char, char> cipherMap) {
    string encryptedText;
    
    for (char ch : input) {
        if (cipherMap.find(ch) != cipherMap.end()) {
            encryptedText += cipherMap.at(ch); 
        } else {
            encryptedText += ch; 
        }
    }

    return encryptedText;
}

int main() {
   
    map<char, char> cipherMap,decryptMap; 
    readCipherKey("key.txt", cipherMap,decryptMap);
    
    string invoice;
    cout << "enter plain text: ";
    getline(cin, invoice);

    string encryptedInvoice = encryptInvoice(invoice, cipherMap);

    cout << "encrypted Text: " << encryptedInvoice << endl;

    return 0;
}
