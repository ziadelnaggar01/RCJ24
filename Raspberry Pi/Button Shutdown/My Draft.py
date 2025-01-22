import RPi.GPIO as GPIO
import os

# Set GPIO mode (BCM or BOARD)
GPIO.setmode(GPIO.BCM)

GPIO.setwarnings(False)

# Define GPIO pins
Button = 26

# Configure the button pin as an input with a pull-up resistor
GPIO.setup(Button, GPIO.IN, pull_up_down=GPIO.PUD_UP)
while True:
    if GPIO.input(Button)!=1:
        os.system("sudo shutdown -h now")
