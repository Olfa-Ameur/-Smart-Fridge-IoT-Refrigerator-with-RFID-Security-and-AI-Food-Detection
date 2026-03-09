## 📡 Project Overview

The Smart Fridge project is an embedded IoT system designed to transform a traditional refrigerator into an intelligent device capable of monitoring its environment, securing access, and identifying stored food items using artificial intelligence.

The system integrates multiple technologies including STM32 microcontrollers, ESP32-CAM vision modules, RFID authentication, environmental sensors, MQTT communication, and a graphical user interface.

The refrigerator continuously monitors temperature and humidity, detects food items using a trained AI model, and transmits real-time data to a graphical dashboard accessible by the user.

## ⚙️ Key Features

• RFID-based secure access control  
• Automatic door unlocking using servo motor  
• Temperature monitoring using DHT11 sensor  
• Humidity monitoring inside the refrigerator  
• Real-time display on LCD screen  
• AI-based food recognition using ESP32-CAM  
• Detection of vegetables such as tomatoes and peppers  
• MQTT communication for real-time data transmission  
• Graphical interface for remote monitoring

## 🧩 Hardware Components

• STM32 Nucleo board (main controller)  
• ESP32-CAM module (image capture and AI inference)  
• RFID RC522 module (secure access authentication)  
• Servo motor (door locking system)  
• DHT11 sensor (temperature and humidity monitoring)  
• LCD display with I2C interface  


## 🧠 AI Food Detection

The ESP32-CAM module is used to capture images inside the refrigerator.

A computer vision model trained using **Edge Impulse** was deployed on the ESP32-CAM to identify food items stored inside the fridge.

The training dataset was created by capturing multiple images of vegetables including:

• Tomatoes  
• Peppers

The trained model runs directly on the ESP32-CAM using embedded inference and detects objects in real time.

## 📡 MQTT Communication

The system uses MQTT protocol for real-time data transmission between the embedded devices and the graphical user interface.

The following data are transmitted:

• Temperature values  
• Humidity levels  
• Detected food objects  


## 🖥 User Interface

A graphical interface was developed to allow users to monitor the refrigerator remotely.

The interface displays:

• Current temperature  
• Humidity level  
• Detected food items  
• System status

All information is updated in real time using MQTT communication.

## 💻 Software Architecture

The system is composed of three main software components:

 STM32 Firmware
 
• RFID authentication
• Sensor acquisition
• LCD display control
• Servo motor control

 ESP32-CAM Firmware
 
• Image capture
• Edge Impulse inference
• MQTT data transmission

User Interface

• Data visualization
• Real-time monitoring
• MQTT communication

## 🛠 Tools & Technologies

• STM32CubeIDE  
• Arduino IDE (ESP32-CAM)  
• Edge Impulse  
• MQTT Protocol  
• Embedded C   
• ESP32-CAM

## 🚀 Future Improvements

• Food expiration tracking  
• Recipe recommendation based on fridge content  
• Mobile application integration  
• Cloud data storage  
• More advanced food recognition model

## 👨‍💻 Author

Embedded Systems & IoT Developer

Interests:

• Embedded systems  
• Artificial intelligence on edge devices  
• IoT architectures  
• Computer vision
