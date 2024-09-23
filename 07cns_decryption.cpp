#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int modExp(int base, int exp, int mod) {
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

int nextPrime(int start) {
    while (!isPrime(start)) {
        start++;
    }
    return start;
}

void generateKeys(int &n, int &e, int &d, int p, int q) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    e = 2;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }
    int k = 1;
    while ((k * phi + 1) % e != 0) {
        k++;
    }
    d = (k * phi + 1) / e;
}

int encrypt(int message, int e, int n) {
    return modExp(message, e, n);
}

int decrypt(int encryptedMessage, int d, int n) {
    return modExp(encryptedMessage, d, n);
}

int main() {
    int p, q;
    std::cout << "Enter prime number p: ";
    std::cin >> p;
    std::cout << "Enter prime number q: ";
    std::cin >> q;

    if (!isPrime(p) || !isPrime(q)) {
        std::cerr << "Both numbers must be prime.\n";
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));
    int n, e, d;
    generateKeys(n, e, d, p, q);
    
  
   

    // Encrypt the message
    int encryptedMessage ;
    std::cout<<"Enter the encrypted message ";
    std::cin>> encryptedMessage;
    

    // Save the keys to a file
    std::ofstream keyFile("rsa_keys.txt");
    keyFile << n << '\n' << e << '\n' << d;
    keyFile.close();

    // Save the encrypted message
    std::ofstream encFile("encrypted_message.txt");
    encFile << encryptedMessage;
    encFile.close();

    // Read keys from file for decryption
    std::ifstream keyFileIn("rsa_keys.txt");
    if (keyFileIn.is_open()) {
        keyFileIn >> n >> e >> d;
        keyFileIn.close();
    } else {
        std::cerr << "Error opening key file\n";
        return 1;
    }

    // Read the encrypted message from file
    std::ifstream encFileIn("encrypted_message.txt");
    if (encFileIn.is_open()) {
        encFileIn >> encryptedMessage;
        encFileIn.close();
    } else {
        std::cerr << "Error opening encrypted message file\n";
        return 1;
    }

    // Decrypt the message
    int decryptedMessage = decrypt(encryptedMessage, d, n);
    std::cout << "Decrypted Message: " << decryptedMessage << "\n";

    return 0;
}
