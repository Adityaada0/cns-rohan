#include <iostream>
#include <vector>
#include <algorithm>

void columnarTranspositionEncrypt(const std::string& text, const std::string& keyword, std::string& encryptedText) {
    int numCols = keyword.size();
    int numRows = (text.size() + numCols - 1) / numCols; // Calculate number of rows required
    // Fill the grid
    std::vector<std::vector<char>> grid(numRows, std::vector<char>(numCols, ' '));
    for (int i = 0; i < text.size(); ++i) {
        grid[i / numCols][i % numCols] = text[i];
    }

    // Create a vector of column indices sorted by keyword order
    std::vector<int> colOrder(numCols);
    for (int i = 0; i < numCols; ++i) {
        colOrder[i] = i;
    }
    std::sort(colOrder.begin(), colOrder.end(), [&keyword](int i1, int i2) {
        return keyword[i1] < keyword[i2];
    });
        encryptedText.clear();
    for (int i : colOrder) {
        for (int j = 0; j < numRows; ++j) {
            if (grid[j][i] != ' ') {
                encryptedText += grid[j][i];
            }
        }
    }
}
int main() {
    std::string text = "rohan";
    std::string keyword = "KEYW";
    std::string encryptedText;

    columnarTranspositionEncrypt(text, keyword, encryptedText);

    std::cout << "Encrypted Text: " << encryptedText << std::endl;

    return 0;
}

