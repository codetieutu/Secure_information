#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <limits>

using namespace std;

map<string, double> calculateCharacterFrequency(string input) {
    map<string, double> frequency;
    for (char ch : input) {
        string key(1, ch); 
        frequency[key]++;
    }

    for (auto &ch : frequency) {
        ch.second = (ch.second / input.length()) * 100;
    }

    return frequency;
}

void readFrequency(map<string, double> &col1, map<string, double> &col2, map<string, double> &col3, map<string, double> &col4) {
    ifstream file("tansuat.txt");

    if (!file) {
        cerr << "Không thể mở file tansuat.txt!\n";
        return ;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string c1, c2, c3, c4;
        double f1, f2, f3, f4;
    
        if (ss >> c1 >> f1 >> c2 >> f2 >> c3 >> f3 >> c4 >> f4) {
            col1[c1] = f1;
            col2[c2] = f2;
            col3[c3] = f3;
            col4[c4] = f4;
        }
    }
   
    file.close();
    return ;
}

pair<string, double> findClosestFrequencyPair(string key, double value, map<string, double> freq) {

    pair<string, double> closestPair ={"a",100};

    for (auto pair : freq) {
        if (abs(pair.second-value)<closestPair.second){
            closestPair.first = pair.first;
            closestPair.second = abs(pair.second-value);
        }
    }

    return closestPair;
}

int main() {
    //read encrypted data
    ifstream file("ma.txt");
    if (!file) {
        cerr << "Không thể mở file ma.txt!\n";
        return 1;
    }

    string ma;
    getline(file, ma);
    file.close();


    map<string, double> maFrequency = calculateCharacterFrequency(ma);
    // read table frequency
    map<string, double> col1, col2, col3, col4;
    readFrequency(col1, col2, col3, col4);
    for (auto row : maFrequency){
        pair<string, double> pair = findClosestFrequencyPair(row.first, row.second, col1);
        cout<<row.first<<" - "<<pair.first<<"\n";
    }
    
    return 0;
}
