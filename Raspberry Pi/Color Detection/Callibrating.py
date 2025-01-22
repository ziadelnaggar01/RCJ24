import cv2
import numpy as np
import os


def hsv_range(image_path):
    # Load the image
    image = cv2.imread(image_path)

    # Convert the image to HSV color space
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Calculate and store the HSV range
    if color == "R":
        middle = 80

        # Create a mask for pixels
        lower_mask = cv2.inRange(hsv_image, (0, 0, 0), (middle, 255, 255))
        upper_mask = cv2.inRange(hsv_image, (middle, 0, 0), (255, 255, 255))

        # Apply the mask to the HSV image
        hsv_image_upper = cv2.bitwise_and(hsv_image, hsv_image, mask=upper_mask)
        hsv_image = cv2.bitwise_and(hsv_image, hsv_image, mask=lower_mask)


# Calculate and store the HSV range
        HSV_min2[Count - 1][0], HSV_max2[Count - 1][0] = np.min(hsv_image_upper[:, :, 0]), np.max(hsv_image_upper[:, :, 0])
        HSV_min2[Count - 1][1], HSV_max2[Count - 1][1] = np.min(hsv_image_upper[:, :, 1]), np.max(hsv_image_upper[:, :, 1])
        HSV_min2[Count - 1][2], HSV_max2[Count - 1][2] = np.min(hsv_image_upper[:, :, 2]), np.max(hsv_image_upper[:, :, 2])

    HSV_min[Count - 1][0], HSV_max[Count - 1][0] = np.min(hsv_image[:, :, 0]), np.max(hsv_image[:, :, 0])
    HSV_min[Count - 1][1], HSV_max[Count - 1][1] = np.min(hsv_image[:, :, 1]), np.max(hsv_image[:, :, 1])
    HSV_min[Count - 1][2], HSV_max[Count - 1][2] = np.min(hsv_image[:, :, 2]), np.max(hsv_image[:, :, 2])


# Type in images paths to pull hsv range
Path = "/home/pi/Desktop/Color Samples" 

# Initialization
Count = 1
HSV_min = [[0 for i in range(3)] for j in range(10)]
HSV_max = [[0 for k in range(3)] for n in range(10)]
HSV_min2 = [[0 for m in range(3)] for o in range(10)]
HSV_max2 = [[0 for p in range(3)] for q in range(10)]

# Choose the color you want range for
print("Which side do you need the range for ?")
Side = input("Press L for left side and R for right side ").upper()
print("Which color do you need the range for ?")
color = input("Press R for Red color and G for Green color and Y for Yellow color ").upper()
Path = f'{Path}/{"Left" if Side == "L" else "Right"}/{"Red" if color == "R" else "Green" if color == "G" else "Yellow"}'
path = Path + f"/{Count}.jpg"


# Pull HSV range
while os.path.isfile(path):
    hsv_range(path)
    Count += 1
    path = Path + f'/{Count}.jpg'

# Prints hsv range detected
for i in range(Count - 1):
    if color != "R":
        print(f'image {i + 1}', HSV_min[i], " ", HSV_max[i])
    else:
        print(HSV_min[i], " ", HSV_max[i], "            ", HSV_min2[i], " ", HSV_max2[i])
