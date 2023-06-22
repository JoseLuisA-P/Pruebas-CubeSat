import json
import serial
import random

if __name__=="__main__":
    print("Ready ...")
    ser = serial.Serial('COM6',baudrate=115200)

    if ser.isOpen():
        
        try:
            mensaje = 'Prueba\n'
            ser.write(mensaje.encode("utf-8"))
            ser.flush()
            echo = ser.readline().decode("utf-8")  
            print(echo);  

        except Exception as e:
            print(e)

        ser.close()

    else:
        print("No se pudo abrir el puerto")