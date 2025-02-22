#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Hàm đọc ma trận khóa từ file
vector<vector<int>> readKey(string fileName, int &n)
{
    ifstream file(fileName);
    if (!file)
    {
        cout << "Không thể mở tệp!" << endl;
        exit(1); // Thoát chương trình nếu file lỗi
    }

    file >> n; // Đọc kích thước ma trận

    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

// Hàm mã hóa Hill
string hillCipherEncrypt(string data, vector<vector<int>> key, int n)
{
    string ciphertext = "";
    vector<int> temp(n, 0); // Mảng lưu nhóm ký tự

    // Duyệt từng nhóm `n` ký tự trong data
    for (int  i = 0; i < data.size(); i += n)
    {
        for (int j = 0; j < n; j++)
        {
            if (i + j < data.size())
                temp[j] = data[i + j] - 'a'; 
            else
                temp[j] = 0; 
        }

        for (int row = 0; row < n; row++)
        {
            int sum = 0;
            for (int col = 0; col < n; col++)
            {
                sum += temp[col] * key[row][col];
            }
            ciphertext += (char)((sum % 26) + 'a'); // Đưa về ký tự chữ cái
        }
    }

    return ciphertext;
}

int main()
{
    int n;
    vector<vector<int>> key = readKey("key.txt", n);

    string data = "paymoremoney"; // Văn bản cần mã hóa
    string ciphertext = hillCipherEncrypt(data, key, n);

    cout << "Ciphertext: " << ciphertext << endl;
    return 0;
}
