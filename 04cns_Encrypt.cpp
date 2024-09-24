#include <bits/stdc++.h>
using namespace std;

string encryptRailFence(string text, int key) {
    char rail[key][text.length()];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < text.length(); i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][col++] = text[i];
        dir_down ? row++ : row--;
    }

    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);
    return result;
}

int main() {
    string plainText = "amaolhanrinkhede";
    int key = 3;

    string encryptedText = encryptRailFence(plainText, key);
    cout << "Encrypted: " << encryptedText << endl;

    return 0;
}

