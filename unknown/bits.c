
def bit_stuff_sender(data_bits):
    stuffed = []
    count_ones = 0
    for bit in data_bits:
        stuffed.append(bit)
        if bit == '1':
            count_ones += 1
            if count_ones == 5:
                stuffed.append('0')
                count_ones = 0
        else:
            count_ones = 0
    return ''.join(stuffed)

def bit_stuff_receiver(stuffed_bits):
    original = []
    count_ones = 0
    i = 0
    while i < len(stuffed_bits):
        original.append(stuffed_bits[i])
        if stuffed_bits[i] == '1':
            count_ones += 1
            if count_ones == 5:
                i += 1
                count_ones = 0
        else:
            count_ones = 0
        i += 1
    return ''.join(original)

def bit_stuff_flag(data_bits):
    FLAG = '01111110'
    stuffed = bit_stuff_sender(data_bits)
    return FLAG + stuffed + FLAG

def bit_unstuff_frame(frame_bits):
    FLAG = '01111110'
    if frame_bits.startswith(FLAG) and frame_bits.endswith(FLAG):
        data = frame_bits[len(FLAG):-len(FLAG)]
        return bit_stuff_receiver(data)
    else:
        print("Error: Invalid frame - missing flags!")
        return None

data = input("Enter data bits: ")
frame = bit_stuff_flag(data)
print("Transmitted Frame:", frame)
received = bit_unstuff_frame(frame)
print("Original Data:", received)
