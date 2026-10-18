# Assignment 5 - File Integrity in SHA-256
# Luke Colehower

import hashlib
import os


def generate_hash(file_path):
    """Generate SHA-256 Hash of a File."""
    sha256_hash = hashlib.sha256()

    try:
        with open(file_path, "rb") as f:
            for byte_block in iter(lambda: f.read(4096), b""):
                sha256_hash.update(byte_block)

        hash_value = sha256_hash.hexdigest()

        with open(file_path + ".hash", "w") as hash_file:
            hash_file.write(hash_value)

        print("Hash Generated and Saved as " + file_path + ".hash")
        print("SHA-256: " + hash_value)

    except FileNotFoundError:
        print("Error: File Not Found")

    except PermissionError:
        print("Error: Permission Denied")


def verify_hash(file_path):
    """Verify the Integrity of a File by Comparing Stored Hash."""

    hash_file_path = file_path + ".hash"

    if not os.path.exists(file_path):
        print("Error: File Not Found")
        return

    if not os.path.exists(hash_file_path):
        print("Error: No Stored Hash Found. Please Generate a Hash First")
        return

    sha256_hash = hashlib.sha256()

    try:
        with open(file_path, "rb") as f:
            for byte_block in iter(lambda: f.read(4096), b""):
                sha256_hash.update(byte_block)

        current_hash = sha256_hash.hexdigest()

        with open(hash_file_path, "r") as hash_file:
            stored_hash = hash_file.read().strip()

        print("Stored SHA-256: " + stored_hash)
        print("Current SHA-256: " + current_hash)

        if current_hash == stored_hash:
            print("File Verified Successfully. Integrity Intact.")
        else:
            print("Warning: File Integrity Check Failed!")
            print("Current Hash Does Not Match the Stored Hash Value.")

    except PermissionError:
        print("Error: Permission Denied")


def main():
    print("======= FILE INTEGRITY CHECKER (SHA-256) =======")
    print("1. Generate Hash For a File")
    print("2. Verify File Integrity")
    print("3. Exit")

    choice = input("Select Mode (1/2/3): ")

    if choice == "1":
        file_path = input("Enter File Path: ")
        generate_hash(file_path)

    elif choice == "2":
        file_path = input("Enter File Path: ")
        verify_hash(file_path)

    elif choice == "3":
        print("Exiting...")
        return

    else:
        print("Invalid Choice. Exiting...")
        return


if __name__ == "__main__":
    main()

