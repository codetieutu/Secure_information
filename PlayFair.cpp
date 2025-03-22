#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

vector<vector<char>> keyMatrix(string key) {
    bool isUsed[26] = {false}; 
    vector<vector<char>> matrix(5, vector<char>(5, ' '));
    
    int row = 0, col = 0;

    for (char &ch : key) {
        ch = tolower(ch);
    }

    for (char ch : key) {
        if (ch == 'J') continue; 
        if (!isUsed[ch - 'a']) {
            matrix[row][col] = ch;
            isUsed[ch - 'a'] = true;
            col++;
            if (col > 4) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue; 
        if (!isUsed[ch - 'a']) {
            matrix[row][col] = ch;
            isUsed[ch - 'a'] = true;
            col++;
            if (col > 4) {
                col = 0;
                row++;
            }
        }
    }
    
    return matrix;
}

pair<int, int> findPos(vector<vector<char>> matrix, char k){
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            if(matrix[i][j]==k){
                return {i, j};
            }
        }
    }
    return {-1, -1}; 
}
char charAtPos(vector<vector<char>> matrix, int row, int col){
    return matrix[row][col];
}

string encryption(string plainText, vector<vector<char>> key){
    vector<pair<char, char>> pairs;
    int pos=0;
    string cipherText = "";
    while (pos<plainText.length()){
        char first = plainText[pos], second;
        pos++;
        if(pos==plainText.length() || plainText[pos-1]==plainText[pos]){
            second = 'x';
        }else{
            second = plainText[pos];
            pos++;
        }
        pairs.push_back({first, second});
    }
    
    for (pair p : pairs){
        pair<int, int> pos1 = findPos(key, p.first);
        pair<int, int> pos2 = findPos(key, p.second);
        pair<int, int> newPos1, newPos2;
        if(pos1.first==pos2.first){//same row
            newPos1 = {pos1.first, (pos1.second+1) % 5};
            newPos2 = {pos2.first, (pos2.second+1) % 5};
        }
        else if(pos1.second==pos2.second){//same col
            newPos1 = {(pos1.first+1) % 5, pos1.second};
            newPos2 = {(pos2.first+1) % 5, pos2.second};
        }
        else{
            newPos1 = {pos1.first, pos2.second};
            newPos2 = {pos2.first, pos1.second};
        }
        cipherText+= charAtPos(key, newPos1.first,newPos1.second);
        cipherText+= charAtPos(key, newPos2.first,newPos2.second);
    }

    return cipherText;
}

int main() {
    string plainText = "balloon";
    string key = "MONARCHY";
    vector<vector<char>> matrix = keyMatrix(key);
    
    string cipherText = encryption(plainText, matrix);
    cout<<cipherText;
    return 0;
}
