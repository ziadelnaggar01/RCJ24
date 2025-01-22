import cv2


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
Path = "/home/pi/Desktop/Data base/Color Samples"

# Initialize the cameras
lcamera = cv2.VideoCapture(2)
rcamera = cv2.VideoCapture(0)

# Initialize image name
Count = [1]*6

print("Press 1 for Left red")
print("Press 2 for Left green")
print("Press 3 for Left yellow")
print("Press 4 for Right red")
print("Press 5 for Right green")
print("Press 6 for Right yellow")

# Main Code
while True:
    lFrame, rFrame = cap()

    key = cv2.waitKey(1)

    if key == ord('q'):
        break
    elif key == ord('1'):
                path = f'{Path}/Left/Red/{Count[0]}.jpg'
                cv2.imwrite(path, lFrame)
                Count[0] += 1
    elif key == ord('2'):
                path = f'{Path}/Left/Green/{Count[1]}.jpg'
                cv2.imwrite(path, lFrame)
                Count[1] += 1
    elif key == ord('3'):
                path = f'{Path}/Left/Yellow/{Count[2]}.jpg'
                cv2.imwrite(path, lFrame)
                Count[2] += 1
    elif key == ord('4'):
                path = f'{Path}/Right/Red/{Count[3]}.jpg'
                cv2.imwrite(path, rFrame)
                Count[3] += 1
    elif key == ord('5'):
                path = f'{Path}/Right/Green/{Count[4]}.jpg'
                cv2.imwrite(path, rFrame)
                Count[4] += 1
    elif key == ord('6'):
                path = f'{Path}/Right/Yellow/{Count[5]}.jpg'
                cv2.imwrite(path, rFrame)
                Count[5] += 1


# Release the camera
lcamera.release()
rcamera.release()
cv2.destroyAllWindows()
