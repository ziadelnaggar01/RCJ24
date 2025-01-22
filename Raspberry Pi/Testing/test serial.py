import serial

# Setup Serial connection
try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
except:
    ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)

ser.reset_input_buffer()
ser.write(b'a')

