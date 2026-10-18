# Assignment 3
# Luke Colehower

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP


def generate_keys():
    """
    Generates a 2048-bit RSA public/private key pair
    and saves them to files.
    """

    # Generate a 2048-bit RSA key pair
    key = RSA.generate(2048)

    # Export the private key
    private_key = key.export_key()

    # Export the public key
    public_key = key.publickey().export_key()

    # Save the public key to public_key.pem
    with open("public_key.pem", "wb") as public_file:
        public_file.write(public_key)

    # Save the private key to private_key.pem
    with open("private_key.pem", "wb") as private_file:
        private_file.write(private_key)


def encrypt_message(message):
    """
    Reads the public key, encrypts the message using RSA-OAEP,
    and saves the ciphertext to message.enc.
    """

    # Read the public key
    with open("public_key.pem", "rb") as public_file:
        public_key = RSA.import_key(public_file.read())

    # Create the RSA OAEP cipher using the public key
    cipher = PKCS1_OAEP.new(public_key)

    # Convert the message from a string to bytes
    message_bytes = message.encode("utf-8")

    # Encrypt the message
    ciphertext = cipher.encrypt(message_bytes)

    # Save the ciphertext to message.enc
    with open("message.enc", "wb") as encrypted_file:
        encrypted_file.write(ciphertext)


def decrypt_message():
    """
    Reads the ciphertext and private key, decrypts the message,
    and returns the plaintext.
    """

    # Read the ciphertext from message.enc
    with open("message.enc", "rb") as encrypted_file:
        ciphertext = encrypted_file.read()

    # Read the private key
    with open("private_key.pem", "rb") as private_file:
        private_key = RSA.import_key(private_file.read())

    # Create the RSA OAEP cipher using the private key
    cipher = PKCS1_OAEP.new(private_key)

    # Decrypt the ciphertext
    plaintext = cipher.decrypt(ciphertext)

    # Convert the plaintext from bytes back to a string
    return plaintext.decode("utf-8")


# Main program
if __name__ == "__main__":

    # Generate the RSA key pair
    generate_keys()

    # Replace this with your actual Rowan Banner ID
    banner_id = "YOUR_ROWAN_BANNER_ID"

    # Encrypt the Banner ID
    encrypt_message(banner_id)

    # Decrypt and print the Banner ID
    print(decrypt_message())