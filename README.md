# Arduino Escape Room – *L'Ufficio dello Scienziato*

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
├── 📁 Bolobox/                            # Puzzle 1 - Scatole Enigmatiche
│   ├── 🧩 Bolobox.ino
├── 📁 IR_Clock/                           # Puzzle 3 - Il Cifratempo
│   ├── 🧩 orologio_IR.ino
├── 📁 LeverOpening/                       # Puzzle 2 - Gli Occhi della Verità (lever mechanism)
│   ├── 🧩 apertura_leva.ino
├── 📁 ObstacleDetection/                  # Puzzle 2 - Obstacle detection logic
│   ├── 🧩 rileva_ostacoli.ino
├── 📁 TypingMachine/                      # Puzzle 4 - Il Disegno del Destino (robot drawing)
│   ├── 🧩 macchina_da_scrivere.ino
├── 📁 PCBs/                               # Custom PCB schematics (EasyEDA files - not included)
├── 📁 Images/                             # (Reserved for future images if available)
├── 📘 Escape.pdf                           # Project overall description (Italian)
├── 📄 README.md                            # You are here!
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
  - Clear obstacles detected by boxes.
  - Solve a 4-variable system displayed on LCDs to extract a numeric code.

🔧 Related Code:  
[`Bolobox/Bolobox.ino`](./Bolobox/Bolobox.ino)

---

### 🧩 Puzzle 2: **Gli Occhi della Verità** (The Eyes of Truth)

- **Hardware**:
  - Servo motors
  - Push buttons
  - RGB LEDs
  - LCD Displays
  - Arduino MEGA
- **Objective**:
  - Enter the code from Puzzle 1 to unlock a mechanical box.
  - Press wall-mounted buttons in coordination to reveal hidden messages.

🔧 Related Code:  
[`LeverOpening/apertura_leva.ino`](./LeverOpening/apertura_leva.ino)  
[`ObstacleDetection/rileva_ostacoli.ino`](./ObstacleDetection/rileva_ostacoli.ino)

---

### 🧩 Puzzle 3: **Il Cifratempo** (The Cipher Time)

- **Hardware**:
  - Stepper motor
  - IR Receiver (Sony Remote Control)
  - Arduino Nano
- **Objective**:
  - Operate a frozen clock via IR control.
  - Decrypt a Caesar cipher code hidden in clock movement sequences.

🔧 Related Code:  
[`IR_Clock/orologio_IR.ino`](./IR_Clock/orologio_IR.ino)

---

### 🧩 Puzzle 4: **Il Disegno del Destino** (The Destiny Drawing)

- **Hardware**:
  - DIY Drawing Robot
  - Magnetic whiteboard
  - Color markers
  - Arduino Controller
- **Objective**:
  - A robot autonomously draws a key symbol on the whiteboard after proper initialization.

🔧 Related Code:  
[`TypingMachine/macchina_da_scrivere.ino`](./TypingMachine/macchina_da_scrivere.ino)

---

## 🛠 Hardware & Tools Used

- **Arduino UNO / MEGA / Nano Boards**
- **HC-SR04 Ultrasonic Sensors**
- **LCD Displays 16x2**
- **RGB LEDs and Standard LEDs**
- **Stepper Motors and Servo Motors**
- **Sony Remote Control (IR Communication)**
- **Custom PCBs designed via EasyEDA**

---

## 🧪 Key Learning Outcomes

- Embedded system integration for real-world interactive games.
- PCB design for robust, reliable hardware using EasyEDA.
- Implementation of real-time sensing, decoding, and mechanical control.
- Multistage puzzle design based on electrical engineering and software logic.

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

- 📘 [Escape.pdf](./Escape.pdf) – Project and room overview (Italian)
- 🎯 Arduino Puzzle Codes (`*.ino`)
- 🧩 PCB Designs (EasyEDA projects – not included)

---

## 📜 License

All rights reserved. Educational and demonstrative use only.

---
