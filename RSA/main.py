#Assignment 3 - RSA
# Luke Colehower

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP


def generate_keys():
    key = RSA.generate(2048)
    private_key = key.export_key()
    public_key = key.publickey().export_key()

    # Save the public key to public_key.pem
    with open("public_key.pem", "wb") as public_file:
        public_file.write(public_key)

    # Save the private key to private_key.pem
    with open("private_key.pem", "wb") as private_file:
        private_file.write(private_key)


def encrypt_message(message):
    with open("public_key.pem", "rb") as public_file:
        public_key = RSA.import_key(public_file.read())

    cipher = PKCS1_OAEP.new(public_key)
    message_bytes = message.encode("utf-8")
    ciphertext = cipher.encrypt(message_bytes)

    with open("message.enc", "wb") as encrypted_file:
        encrypted_file.write(ciphertext)


def decrypt_message():
    # Read the ciphertext from message.enc
    with open("message.enc", "rb") as encrypted_file:
        ciphertext = encrypted_file.read()

    # Read the private key
    with open("private_key.pem", "rb") as private_file:
        private_key = RSA.import_key(private_file.read())


    cipher = PKCS1_OAEP.new(private_key)
    plaintext = cipher.decrypt(ciphertext)

    return plaintext.decode("utf-8")


# Main program
if __name__ == "__main__":

    # Generate the RSA key pair
    generate_keys()

    banner_id = "916338857"
    encrypt_message(banner_id)
    print(decrypt_message())