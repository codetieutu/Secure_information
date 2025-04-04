#include <iostream>
#include <cstdlib> 
#include <ctime>  
#include <vector>
using namespace std;

vector<int> generateKey(int length){
    vector<int> key;
    srand(time(0));
    for (int i=0; i<length; i++){
        key.push_back(rand() % 2);
    }
    return key;
}

int main() {
  vector<int> key =  generateKey(10);
  for(int i : key){
    cout<<i;
  }
  return 0;
}

