#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstring> // for std::memcpy
#include <algorithm> // for std::reverse



using namespace std;

// Initial Permutation table
int initial_permutation[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation table
int final_permutation[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion table
int expansion_table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 
    6, 7, 8, 9, 8, 9, 10, 11, 
    12, 13, 12, 13, 14, 15, 16, 17, 
    16, 17, 18, 19, 20, 21, 20, 21, 
    22, 23, 24, 25, 24, 25, 26, 27, 
    28, 29, 28, 29, 30, 31, 32, 1
};

// S-boxes
int s_boxes[8][4][16] = {
    { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
      {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
      {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
      {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} },
    { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
      {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
      {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
      {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} },
    { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
      {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
      {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
      {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} },
    { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
      {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
      {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
      {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} },
    { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
      {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
      {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
      {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} },
    { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
      {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
      {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
      {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} },
    { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
      {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
      {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
      {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} },
    { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
      {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
      {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
      {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} }
};

// Permutation table
int permutation_table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 
    1, 15, 23, 26, 5, 18, 31, 10, 
    2, 8, 24, 14, 32, 27, 3, 9, 
    19, 13, 30, 6, 22, 11, 4, 25
};

// Permuted choice 1 table
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permuted choice 2 table
int pc2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

// Left shifts for key schedule
int shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// Function to apply permutation to 64-bit block
bitset<64> apply_permutation(bitset<64> input, int permutation_table[], int size) {
    bitset<64> output;
    for (int i = 0; i < size; i++) {
        output[size - 1 - i] = input[64 - permutation_table[i]];
    }
    return output;
}

// Function to expand 32-bit input to 48-bit using expansion table
bitset<48> expand(bitset<32> input) {
    bitset<48> output;
    for (int i = 0; i < 48; i++) {
        output[47 - i] = input[32 - expansion_table[i]];
    }
    return output;
}

// XOR two bitsets
template <size_t N>
bitset<N> xor_bitsets(bitset<N> a, bitset<N> b) {
    return a ^ b;
}

// F-function (complete S-box and permutation)
bitset<32> f_function(bitset<32> R, bitset<48> subkey) {
    bitset<48> expanded_R = expand(R);
    bitset<48> xored = xor_bitsets(expanded_R, subkey);

    // S-box substitution
    bitset<32> output;
    for (int i = 0; i < 8; i++) {
        int row = (xored[47 - (i * 6)] << 1) + xored[47 - (i * 6 + 5)];
        int col = (xored[47 - (i * 6 + 1)] << 3) + (xored[47 - (i * 6 + 2)] << 2) +
                  (xored[47 - (i * 6 + 3)] << 1) + xored[47 - (i * 6 + 4)];
        int sbox_val = s_boxes[i][row][col];
        for (int j = 0; j < 4; j++) {
            output[31 - (i * 4 + j)] = (sbox_val >> (3 - j)) & 1;
        }
    }

    // Permutation
    bitset<32> permuted_output;
    for (int i = 0; i < 32; i++) {
        permuted_output[31 - i] = output[32 - permutation_table[i]];
    }

    return permuted_output;
}

// DES encryption round
pair<bitset<32>, bitset<32>> des_round(pair<bitset<32>, bitset<32>> LR, bitset<48> subkey) {
    bitset<32> L = LR.first;
    bitset<32> R = LR.second;

    bitset<32> new_L = R;
    bitset<32> new_R = xor_bitsets(L, f_function(R, subkey));

    return make_pair(new_L, new_R);
}

// Key schedule
vector<bitset<48>> generate_subkeys(bitset<64> key) {
    vector<bitset<48>> subkeys;

    // Apply PC1 to get the initial key
    bitset<56> permuted_key;
    for (int i = 0; i < 56; i++) {
        permuted_key[55 - i] = key[64 - pc1[i]];
    }

    // Split into left and right halves
    bitset<28> C = static_cast<unsigned long>(permuted_key.to_ullong()) >> 28; // Correct conversion
    bitset<28> D = static_cast<unsigned long>(permuted_key.to_ullong()) & 0xFFFFFFF; // Correct conversion

    // Generate 16 subkeys
    for (int i = 0; i < 16; i++) {
        // Perform left shifts
        C = (C << shifts[i]) | (C >> (28 - shifts[i]));
        D = (D << shifts[i]) | (D >> (28 - shifts[i]));

        // Combine C and D, and apply PC2 to get the subkey
        bitset<56> combined = (C.to_ullong() << 28) | D.to_ullong(); // Correct conversion
        bitset<48> subkey;
        for (int j = 0; j < 48; j++) {
            subkey[47 - j] = combined[56 - pc2[j]];
        }
        subkeys.push_back(subkey);
    }

    return subkeys;
}

// DES encryption
bitset<64> des_encrypt(bitset<64> plaintext, bitset<64> key) {
    // Apply initial permutation
    bitset<64> permuted_plaintext = apply_permutation(plaintext, initial_permutation, 64);

    // Split the permuted plaintext into left and right halves
    bitset<32> L = (permuted_plaintext.to_ullong() >> 32) & 0xFFFFFFFF; // Correct extraction
    bitset<32> R = permuted_plaintext.to_ullong() & 0xFFFFFFFF; // Correct extraction

    // Generate 16 subkeys
    vector<bitset<48>> subkeys = generate_subkeys(key);

    // Perform 16 rounds of DES
    for (int i = 0; i < 16; i++) {
        pair<bitset<32>, bitset<32>> LR = des_round(make_pair(L, R), subkeys[i]);
        L = LR.first;
        R = LR.second;
    }

    // Combine L and R and apply the final permutation
    bitset<64> combined = (L.to_ullong() << 32) | R.to_ullong(); // Correct conversion
    bitset<64> ciphertext = apply_permutation(combined, final_permutation, 64);

    return ciphertext;
}
// DES decryption
bitset<64> des_decrypt(bitset<64> ciphertext, bitset<64> key) {
    // Apply initial permutation
    bitset<64> permuted_ciphertext = apply_permutation(ciphertext, initial_permutation, 64);

    // Split the permuted ciphertext into left and right halves
    bitset<32> L = (permuted_ciphertext.to_ullong() >> 32) & 0xFFFFFFFF; // Left half
    bitset<32> R = permuted_ciphertext.to_ullong() & 0xFFFFFFFF; // Right half

    // Generate 16 subkeys (but in reverse order for decryption)
    vector<bitset<48>> subkeys = generate_subkeys(key);
    reverse(subkeys.begin(), subkeys.end()); // Reverse the subkeys for decryption

    // Perform 16 rounds of DES
    for (int i = 0; i < 16; i++) {
        pair<bitset<32>, bitset<32>> LR = des_round(make_pair(L, R), subkeys[i]);
        L = LR.first;
        R = LR.second;
    }

    // Combine L and R and apply the final permutation
    bitset<64> combined = (L.to_ullong() << 32) | R.to_ullong(); // Combine halves
    bitset<64> decrypted_text = apply_permutation(combined, final_permutation, 64); // Final permutation

    return decrypted_text;
}
int main() {
    // Encrypt the string "harsh"
    const char* str = "harsh"; // original string
    char padded_str[8] = {0}; // buffer for 8 bytes, initialized to 0

    // Copy the string and pad with zeros
    std::memcpy(padded_str, str, strlen(str));
    
    // Create a bitset from the padded string
    bitset<64> plaintext;
    for (int i = 0; i < 8; i++) {
        plaintext[i * 8]     = (padded_str[i] >> 7) & 1;
        plaintext[i * 8 + 1] = (padded_str[i] >> 6) & 1;
        plaintext[i * 8 + 2] = (padded_str[i] >> 5) & 1;
        plaintext[i * 8 + 3] = (padded_str[i] >> 4) & 1;
        plaintext[i * 8 + 4] = (padded_str[i] >> 3) & 1;
        plaintext[i * 8 + 5] = (padded_str[i] >> 2) & 1;
        plaintext[i * 8 + 6] = (padded_str[i] >> 1) & 1;
        plaintext[i * 8 + 7] = (padded_str[i] >> 0) & 1;
    }

    // Use the same key for encryption
    bitset<64> key(0x133457799BBCDFF1);

    // Encrypt the plaintext
    bitset<64> ciphertext = des_encrypt(plaintext, key);
    cout << "Ciphertext: " << hex << ciphertext.to_ullong() << endl;

    // Decrypt the ciphertext
    bitset<64> decrypted_text = des_decrypt(ciphertext, key);

    // Convert decrypted bitset back to string
    char decrypted_str[9] = {0}; // buffer for the original string + null terminator
    for (int i = 0; i < 8; i++) {
        decrypted_str[i] = 0;
        for (int j = 0; j < 8; j++) {
            decrypted_str[i] |= (decrypted_text[i * 8 + j] << (7 - j));
        }
    }

    // Output the decrypted plaintext
    cout << "Decrypted plaintext: " << decrypted_str << endl;

    return 0;
}