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
    std::string encryptedText = "049a8a270a0257c6";
    std::string key = "12345678"; 
    
    std::cout << "Encrypted Text: " << encryptedText << std::endl;

    std::string decryptedText = runDES("decrypt", encryptedText, key);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;
    return 0;
}
