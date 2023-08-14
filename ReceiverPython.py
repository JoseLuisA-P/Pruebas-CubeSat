import serial

SERIAL_PORT = 'COM14'
BAUD_RATE = 9600

def receive_data_with_ack():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    received_data = bytearray()
    received_ack = False

    while not received_ack:
        if ser.readable():
            received_data.extend(ser.read(4))

            if len(received_data) >= 1:
                print(str(received_data))
                # Enviar o recibir el ACK(A) o NACK(N)
                ser.write(b'N')

                received_ack = True

    ser.close()

def calculate_crc(data):
    CRC_POLYNOMIAL = 0x1021  # CRC-16-CCITT polynomial
    CRC_INITIAL = 0xFFFF     # Initial value for CRC calculation

    crc = CRC_INITIAL

    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = (crc << 1) ^ CRC_POLYNOMIAL
            else:
                crc <<= 1

    return crc & 0xFFFF  # Ensure the result is 16-bit


if __name__ == "__main__":
    receive_data_with_ack()
