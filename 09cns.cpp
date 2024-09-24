#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint> // For uint32_t and uint64_t

typedef uint32_t uint32;  // Define uint32 as an alias for uint32_t
typedef uint64_t uint64;  // Define uint64 as an alias for uint64_t

// Constants for MD5
const uint32 T[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x6d0312d8, 0x8c1fdc3b, 0x5bfebc37, 0x4f019c47, 0x7f9305a0
};

const uint32 S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

uint32 left_rotate(uint32 value, uint32 shift) {
    return (value << shift) | (value >> (32 - shift));
}

void md5_init(uint32 state[4]) {
    state[0] = 0x67452301;
    state[1] = 0xEFCDAB89;
    state[2] = 0x98BADCFE;
    state[3] = 0x10325476;
}

void md5_process_block(const uint8_t block[64], uint32 state[4]) {
    uint32 M[16];
    for (int i = 0; i < 16; ++i) {
        M[i] = (block[i * 4 + 0]) |
               (block[i * 4 + 1] << 8) |
               (block[i * 4 + 2] << 16) |
               (block[i * 4 + 3] << 24);
    }

    uint32 A = state[0];
    uint32 B = state[1];
    uint32 C = state[2];
    uint32 D = state[3];

    for (int i = 0; i < 64; ++i) {
        uint32 F, g;
        if (i < 16) {
            F = (B & C) | (~B & D);
            g = i;
        } else if (i < 32) {
            F = (B ^ C ^ D);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            F = (B & C) | (B & D) | (C & D);
            g = (3 * i + 5) % 16;
        } else {
            F = (B ^ C ^ D);
            g = (7 * i) % 16;
        }

        uint32 temp = D;
        D = C;
        C = B;
        B = B + left_rotate(A + F + T[i] + M[g], S[i]);
        A = temp;
    }

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
}

// Pad the input and process blocks
std::string md5(const std::string& input) {
    uint32 state[4];
    md5_init(state);

    std::string padded_input = input;
    uint64_t original_bit_length = padded_input.size() * 8;

    padded_input += static_cast<char>(0x80);

    while ((padded_input.size() * 8) % 512 != 448) {
        padded_input += static_cast<char>(0x00);
    }

    for (int i = 0; i < 8; ++i) {
        padded_input += static_cast<char>((original_bit_length >> (i * 8)) & 0xFF);
    }

    for (size_t i = 0; i < padded_input.size(); i += 64) {
        md5_process_block(reinterpret_cast<const uint8_t*>(&padded_input[i]), state);
    }

    std::stringstream result;
    result << std::hex << std::setfill('0');
    for (int i = 0; i < 4; ++i) {
        result << std::setw(8) << state[i];
    }

    return result.str();
}

int main() {
    std::string input = "adityagondane";
    std::string output = md5(input);

    std::cout << "Original Text: " << input << std::endl;
    std::cout << "MD5 Hash: " << output << std::endl;

    return 0;
}
