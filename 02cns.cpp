#include <iostream>
#include <bitset>
#include <string>

using namespace std;

void encryptMessage(const string& message) {
    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message:  ";

    for (char c : message) {
        bitset<7> binaryRepresentation(c);
        cout << binaryRepresentation << " ";
    }
    cout << endl;
}

int main() {
    string message = "CRYPTOGRAPHY AND NETWORK SECURITY";
    encryptMessage(message);

    return 0;
}
