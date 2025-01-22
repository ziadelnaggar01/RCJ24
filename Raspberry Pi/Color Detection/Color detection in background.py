import cv2
import numpy as np
import serial
import RPi.GPIO as GPIO
import os
import time

# Set GPIO mode and pins
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
Button = 26

# Configure the button pin as an input with a pull-up resistor
GPIO.setup(Button, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Setup Serial connection
try:
    ser = serial.Serial('/dev/ttyUSB0', 300, timeout=1)
except:
    ser = serial.Serial('/dev/ttyUSB1', 300, timeout=1)
ser.reset_input_buffer()



# Define the color ranges for red, green, yellow in HSV
lred_lower1 = np .array([170, 150, 0])
lred_upper1 = np.array([179, 255, 255])

lred_lower2 = np.array([0, 150, 0])
lred_upper2 = np.array([10, 255, 255])

lgreen_lower = np.array([70, 115, 60])
lgreen_upper = np.array([82, 215, 120])

lyellow_lower = np.array([20, 150, 80])
lyellow_upper = np.array([30, 255, 225])


rred_lower1 = np .array([170, 150, 0])
rred_upper1 = np.array([179, 255, 255])

rred_lower2 = np.array([0, 150, 0])
rred_upper2 = np.array([10, 255, 255])

rgreen_lower = np.array([80, 150, 55])
rgreen_upper = np.array([90, 240, 130])

ryellow_lower = np.array([20, 80, 125]) # middle 80
ryellow_upper = np.array([35, 255, 215])

# Define the area boundaries
color_min = 23000


def masking(red_lower1, red_upper1, red_lower2, red_upper2, green_lower, green_upper, yellow_lower, yellow_upper):
    # Convert the frame from BGR to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create masks for each color
    red1 = cv2.inRange(hsv, red_lower1, red_upper1)
    red2 = cv2.inRange(hsv, red_lower2, red_upper2)
    red = red1 + red2
    green = cv2.inRange(hsv, green_lower, green_upper)
    yellow = cv2.inRange(hsv, yellow_lower, yellow_upper)

    return red, green, yellow


def create_contour(mask):
    _, mask_contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if len(mask_contours) != 0:
        largest_contour = max(mask_contours, key=cv2.contourArea)
        if cv2.contourArea(largest_contour) > color_min:
            return True
    return False

def clockCheck(clock):
    if time.time() - clock > 1:
        return True
    return False


def color_detection(side, clock):
    # Check if any color is detected in the combined mask
    if create_contour(yellow_mask) and clockCheck(clock):
        if side == 'R':
            ser.write(b"rYS\n")
        else:
            ser.write(b"lYS\n")
        clock = time.time()
    elif create_contour(red_mask) and clockCheck(clock):
        if side == 'R':
            ser.write(b"rRH\n")
        else:
            ser.write(b"lRH\n")
        clock = time.time()
    return clock


# Open a video capture object
lcamera = cv2.VideoCapture(2)
rcamera = cv2.VideoCapture(0)
clock = time.time()

while True:
    # Read a frame from the left camera
    _, frame = lcamera.read()
    frame = frame[0:310, 0:1080]
    # Create masks
    red_mask, green_mask, yellow_mask = masking(lred_lower1, lred_upper1, lred_lower2, lred_upper2, lgreen_lower, lgreen_upper, lyellow_lower, lyellow_upper)
    # Call the color detection function on the frame
    clock = color_detection('L', clock)
    # Read a frame from the right camera
    _, frame = rcamera.read()
    frame = frame[0:310, 0:1080]
    # Create masks
    red_mask, green_mask, yellow_mask = masking(rred_lower1, rred_upper1, rred_lower2, rred_upper2, rgreen_lower, rgreen_upper, ryellow_lower, ryellow_upper)  
    # Call the color detection function on the frame
    clock = color_detection('R', clock)
    # Shutdown Raspberry Pi when button is pressed
    if GPIO.input(Button) != 1:
        lcamera.release()
        rcamera.release()
        os.system("sudo shutdown -h now")

