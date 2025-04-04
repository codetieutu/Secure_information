#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib> 
#include <ctime> 
#include <string>

using namespace std;

// LFSR cấu trúc
struct LFSR {
    vector<int> reg;
    vector<int> taps;
    int clockBit;

    LFSR(int size, vector<int> tap_positions, int clock_bit) {
        reg.resize(size, 0);
        taps = tap_positions;
        clockBit = clock_bit;
    }

    void shift() {
        int new_bit = 0;
        for (int t : taps) {
            new_bit ^= reg[t];
        }
        for (int i = reg.size() - 1; i > 0; --i) {
            reg[i] = reg[i - 1];
        }
        reg[0] = new_bit;
    }

    int getClockBit() const {
        return reg[clockBit];
    }

    int getOutputBit() const {
        return reg.back();
    }
};

// Hàm majority
int majority(int x, int y, int z) {
    return (x + y + z) > 1 ? 1 : 0;
}

// Khởi tạo LFSR với khóa
void initWithKey(LFSR &r1, LFSR &r2, LFSR &r3, const vector<int> &key) {
    for (int i = 0; i < key.size(); ++i) {
        r1.reg[i % r1.reg.size()] ^= key[i];
        r2.reg[i % r2.reg.size()] ^= key[i];
        r3.reg[i % r3.reg.size()] ^= key[i];
    }
}

// Sinh keystream dài n bit
vector<int> generateKeystream(int length, LFSR r1, LFSR r2, LFSR r3) {
    vector<int> keystream;
    for (int i = 0; i < length; ++i) {
        int maj = majority(r1.getClockBit(), r2.getClockBit(), r3.getClockBit());
        if (r1.getClockBit() == maj) r1.shift();
        if (r2.getClockBit() == maj) r2.shift();
        if (r3.getClockBit() == maj) r3.shift();
        int bit = r1.getOutputBit() ^ r2.getOutputBit() ^ r3.getOutputBit();
        keystream.push_back(bit);
    }
    return keystream;
}

// XOR 2 vector bit
vector<int> xorBits(const vector<int> &a, const vector<int> &b) {
    vector<int> result;
    for (int i = 0; i < a.size(); ++i) {
        result.push_back(a[i] ^ b[i]);
    }
    return result;
}

// Chuyển chuỗi "101010" -> vector<int>
vector<int> stringToBits(const string &s) {
    vector<int> bits;
    for (char c : s) {
        bits.push_back(c - '0');
    }
    return bits;
}

// Chuyển vector<int> -> chuỗi "101010"
string bitsToString(const vector<int> &bits) {
    string s;
    for (int b : bits) {
        s += (b ? '1' : '0');
    }
    return s;
}

// Hàm mã hóa/giải mã
string encryptDecrypt(const string &inputBits, const vector<int> &key) {
    // Tạo 3 LFSR
    LFSR r1(5, {1, 2}, 2);
    LFSR r2(5, {2, 3}, 1);
    LFSR r3(5, {1, 4}, 3);
    initWithKey(r1, r2, r3, key);

    vector<int> input = stringToBits(inputBits);
    vector<int> keystream = generateKeystream(input.size(), r1, r2, r3);
    vector<int> output = xorBits(input, keystream);

    return bitsToString(output);
}
string stringToBinary(const string &input) {
    string binaryString = "";
    for (char c : input) {
        bitset<8> bits((int)c);
        binaryString += bits.to_string();
    }
    return binaryString;
}

string binaryToString(const string &binaryInput) {
    string result = "";
    for (size_t i = 0; i < binaryInput.size(); i += 8) {
        string byte = binaryInput.substr(i, 8);
        char c = (char)bitset<8>(byte).to_ulong();
        result += c;
    }
    return result;
}
vector<int> generateKey(int length){
    vector<int> key;
    srand(time(0));
    for (int i=0; i<length; i++){
        key.push_back(rand() % 2);
    }
    return key;
}
vector<int> stringToBitVector(const string &binaryStr) {
    vector<int> bits;
    for (char c : binaryStr) {
        if (c == '0') bits.push_back(0);
        else if (c == '1') bits.push_back(1);
        else {
            cerr << "Ký tự không hợp lệ trong chuỗi nhị phân: " << c << endl;
        }
    }
    return bits;
}

int main() {
    string plaintext = "nhanguyen";
    vector<int> key = generateKey(10);
    string keyTemp;
    cout <<"enter plaintext: ";
    cin >> plaintext;
    string ciphertext = encryptDecrypt(stringToBinary(plaintext), key); 
    cout << "Ciphertext: " << ciphertext << endl;
    cout<<"key: ";
    for (int i : key){
        cout<<i;
    }
    cout<<"\n";
    cout<<"enter ciphertext: ";
    cin>>ciphertext;
    cout<<"Enter key: ";
    cin>>keyTemp;
    plaintext = binaryToString(encryptDecrypt(ciphertext,stringToBitVector(keyTemp)));
    cout<<"plain text: "<<plaintext;
    return 0;
}
