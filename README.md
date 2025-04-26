# 🧩 Arduino Escape Room – *L'Ufficio dello Scienziato*

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue?logo=arduino)](https://www.arduino.cc/) [![PCB](https://img.shields.io/badge/PCB-Designed%20with-EasyEDA-green)](https://easyeda.com/)  
An interactive Arduino-based escape room featuring real-time puzzles, sensors, actuators, and custom-designed PCBs to create an immersive technological challenge.

---

## 🧠 About the Project

**L'Ufficio dello Scienziato** ("The Scientist’s Office") is a complete real-world escape room designed around Arduino electronics and fully custom puzzles.  
Participants must solve complex electronic-based challenges by interacting with **real sensors**, **actuators**, and **programmed puzzles**, all embedded inside a futuristic laboratory environment.

Each puzzle integrates custom-built electronic circuits and PCBs designed using **EasyEDA**, ensuring reliable, modular, and professional-grade performance.  
Creating custom PCBs allowed for **efficient wiring**, **increased robustness**, and **scalable designs**, which are fundamental in embedded interactive systems.

---

## 🗂 Project Structure

```
📦 Arduino-Escape-Room/
├── 📁 Bolobox/
│   ├── 🧩 Bolobox.ino
│   ├── 🖼️ Bolobox_PCB.png
│   ├── 🖼️ Bolobox_Schematic.png
├── 📁 IR_Clock/
│   ├── 🧩 IR_Clock.ino
│   ├── 🖼️ Clock_PCB.png
│   ├── 🖼️ Clock_Schematic.png
├── 📁 Keyboard/
│   ├── 🧩 Keyboard.ino
│   ├── 🖼️ Keyboard_PCB.png
│   ├── 🖼️ Keyboard_Schematic.png
├── 📁 ObstacleDetection/
│   ├── 🧩 ObstacleDetection.ino
│   ├── 🖼️ ObstacleDetection_PCB.png
│   ├── 🖼️ ObstacleDetection_Schematic.png
├── 📘 Escape.pdf
├── 📄 README.md
```

---

## 🎮 Room Scenario

> *"Four daring investigators are trapped inside the laboratory of a visionary — but dangerously eccentric — scientist. Surrounded by futuristic machines, hidden clues, and high-tech devices, they must solve intricate puzzles to uncover the truth... and escape before time runs out."*

Each solved puzzle brings players closer to unveiling the secrets buried deep within the scientist’s mind.

---

## 🔥 Puzzle Descriptions

---

### 🧩 Puzzle 1: **Scatole Enigmatiche del Genio** (The Genius' Mysterious Boxes)

- **Hardware**:
  - Ultrasonic sensors (HC-SR04)
  - RGB LEDs
  - LCD Displays
  - Arduino UNO
- **Objective**:
  - Players must clear obstacles detected by four smart boxes.
  - Solve a 4-variable system displayed on LCDs to unlock the next stage.

🔧 Related Files:  
[`Bolobox/Bolobox.ino`](./Bolobox/Bolobox.ino)

📸 PCB and Schematic:
<p align="center">
  <img src="./Bolobox/Bolobox_PCB.png" height="230"/>
  <img src="./Bolobox/Bolobox_Schematic.png" height="230"/>
</p>

---

### 🧩 Puzzle 2: **Gli Occhi della Verità** (The Eyes of Truth) – **Obstacle Detection Module**

- **Hardware**:
  - Servo motors
  - Push buttons
  - RGB LEDs
  - LCD Displays
  - Arduino MEGA
- **Objective**:
  - After entering the first code, players trigger wall buttons simultaneously.
  - Sensors validate coordination to reveal hidden messages.

🔧 Related Files:  
[`ObstacleDetection/ObstacleDetection.ino`](./ObstacleDetection/ObstacleDetection.ino)

📸 PCB and Schematic:
<p align="center">
  <img src="./ObstacleDetection/ObstacleDetection_PCB.png" height="230"/>
  <img src="./ObstacleDetection/ObstacleDetection_Schematic.png" height="230"/>
</p>

---

### 🧩 Puzzle 3: **Il Cifratempo** (The Cipher Time)

- **Hardware**:
  - Stepper motor
  - IR Receiver (Sony Remote Control)
  - Arduino Nano
- **Objective**:
  - Control a frozen clock via infrared.
  - Decrypt the movement pattern into a hidden password.

🔧 Related Files:  
[`IR_Clock/IR_Clock.ino`](./IR_Clock/IR_Clock.ino)

📸 PCB and Schematic:
<p align="center">
  <img src="./IR_Clock/Clock_PCB.png" height="230"/>
  <img src="./IR_Clock/Clock_Schematic.png" height="230"/>
</p>

---

### 🧩 Puzzle 4: **Il Disegno del Destino** (The Destiny Drawing)

- **Hardware**:
  - DIY Drawing Robot
  - Magnetic whiteboard
  - Arduino Controller
- **Objective**:
  - Deploy a robot that autonomously draws a clue leading to the final exit.

🔧 Related Files:  
[`Keyboard/Keyboard.ino`](./Keyboard/Keyboard.ino)

📸 PCB and Schematic:
<p align="center">
  <img src="./Keyboard/Keyboard_PCB.png" height="230"/>
  <img src="./Keyboard/Keyboard_Schematic.png" height="230"/>
</p>

---

## 🛠 Hardware & Tools Used

- **Arduino UNO / MEGA / Nano Boards**
- **HC-SR04 Ultrasonic Sensors**
- **LCD Displays 16x2**
- **RGB LEDs and Standard LEDs**
- **Stepper Motors and Servo Motors**
- **IR Receiver Modules (Sony Remote)**
- **Custom PCB Design with EasyEDA**

---

## 🧪 Key Learning Outcomes

- Full-stack embedded system development for an interactive experience.
- PCB design to improve reliability and minimize wiring errors.
- Real-time control systems, IR communication, ultrasonic obstacle detection, and stepper motor management.
- Engineering storytelling and puzzle integration.

---

## 📅 Year

2023

---

## 👨‍🎓 Authors

- Andrea Perna  
- Mattia Zappalà

📧 and.perna99@gmail.com  
📧 matty.zapp.99.mz@gmail.com

---

## 📎 Resources

- 📘 [Escape.pdf](./Escape.pdf) – Overall room description
- 🧩 Puzzle-specific Arduino codes and schematics
- 🛠 Custom PCB projects (EasyEDA)

---

## 📜 License

All rights reserved. Educational and demonstrative use only.

---
