def char_stuff_sender(data_bytes):
    FLAG = 0x7E
    ESC = 0x7D
    stuffed = []
    for byte in data_bytes:
        if byte == FLAG or byte == ESC:
            stuffed.append(ESC)
            stuffed.append(byte ^ 0x20)
        else:
            stuffed.append(byte)

    return stuffed


def char_stuff_receiver(stuffed_bytes):
    ESC = 0x7D
    original = []
    i = 0

    while i < len(stuffed_bytes):

        if stuffed_bytes[i] == ESC:
            i += 1
            original.append(stuffed_bytes[i] ^ 0x20)

        else:
            original.append(stuffed_bytes[i])

        i += 1

    return original

data = [0x41, 0x7E, 0x42, 0x7D]

stuffed = char_stuff_sender(data)

print("Original Data:", data)
print("Stuffed Data:", stuffed)
received = char_stuff_receiver(stuffed)

print("Destuffed Data:", received)
