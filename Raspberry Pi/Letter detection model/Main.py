import cv2
import tensorflow as tf
import numpy as np

# Load the TensorFlow Saved Model
model = tf.saved_model.load("E:\Robocup 2024 International\Raspberry Pi\Letter detection model\Yehia")


# Function to load class labels from a text file
def load_class_labels(file_path):
    with open(file_path, 'r') as f:
        class_labels = f.read().splitlines()
    return class_labels


# Function to preprocess the frame
def preprocess_frame(frame):
    # Resize frame to match input shape of the model
    resized_frame = cv2.resize(frame, (224, 224))
    # Preprocess the frame (e.g., normalize pixel values)
    preprocessed_frame = resized_frame.astype(np.float32) / 255.0  # Ensure float32 type and normalize pixel values
    return preprocessed_frame


# Access Webcam Feed
cap = cv2.VideoCapture(1)  # Use 0 for default webcam

# Load class labels from label.txt file
class_labels = load_class_labels("E:\Robocup 2024 International\Raspberry Pi\Letter detection model\labels.txt")  # Provide the path to your label.txt file

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    if not ret:
        break

    # Preprocess the frame
    preprocessed_frame = preprocess_frame(frame)

    # Perform Inference
    input_data = np.expand_dims(preprocessed_frame, axis=0)  # Add batch dimension
    output_data = model(input_data)  # Call model directly on input data

    # Process output_data
    class_probabilities = output_data[0]
    predicted_class_index = np.argmax(class_probabilities)
    predicted_class_label = class_labels[predicted_class_index]

    # Visualize Results
    cv2.putText(frame, predicted_class_label, (20, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.imshow('Frame', frame)

    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture
cap.release()
cv2.destroyAllWindows()
