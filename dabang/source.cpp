#include <iostream>
#include <unordered_map>

using namespace std;

// Hàm mã hóa
string encrypt(const string &text, const unordered_map<char, char> &keyMap)
{
    string encryptedText = "";
    for (char c : text)
    {
        if (keyMap.find(c) != keyMap.end())
        {
            encryptedText += keyMap.at(c);
        }
        else
        {
            encryptedText += c;
        }
    }
    return encryptedText;
}

// Hàm giải mã
string decrypt(const string &text, const unordered_map<char, char> &keyMap)
{
    unordered_map<char, char> reverseKeyMap;
    for (auto pair : keyMap)
    {
        reverseKeyMap[pair.second] = pair.first;
    }

    string decryptedText = "";
    for (char c : text)
    {
        if (reverseKeyMap.find(c) != reverseKeyMap.end())
        {
            decryptedText += reverseKeyMap.at(c);
        }
        else
        {
            decryptedText += c;
        }
    }
    return decryptedText;
}

int main()
{
    // Bảng thay thế đơn giản (có thể thay đổi)
    unordered_map<char, char> keyMap = {
        {'a', 'q'}, {'b', 'w'}, {'c', 'e'}, {'d', 'r'}, {'e', 't'}, {'f', 'y'}, {'g', 'u'}, {'h', 'i'}, {'i', 'o'}, {'j', 'p'}, {'k', 'a'}, {'l', 's'}, {'m', 'd'}, {'n', 'f'}, {'o', 'g'}, {'p', 'h'}, {'q', 'j'}, {'r', 'k'}, {'s', 'l'}, {'t', 'z'}, {'u', 'x'}, {'v', 'c'}, {'w', 'v'}, {'x', 'b'}, {'y', 'n'}, {'z', 'm'}};

    string plaintext = "hello world";
    string encryptedText = encrypt(plaintext, keyMap);
    string decryptedText = decrypt(encryptedText, keyMap);

    cout << "Văn bản gốc: " << plaintext << endl;
    cout << "Văn bản mã hóa: " << encryptedText << endl;
    cout << "Văn bản giải mã: " << decryptedText << endl;

    return 0;
}
