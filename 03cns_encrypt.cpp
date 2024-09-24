#include<iostream>
using namespace std;
string encrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i <text.length(); i++){
        if (isupper(text[i]))
            result += char(int(text[i] + shift -65) % 26 +65);
        else
            result += char(int(text[i] + shift -97) % 26 + 97);
        
    }

    return result;
}


int main() {
    string text = "RohanNakade";
    int shift = 5;
    cout <<"Text: "<< text << endl;
    cout <<"Shift: "<< shift << endl;
    cout <<"Cipher: "<<encrypt(text, shift)<< endl;

    return 0; 

}