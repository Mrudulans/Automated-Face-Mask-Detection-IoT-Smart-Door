import cv2
import numpy as np
from tensorflow.keras.models import load_model
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
import serial
import time

# Initialize serial communication with Arduino (update COM port as needed)
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)  # Replace 'COM3' with your Arduino port
time.sleep(2)  # Wait for Arduino to initialize

# Load the mask detection model
model = load_model('C:/Users/Admin/Desktop/mask_detector.h5')

# Initialize the webcam
video_stream = cv2.VideoCapture(0)

while True:
    ret, frame = video_stream.read()
    if not ret:
        break

    # Preprocess the frame for mask detection
    frame_resized = cv2.resize(frame, (224, 224))
    frame_array = np.array(frame_resized, dtype="float32")
    frame_preprocessed = preprocess_input(frame_array)
    frame_preprocessed = np.expand_dims(frame_preprocessed, axis=0)

    # Predict mask status
    (mask, without_mask) = model.predict(frame_preprocessed)[0]
    label = "Mask" if mask > without_mask else "No Mask"
    confidence = max(mask, without_mask) * 100

    # Send data to Arduino
    if label == "Mask":
        arduino.write(b'1')  # Send '1' to Arduino for mask detected
        print("Sent to Arduino: 1 (Mask Detected)")
    else:
        arduino.write(b'0')  # Send '0' to Arduino for no mask detected
        print("Sent to Arduino: 0 (No Mask Detected)")

    # Display the label and confidence on the frame
    cv2.putText(frame, f"{label}: {confidence:.2f}%", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, 
                (0, 255, 0) if label == "Mask" else (0, 0, 255), 2)
    cv2.imshow("Mask Detector", frame)

    # Press 'q' to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_stream.release()
cv2.destroyAllWindows()
arduino.close()