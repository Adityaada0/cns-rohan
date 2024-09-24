#include <iostream>
#include <vector>
#include <algorithm>

void columnarTranspositionDecrypt(const std::string& encryptedText, const std::string& keyword, std::string& decryptedText) {
    int numCols = keyword.size();
    int numRows = (encryptedText.size() + numCols - 1) / numCols;

    // Create a vector of column indices sorted by keyword order
    std::vector<int> colOrder(numCols);
    for (int i = 0; i < numCols; ++i) {
        colOrder[i] = i;
    }
    std::sort(colOrder.begin(), colOrder.end(), [&keyword](int i1, int i2) {
        return keyword[i1] < keyword[i2];
    });

    // Calculate the number of characters in each column
    std::vector<int> colHeights(numCols, numRows);  // All columns have `numRows` rows by default
    int shortCols = numCols * numRows - encryptedText.size();  // Columns that will have fewer characters
    for (int i = 0; i < shortCols; ++i) {
        colHeights[colOrder[numCols - 1 - i]]--;  // Shorter columns are at the end of the sorted order
    }

    // Fill the grid based on the encrypted text
    std::vector<std::vector<char>> grid(numRows, std::vector<char>(numCols, ' '));
    int currentChar = 0;
    for (int colIdx : colOrder) {
        for (int row = 0; row < colHeights[colIdx]; ++row) {
            if (currentChar < encryptedText.size()) {
                grid[row][colIdx] = encryptedText[currentChar++];
            }
        }
    }

    // Read the grid row by row to get the decrypted text
    decryptedText.clear();
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (grid[row][col] != ' ') {
                decryptedText += grid[row][col];
            }
        }
    }
}

int main() {
    std::string encryptedText = "hntcautaer";
    std::string keyword = "KEYW";
    std::string decryptedText;

    columnarTranspositionDecrypt(encryptedText, keyword, decryptedText);

    std::cout << "Decrypted Text: "<<decryptedText << std::endl;

    return 0;
}
