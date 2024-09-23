#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to simulate DES encryption
void simulateDESEncryption(const string& plaintext) {
    
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Encrypted:") != string::npos) {
                cout << line << endl; 
            }
        }
        file.close();
    } else {
        cout << "Unable to open the file 'encryption.txt'!" << endl;
    }
}

int main() {
    string plaintext;

    cout << "plaintext : ";
    cin >> plaintext;

    simulateDESEncryption(plaintext);

    return 0;
}
