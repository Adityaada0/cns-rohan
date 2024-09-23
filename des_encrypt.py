# des_encrypt.py
from Crypto.Cipher import DES
import sys

def des_encrypt(plaintext, key):
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.encrypt(plaintext.ljust(8).encode('utf-8')).hex()

def des_decrypt(ciphertext, key):
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.decrypt(bytes.fromhex(ciphertext)).strip().decode('utf-8')

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python des_encrypt.py <action> <text> <key>")
        sys.exit(1)

    action = sys.argv[1]  # "encrypt" or "decrypt"
    text = sys.argv[2]
    key = sys.argv[3].encode()

    if action == "encrypt":
        print(des_encrypt(text, key))
    elif action == "decrypt":
        print(des_decrypt(text, key))
