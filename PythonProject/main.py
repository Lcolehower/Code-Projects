import base64
import codecs

encoded_msg = "3Pilv6Wvure4t/avtbizo6ezpLD2vqK/ofalprqzvvaio7T2ori3oLO6s6Skv/alv/aiuLOiuLm19rO+ovawufaipbOk9rO+gtz44uLg4PuSgpGB+4+dhfbssbe6sPazvqL2urezoLOk9rq6v6H2pb+lr7q3uLf2uqOws6S3ldz4s7q0t7K3s6T2sri39rq3pKOit7j2vbm5uva5ovays7ixv6Wzsvaks7q6v7D2oqWjvPalv/airrOi9qW/vqL2sLn2oqW5m9z4s7G3paWzu/a4s7Kyv772t/als7+69r6mt6Sxt6S3pvavpLe4v7Kkufazpb+hpLO+orn2pb++ovawufazurKyv7v2s76i9rif"

# 1. Padding
missing_padding = len(encoded_msg) % 4
if missing_padding:
    encoded_msg += '=' * (4 - missing_padding)

# 2. Decode, Reverse, and Bitwise NOT
raw_bytes = base64.b64decode(encoded_msg)
reversed_bytes = raw_bytes[::-1]
flipped_bytes = bytes([b ^ 0xFF for b in reversed_bytes])

# 3. Apply the ROT13 shift to the flipped data
# We use Shift 09 as our baseline because it had the right word lengths
best_guess_bytes = bytes([(b - 9) % 256 for b in flipped_bytes])
intermediate_text = best_guess_bytes.decode('utf-8', errors='ignore')

# 4. Final ROT13 Unmasking
final_output = codecs.encode(intermediate_text, 'rot_13')

print("--- DECODED FLAG MESSAGE ---")
print(final_output)