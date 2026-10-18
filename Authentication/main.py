# Assignment 6: Authentication
# Luke Colehower

import hashlib
import os
import json

USER_FILE = "users.json"


def load_users():
    """LOAD USER DATA FROM JSON FILE"""

    if not os.path.exists(USER_FILE):
        return {}

    with open(USER_FILE, "r") as f:
        return json.load(f)


def save_users(users):
    """SAVE USER DATA TO JSON FILE"""
    with open(USER_FILE, "w") as f:
        json.dump(users, f, indent=4)

def hash_password(password, salt=None):
    """HASH PASSWORD WITH SHA-256 AND A RANDOM SALT"""
    if salt is None:
        salt = os.urandom(16).hex()

    hashed = hashlib.sha256((salt + password).encode()).hexdigest()

    return hashed, salt


def register_user():
    users = load_users()

    username = input("Enter New Username: ").strip()

    if username in users:
        print("Username Already Exists.")
        return

    password = input("Enter New Password: ").strip()

    hashed, salt = hash_password(password)

    users[username] = {
        "salt": salt,
        "hashed": hashed
    }

    save_users(users)

    print(f"User {username} has been registered.")


def login_user():
    users = load_users()

    username = input("Enter Username: ").strip()

    if username not in users:
        print("Username Does Not Exist. Please Register First.")
        return

    password = input("Enter Password: ").strip()

    salt = users[username]["salt"]

    hashed, _ = hash_password(password, salt)

    if hashed == users[username]["hashed"]:
        print(f"User {username} has logged in Successfully. Welcome.")
    else:
        print("Incorrect Password. Access Denied.")


def main():
    print("====== Secure Authentication System ======")
    print("1: Register")
    print("2: Login")


    choice = input("Select Option (1/2): ")

    if choice == "1":
        register_user()

    elif choice == "2":
        login_user()

        return

    else:
        print("Incorrect Option. Please Select 1 or 2.")


if __name__ == "__main__":
    main()