#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void swap(char &k1, char &k2) {
    char temp = k1;
    k1 = k2;
    k2 = temp;
}

void swapColumns(vector<vector<char>>& matrix, int col1, int col2, int row) {
    for (int i = 0; i < row; i++) {
        swap(matrix[i][col1], matrix[i][col2]);
    }
}


string encryption(string plainText, string key, int times) {
    if(times==0) return plainText;
    int col = key.length();
    int row = (plainText.length() / col) + 1;
    
    vector<vector<char>> matrix(row, vector<char>(col, ' '));

    int d = 0;
    string cipherText = "";

    for (int i = 0; i < col; i++) {
        matrix[0][i] = key[i];
    }
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (d < plainText.length()) {
                matrix[i][j] = plainText[d++];
            } else {
                matrix[i][j] = ' ';  
            }
        }
    }

    for (int i = 0; i < col - 1; i++) {
        for (int j = i + 1; j < col; j++) {
            if (matrix[0][i] > matrix[0][j]) {
                swapColumns(matrix, i, j, row);
            }
        }
    }

    // In ma trận đã sắp xếp
    // for (int i = 0; i < row; i++) {
    //     for (int j = 0; j < col; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < col; i++) {
        for (int j = 1; j < row; j++) {
            cipherText += matrix[j][i];
        }
    }

    return encryption(cipherText, key, times-1);
}

// Hàm giải mã
string decryption(string cipherText, string key, int times) {
    if (times == 0) return cipherText;

    int col = key.length();
    int row = (cipherText.length() / col) + 1;

    vector<vector<char>> matrix(row, vector<char>(col, ' '));

    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

    vector<int> colOrder(col);
    for (int i = 0; i < col; i++) {
        colOrder[i] = key.find(sortedKey[i]); 
    }

    int d = 0;
    for (int i = 0; i < col; i++) {
        int originalCol = colOrder[i];
        for (int j = 1; j < row; j++) {
            if (d < cipherText.length()) {
                matrix[j][originalCol] = cipherText[d++];
            }
        }
    }

    string plainText = "";
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col; j++) {
            plainText += matrix[i][j];
        }
    }

    return decryption(plainText, key, times - 1);
}

int main() {
    string plainText = "attackpostponeduntilthisnoon";
    string cipherText = "nttcnasilotoaodstetipphuknno";
    string key = "MONARCH";
    int times = 2;

    cipherText = encryption(plainText, key, times);
    plainText = decryption(cipherText, key, times);
    cout << "\nCipher Text: " << plainText << endl;

    return 0;
}
