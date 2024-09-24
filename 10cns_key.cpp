#include <iostream>
#include <cmath>
unsigned long long mod_exp(unsigned long long base, unsigned long long exponent, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) { 
            result = (result * base) % mod;
        }
        exponent = exponent >> 1; 
        base = (base * base) % mod; 
    }
    return result;
}
int main() {

    unsigned long long p = 11; // A prime number
    unsigned long long g = 9;  // A primitive root modulo p
    // Private keys (kept secret)
    unsigned long long a = 4; // Alice's private key
    unsigned long long b = 3; // Bob's private key

    // Public keys
    unsigned long long A = mod_exp(g, a, p); // Alice's public key
    unsigned long long B = mod_exp(g, b, p); // Bob's public key
    // Exchange public keys and compute shared secret
    unsigned long long shared_secret_A = mod_exp(B, a, p); // Alice computes the shared secret
    unsigned long long shared_secret_B = mod_exp(A, b, p); // Bob computes the shared secret
    std::cout << "Public Parameters: p = " << p << ", g = " << g << std::endl;
    std::cout << "Alice's Private Key: " << a << std::endl;
    std::cout << "Bob's Private Key: " << b << std::endl;
    std::cout << "Alice's Public Key: " << A << std::endl;
    std::cout << "Bob's Public Key: " << B << std::endl;
    std::cout << "Shared Secret Computed by Alice: " << shared_secret_A << std::endl;
    std::cout << "Shared Secret Computed by Bob: " << shared_secret_B << std::endl;
    return 0;
}
