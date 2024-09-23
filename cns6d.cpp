#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to simulate DES decryption
void simulateDESDecryption(const string& encryptedText) {
  
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Plaintext:") != string::npos) {
                cout << line << endl; // Output the plaintext
            }
        }
        file.close();
    } else {
        cout << "Unable to run!" << endl;
    }
}

int main() {
    string encryptedText;

    cout << "encrypted text : ";
    cin >> encryptedText;

    simulateDESDecryption(encryptedText);

    return 0;
}
