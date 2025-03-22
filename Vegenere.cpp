#include <iostream>
#include <string>
using namespace std;

// Tim P (dua tren C va KK)
string decryptVigenere(string ciphertext, string key)
{
    string plaintext = "";
    int keyLength = key.length();

    for (int i = 0, j = 0; i < ciphertext.length(); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char c = toupper(ciphertext[i]) - 'A';
            char k = toupper(key[j % keyLength]) - 'A';
            char p = (c - k + 26) % 26 + 'A';
            plaintext += p;
            j++;
        }
        else
        {
            plaintext += ciphertext[i];
        }
    }
    return plaintext;
}
string encryptVigenere(string text, string key)
{
    string ciphertext = "";
    int keyLength = key.length();

    for (int i = 0, j = 0; i < text.length(); i++)
    {
        if (isalpha(text[i]))
        {
            char p = toupper(text[i]) - 'A';
            char k = toupper(key[j % keyLength]) - 'A';
            char c = (p + k) % 26 + 'A';
            ciphertext += c;
            j++;
        }
        else
        {
            ciphertext += text[i];
        }
    }
    return ciphertext;
}
string findVigenereKey(string plaintext, string ciphertext)
{
    string key = "";
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (isalpha(plaintext[i]) && isalpha(ciphertext[i]))
        {
            char p = toupper(plaintext[i]);
            char c = toupper(ciphertext[i]);
            char k = ((c - p + 26) % 26) + 'A';
            key += k;
        }
        else
        {
            key += plaintext[i];
        }
    }
    return key;
}

int main()
{
    string ciphertext, key;
    cout << "Nhap ban ma (C): ";
    getline(cin, ciphertext);
    cout << "Nhap khoa (K): ";
    getline(cin, key);

    if (key.empty())
    {
        cout << "Loi: Khong duoc de trong khoa!" << endl;
        return 1;
    }

    string decryptedText = findVigenereKey(ciphertext, key);
    cout << "Ban ro (P): " << decryptedText << endl;

    return 0;
}
