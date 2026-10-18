# Assignement 2 - Symmetric Key
# Luke Colehower

import ast
import time
from base64 import b64decode
from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes


def decrypt_aes_gcm(encrypted_data, key):

    ciphertext = b64decode(encrypted_data['ciphertext'])
    nonce = b64decode(encrypted_data['nonce'])
    tag = b64decode(encrypted_data['tag'])

    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    plaintext = cipher.decrypt_and_verify(ciphertext, tag)

    return plaintext.decode('utf-8')


def brute_force_decrypt_aes_gcm(text: str) -> str:

    encrypted_data = ast.literal_eval(text)

    for attempt in range(100000):
        aes_key = get_random_bytes(32)

        try:
            plaintext = decrypt_aes_gcm(encrypted_data, aes_key)

            print(f"Key found on attempt {attempt + 1}!")
            print(f"AES Key: {aes_key.hex()}")

            return plaintext

        except (ValueError, KeyError, UnicodeDecodeError):
            # Incorrect key or invalid authentication tag
            continue

    return "Key was not found in 100,000 attempts."


def main():
    # Read encrypted message from the provided text file
    with open("Assignment 2 - Encrypted Text.txt", "r") as file:
        encrypted_text = file.read()

    # Measure time before brute-force attack
    start_time = time.perf_counter()

    plaintext = brute_force_decrypt_aes_gcm(encrypted_text)

    # Measure time after brute-force attack
    end_time = time.perf_counter()

    elapsed_time = end_time - start_time

    # Estimate time for a complete AES-256 brute-force attack
    estimated_time = elapsed_time * (2**256 / 100000)

    print("\n----- Results -----")
    print(f"Plaintext: {plaintext}")
    print(f"Time for 100,000 attempts: {elapsed_time:.6f} seconds")
    print(f"Estimated full AES-256 brute-force time: {estimated_time:.6e} seconds")


if __name__ == "__main__":
    main()