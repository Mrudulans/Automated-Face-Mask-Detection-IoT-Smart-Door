
# AUTOMATED FACE MASK DETECTION AND MONITORING OF BODY TEMPERATURE USING IOT ENABLED SMART DOOR

## 🔍 Overview
This project is an IoT-enabled smart door system that uses computer vision and sensors to ensure safe and contactless entry. It detects whether a person is wearing a face mask and monitors their body temperature using Arduino and a temperature sensor.

## ⚙️ Technologies Used
- Python (OpenCV, TensorFlow, Keras)
- Arduino (C/C++)
- Serial Communication (Python ↔ Arduino)
- IoT Components (Temperature Sensor, Servo Motor)
- Deep Learning (MobileNetV2 model for mask detection)

## 🧠 Working
1. The camera captures a live video feed.
2. The trained CNN model (`mask_detector.h5`) detects whether a mask is worn.
3. Temperature is measured through the Arduino setup.
4. If the person wears a mask and has a normal temperature, the door opens automatically.

## 🧩 Files Included
- `import cv2.py` → Python script for face mask detection and Arduino communication
- `mask_detector.h5` → Trained CNN model
- `project.ino` → Arduino code for temperature monitoring and door control

## 🚀 How to Run
1. Open `import cv2.py` in Python and update your Arduino COM port.
2. Upload `project.ino` to Arduino.
3. Run the Python script and allow camera access.
4. The system will display detection results and control the smart door.

## 👩‍💻 Author
**Mrudula N S**
 
