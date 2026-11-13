def crc_division(data, generator):
    temp = list(data)
    data_len = len(data)
    gen_len = len(generator)

    for i in range(data_len - gen_len + 1):
        if temp[i] == '1':
            for j in range(gen_len):
                if temp[i + j] == generator[j]:
                    temp[i + j] = '0'
                else:
                    temp[i + j] = '1'

    remainder = ''.join(temp[data_len - gen_len + 1:])
    return remainder


def word_to_binary(word):
    binary = ""

    for ch in word:
        ascii_value = ord(ch)

        for j in range(7, -1, -1):
            if ascii_value & (1 << j):
                binary += "1"
            else:
                binary += "0"

    return binary


word = input("Enter a word: ")
generator = "10011"

data = word_to_binary(word)

print("\nData in binary :", data)
print("Generator      :", generator)

padded_data = data + "0" * (len(generator) - 1)

remainder = crc_division(padded_data, generator)

print("CRC Remainder  :", remainder)

transmitted = data + remainder

print("Transmitted Data:", transmitted)


# CRC Basic
generator = "10011"

# CRC-12
generator = "1100000001111"

# CRC-16
generator = "11000000000000101"

# CRC-CCITT
generator = "10001000000100001"