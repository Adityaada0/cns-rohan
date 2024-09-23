#include<iostream>
using namespace std;

// Function to decrypt the message using Caesar Cipher
string decrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i]))
            result += char(int(text[i] - shift - 65 + 26) % 26 + 65);  
        else
            result += char(int(text[i] - shift - 97 + 26) % 26 + 97);  
    }

    return result;
}

int main() {
    string cipherText = "FinydfFbfymfwj";
    int shift = 5;

    cout << "Cipher Text: " << cipherText << endl;
    cout << "Shift: " << shift << endl;
    cout << "Decrypted Text: " << decrypt(cipherText, shift) << endl;

    return 0;
}
