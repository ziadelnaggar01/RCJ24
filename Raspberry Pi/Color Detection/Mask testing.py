import cv2
import numpy as np

# Manually enter desired hsv range
black_lower = np.array([90, 0, 0])
black_upper = np.array([150, 255, 120])



red_lower1 = np .array([170, 150, 0])
red_upper1 = np.array([179, 255, 255])
red_lower2 = np.array([0, 150, 0])
red_upper2 = np.array([10, 255, 255])

green_lower = np.array([75, 85, 75])
green_upper = np.array([95, 230, 255])
yellow_lower = np.array([15, 120, 80])
yellow_upper = np.array([40, 255, 225])


def masking():
    # Convert the frame from BGR to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create masks for each color
    red1 = cv2.inRange(hsv, red_lower1, red_upper1)
    red2 = cv2.inRange(hsv, red_lower2, red_upper2)
    red = red1 + red2
    green = cv2.inRange(hsv, green_lower, green_upper)
    yellow = cv2.inRange(hsv, yellow_lower, yellow_upper)
    black = cv2.inRange(hsv, black_lower, black_upper)

    return red, green, yellow, black


# Open a video capture object
cap = cv2.VideoCapture(2)  # 0: Right, 2: Left

# Main Code
while True:
    # Read a frame from the camera
    _, frame = cap.read()

    frame = cv2.rotate(frame, cv2.ROTATE_180)

    red_mask, green_mask, yellow_mask, black_mask = masking()

    # Display the original frame and the masks
    cv2.imshow('Original Frame', frame)
    cv2.imshow('Red', red_mask)
    cv2.imshow('Yellow', yellow_mask)
    cv2.imshow('Green', green_mask)
    #cv2.imshow('black', black_mask)

    # Break the loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture object and close all windows
cap.release()
cv2.destroyAllWindows()
