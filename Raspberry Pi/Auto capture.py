import cv2
import os
import time


# Captures a frame and displays it
def cap():
    # Capture the frame for both cameras
    _, lFrame = lcamera.read()
    _, rFrame = rcamera.read()

    # Rotate the frames by 180 degrees
    lFrame = cv2.rotate(lFrame, cv2.ROTATE_180)
    rFrame = cv2.rotate(rFrame, cv2.ROTATE_180)

    # Display the frames
    cv2.imshow('Left Camera', lFrame)
    cv2.imshow('Right Camera', rFrame)

    # return the frames
    return lFrame, rFrame


# Path for Data base folder
Path = "/home/pi/Desktop/Data base/Letter Samples"

# Initialize the camera
lcamera = cv2.VideoCapture(2)
rcamera = cv2.VideoCapture(0)

# Ask user to choose which letter is he capturing
lLetter = input("Please enter the letter you are capturing with left camera ").upper()
rLetter = input("Please enter the letter you are capturing with right camera ").upper()

# Determine next image number at location
lCount = 1
rCount = 1
Temp = f'{Path}/Left/{lLetter}/{lCount}.jpg'
while os.path.isfile(Temp):
    lCount += 1
    Temp = f'{Path}/Left/{lLetter}/{lCount}.jpg'
Temp = f'{Path}/Right/{rLetter}/{rCount}.jpg'
while os.path.isfile(Temp):
    rCount += 1
    Temp = f'{Path}/Right/{rLetter}/{rCount}.jpg'

print("Press S when you are ready!")
while cv2.waitKey(1) != ord('s'):
    cap()
    # Break the loop when 'q' is pressed
    if cv2.waitKey(1) == ord('q'):
        break

# Main Code
while True:
    lFrame, rFrame = cap()

    # Locate the path where images are saved
    lPath = f'{Path}/Left/{lLetter}/{lCount}.jpg'
    rPath = f'{Path}/Right/{rLetter}/{rCount}.jpg'

    # Save the image
    cv2.imwrite(lPath, lFrame)
    cv2.imwrite(rPath, rFrame)

    # Increment counter for new image name
    lCount += 1
    rCount += 1

    time.sleep(0.025)
    # Break the loop when 'q' is pressed
    if cv2.waitKey(1) == ord('q'):
        break

# Release the camera
lcamera.release()
rcamera.release()
cv2.destroyAllWindows()
