#include <iostream>
#include <cstdlib>
#include <string>

std::string runDES(const std::string& action, const std::string& text, const std::string& key) {
    std::string command = "python des_encrypt.py " + action + " " + text + " " + key;
    std::string result;
    char buffer[128];

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "Error executing !";
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

int main() {
    std::string plaintext = "harsh";
    std::string key = "12345678"; 

    std::cout<<"plain Text: "<<plaintext<< std::endl;
    std::string encryptedText = runDES("encrypt", plaintext, key);
    std::cout << "Encrypted Text: " << encryptedText << std::endl;
    encryptedText.erase(encryptedText.find_last_not_of("\n\r") + 1);
    return 0;
}
