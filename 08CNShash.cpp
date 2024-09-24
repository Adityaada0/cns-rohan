#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cstdint>
typedef uint32_t uint32;
typedef uint64_t uint64; 
uint32 leftrotate(uint32 x, uint32 c) {
    return (x << c) | (x >> (32 - c));
}
std::string sha1(const std::string& input) {
    uint32 h0 = 0x67452301;
    uint32 h1 = 0xEFCDAB89;
    uint32 h2 = 0x98BADCFE;
    uint32 h3 = 0x10325476;
    uint32 h4 = 0xC3D2E1F0;
    std::string padded_input = input;
    uint64 original_bit_length = padded_input.size() * 8;
    padded_input += static_cast<char>(0x80);
    while ((padded_input.size() * 8) % 512 != 448) {
        padded_input += static_cast<char>(0x00);
    }
    for (int i = 7; i >= 0; --i) {
        padded_input += static_cast<char>((original_bit_length >> (i * 8)) & 0xFF);
    }

    for (size_t chunk_start = 0; chunk_start < padded_input.size(); chunk_start += 64) {
        uint32 w[80];
    
        for (int i = 0; i < 16; ++i) {
            w[i] = (padded_input[chunk_start + i * 4 + 0] & 0xFF) << 24 |
                   (padded_input[chunk_start + i * 4 + 1] & 0xFF) << 16 |
                   (padded_input[chunk_start + i * 4 + 2] & 0xFF) << 8 |
                   (padded_input[chunk_start + i * 4 + 3] & 0xFF);
        }
       
        for (int i = 16; i < 80; ++i) {
            w[i] = leftrotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }
        uint32 a = h0;
        uint32 b = h1;
        uint32 c = h2;
        uint32 d = h3;
        uint32 e = h4;
        for (int i = 0; i < 80; ++i) {
            uint32 f, k;
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32 temp = leftrotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }
    std::stringstream result;
    result << std::hex << std::setfill('0') << std::setw(8) << h0
           << std::setw(8) << h1
           << std::setw(8) << h2
           << std::setw(8) << h3
           << std::setw(8) << h4;
    return result.str();
}
int main() {
    std::string input = "adityakhandagale";
    std::string output = sha1(input);
    std::cout << "Original Text: " << input << std::endl;
    std::cout << "SHA-1 Hash: " << output << std::endl;
    return 0;
}
