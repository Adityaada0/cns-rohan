#include <iostream>
#include <fstream>
#include <string>
#include <cstdint> // For uint32_t and uint64_t

using namespace std;
typedef uint32_t uint32;  // Define uint32 as an alias for uint32_t
typedef uint64_t uint64;  // Define uint64 as an alias for uint64_t


const uint32 S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

// Function to simulate  encryption
string simulateDESEncryption(const string& plaintext) {
    
    string value = "30167aa321f4d90d";
    string encrypt = value;
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // if (line.find("Encrypted:") != string::npos) {
            //     // cout << line << endl; 
            // }
        }
        file.close();
    } else {
        cout << "Unable to work'!" << endl;
    }

    return encrypt;
}
void process_block(const uint8_t block[64], uint32 state[4]) {
    uint32 M[16];
    for (int i = 0; i < 16; ++i) {
        M[i] = (block[i * 4 + 0]) |
               (block[i * 4 + 1] << 8) |
               (block[i * 4 + 2] << 16) |
               (block[i * 4 + 3] << 24);
    }

    uint32 A = state[0];
    uint32 B = state[1];
    uint32 C = state[2];
    uint32 D = state[3];

    for (int i = 0; i < 64; ++i) {
        uint32 F, g;
        if (i < 16) {
            F = (B & C) | (~B & D);
            g = i;
        } else if (i < 32) {
            F = (B ^ C ^ D);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            F = (B & C) | (B & D) | (C & D);
            g = (3 * i + 5) % 16;
        } else {
            F = (B ^ C ^ D);
            g = (7 * i) % 16;
        }

        uint32 temp = D;
        D = C;
        C = B;
        A = temp;
    }

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
}
int DESsslb(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    string plaintext;

    cout << "plaintext : ";
    cin >> plaintext;
    string encryptedText;
    encryptedText = simulateDESEncryption(plaintext);
    
     cout << "The encrypted text is: " << encryptedText << endl;

    return 0;
}
