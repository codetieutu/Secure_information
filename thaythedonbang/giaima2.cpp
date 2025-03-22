#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
    ifstream file("tansuat.txt");
    string line;
    unordered_map<string, double> data;
    while (getline(file, line))
    {
        stringstream ss(line);
        string key;
        double value;
        if (ss >> key >> value) data[key] = value;
    }
    for(auto row : data){
        cout<<row.first<<" - "<<row.second<<"\n";
    }
    return 0;
}