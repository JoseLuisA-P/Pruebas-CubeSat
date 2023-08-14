import serial
import time

SERIAL_PORT = 'COM4'
BAUD_RATE = 9600
message_test = [105, 42,43,44,45, 102] # 105 corresponde a "i" y 102 a "f"
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
def receive_data_with_ack():
    
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

# Funciones de callback para manejar las respuestas del esclavo
def ack_callback():
    # Puedes implementar acciones en caso de ACK recibido
    pass

def nack_callback():
    # Puedes implementar acciones en caso de NACK recibido
    pass

def send_package(message):
        retries = 0
        max_retries = 3
        while retries < max_retries:
            ser.dtr = True  # Comienza la transmisión
            ser.write(message)
            start_time = time.time()
            
            while time.time() - start_time < ser.timeout:
                ser.dtr = False  # Cambia a modo de recepción
                temp = ser.read(1)
                
                if temp == b'A':  # Recibe el ACK
                    ack_callback()
                    print("Data sent successfully!")
                    return
                    
                elif temp == b'N':  # Recibe el NACK
                    nack_callback()
                    print("NACK received, retrying...")
                    retries += 1
                    break
                    
        print("Failed after many attempts")


# if __name__ == "__main__":
#    send_package(message_test) # definir

# ciclo de escucha y trasmision
