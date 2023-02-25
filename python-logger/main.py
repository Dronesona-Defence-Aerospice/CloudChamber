import serial
import glob

from datetime import datetime

# arduino_port = None


# ports = glob.glob('/dev/tty.*') 

# for port in ports:
#     print(port)
#     if 'cu.usbmodem1201' in port:
#         arduino_port = port


serial_port = serial.Serial('/dev/cu.usbmodem11201', 115200)
a = 1
with open(f'temperature - {datetime.now()}.log', 'a') as debug_file:
    while True:
        if serial_port.in_waiting:
            try:
                data = f'{datetime.now()} - {serial_port.readline().decode()}'
                debug_file.write(data)
                a = a + 1           
                print(data)
                if a >= 3:
                    print('---------------------------------')
                    a = 0
            except Exception as e:
                print(f'error: {e}')
