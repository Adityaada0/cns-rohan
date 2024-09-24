#include <iostream>
#include <vector>
#include <string>

using namespace std;

string decryptRailFence(string cipher, int key) {
    // Create the rail matrix filled with spaces
    vector<vector<char>> rail(key, vector<char>(cipher.length(), ' '));

    // Mark the zigzag pattern in the matrix
    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        // Change direction when we hit the top or bottom rail
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        // Mark the position for placing a character later
        rail[row][col++] = '*';

        // Move to the next row in zigzag pattern
        dir_down ? row++ : row--;
    }

    // Fill the cipher text in the zigzag pattern
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < cipher.length(); j++) {
            // Replace the '*' positions with actual characters from the cipher
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];
        }
    }

    // Read the decrypted text from the zigzag pattern
    string result;
    row = 0, col = 0;
    dir_down = false;  // Reset direction for reading the zigzag pattern
    for (int i = 0; i < cipher.length(); i++) {
        // Append the character from the current rail and column
        result.push_back(rail[row][col++]);

        // Change direction at the top or bottom rail
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        // Move in the zigzag pattern
        dir_down ? row++ : row--;
    }

    return result;
}

int main() {
    string encryptedText = "rtjaanmeji";
    int key = 3;

    string decryptedText = decryptRailFence(encryptedText, key);
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}
