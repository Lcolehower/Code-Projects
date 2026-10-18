# ECDSA - Assignment 4
# Luke Colehower

from Crypto.PublicKey import ECC
from Crypto.Signature import DSS
from Crypto.Hash import SHA256


def generate_ecdsa_keys():
    """Generates an ECDSA private and public key pair."""
    key = ECC.generate(curve='P-256')
    return key, key.public_key()


def verify_signature(public_key, message, signature):
    """Verifies an ECDSA signature."""

    hash_message = SHA256.new(message)

    verifier = DSS.new(public_key, 'fips-186-3')

    try:
        verifier.verify(hash_message, signature)
        return True
    except ValueError:
        return False


def main():

    # Import the provided public key
    with open("public_key.pem", "rt") as key_file:
        public_key = ECC.import_key(key_file.read())

    # Read messages
    with open("message1.bin", "rb") as file:
        message1 = file.read()

    with open("message2.bin", "rb") as file:
        message2 = file.read()

    # Read signatures
    with open("signature1.bin", "rb") as file:
        signature1 = file.read()

    with open("signature2.bin", "rb") as file:
        signature2 = file.read()

    # Verify all four combinations
    print("Message 1 with Signature 1:",
          verify_signature(public_key, message1, signature1))

    print("Message 1 with Signature 2:",
          verify_signature(public_key, message1, signature2))

    print("Message 2 with Signature 1:",
          verify_signature(public_key, message2, signature1))

    print("Message 2 with Signature 2:",
          verify_signature(public_key, message2, signature2))


if __name__ == "__main__":
    main()