#include <Wire.h>                // For I2C communication
#include <Adafruit_MLX90614.h>  // MLX90614 library
#include <Servo.h>              // Servo motor library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();  // Create an MLX90614 object
Servo myServo;                                // Create a Servo object

// Pin definitions
const int servoPin = 9;      // Signal pin for the servo motor
const int redLedPin = 10;    // Red LED pin
const int greenLedPin = 11;  // Green LED pin
const int buzzerPin = 12;    // Buzzer pin

// Threshold for temperature (in Celsius)
float tempThreshold = 20.0;  // Adjust based on your requirements

unsigned long previousServoMillis = 0;
const unsigned long servoInterval = 500; // Interval for servo movement in milliseconds
int currentAngle = 0;
bool increasing = true;

void setup() {
    Serial.begin(9600);         // Initialize Serial Monitor
    mlx.begin();                // Initialize MLX90614 sensor
    myServo.attach(servoPin);   // Attach the servo motor to pin 9
    myServo.write(0);           // Set initial position of the servo (0 degrees)

    pinMode(redLedPin, OUTPUT);    // Set red LED pin as output
    pinMode(greenLedPin, OUTPUT);  // Set green LED pin as output
    pinMode(buzzerPin, OUTPUT);    // Set buzzer pin as output

    Serial.println("System Initialized");
}

void loop() {
    // Temperature sensor runs continuously
    float ambientTemp = mlx.readAmbientTempC();  // Read ambient temperature
    float objectTemp = mlx.readObjectTempC();    // Read object temperature

    // Print the temperature readings to the Serial Monitor
    Serial.print("Ambient Temp: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");

    Serial.print("Object Temp: ");
    Serial.print(objectTemp);
    Serial.println(" °C");

    // Handle temperature-based LED control
    if (objectTemp < tempThreshold) {
        Serial.println("Temperature Normal. Granting Access...");
        digitalWrite(greenLedPin, HIGH); // Turn on green LED
        digitalWrite(redLedPin, LOW);   // Turn off red LED
    } else {
        Serial.println("High Temperature! Denying Access...");
        digitalWrite(greenLedPin, LOW);  // Turn off green LED
        digitalWrite(redLedPin, HIGH);  // Turn on red LED
    }

    // Handle mask detection (via serial input)
    if (Serial.available() > 0) {
        char maskStatus = Serial.read();
        if (maskStatus == '1') { // "Low" =  mask worn
            Serial.println(" Mask Detected! Deactivating Buzzer.");
            digitalWrite(buzzerPin, LOW);
        } else if (maskStatus == '0') { // "High" = no mask 
            Serial.println(" No Mask Detected! Activating Buzzer.");
            digitalWrite(buzzerPin,HIGH);
        }
    }

    //Servo motor runs independently
    unsigned long currentMillis = millis();
    if (currentMillis - previousServoMillis >= servoInterval) {
        previousServoMillis = currentMillis;

        if (increasing) {
            currentAngle += 5;
            if (currentAngle >= 180) {
                currentAngle = 180;
                increasing = false;
            }
        } else {
            currentAngle -= 5;
            if (currentAngle <= 0) {
                currentAngle = 0;
                increasing = true;
            }
        }
        myServo.write(currentAngle);
        Serial.print("Servo Angle: ");
        Serial.println(currentAngle);
    }

    delay(100);  // Short delay to reduce serial monitor flooding
}
