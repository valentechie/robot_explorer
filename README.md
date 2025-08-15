# 🤖 Simulation of a Robot Explorer on a Board with Obstacles

[![GPL-3.0 License](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
![Language](https://img.shields.io/badge/C%2B%2B-purple)
![Status](https://img.shields.io/badge/status-active-brightgreen)

---

## 📚 Table of Contents
- [Introduction](#-introduction)
- [Demo](#-demo)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [File Overview](#-file-overview)
- [Project Context](#-project-context)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🚀 Introduction

C++ program that simulates a robot moving around a map. The dimensions of the board, the initial position of the robot and the obstacles can be found in the **`input.txt`** file. The user **can modify the data** in the input.txt file to make the game more dynamic.

The program will terminate when all the cells of the board have been visited or when the robot cannot move to any free cell. The number of free and occupied cells of the board should be displayed on the screen.

In addition, the final result of the program must be printed in a file called **`output.txt`**.

---

## 🎬 Demo

<p align="center">
  <img src="https://github.com/user-attachments/assets/74d541f2-4796-483f-981c-050d73efb945" width="500"/>
</p>

---

## 🛠️ Requirements

- **Compiler:** Any modern C++ compiler 
- **Language Standard:** C++
- **Operating System:** Linux  
  > *May also work on macOS or Windows with minor adjustments*

---

## 📦 Installation

**1️⃣ Clone the repository:**
```bash
git clone https://github.com/valentechie/robot_explorer.git
```

**2️⃣ Navigate to the project folder:**
```bash
cd robot_explorer
```

**3️⃣ Compile the code:**
```bash
g++ robot_simulation.cpp -o robot_simulation
```

**4️⃣ Run the program:**
```bash
./robot_simulation
```

---

## 🕹️ Usage

- Edit **`input.txt`** to set the board size, robot's starting position, and obstacles.
  
  **Example `input.txt`:**
  ```
  5 5          # Board size, rows(5) cols(5)
  2 2          # Robot starting position, row (2) col(2)
  1 0          # Obstacle at row (1) col (0)
  1 3          # Obstacle at row (1) col (3)
  ```

- Run the program.  
- Results are displayed on the terminal and saved in **`output.txt`**.
  
  **Example `output.txt`:**
  ```
  Total free cells visited: 23
  Total Occupied cells: 2

  Final board state:
  R # . . .
  * . . . .
  * * * . .
  . # . . .
  . . . . .
  ```

  **Legend:**  
  - `R` = Robot  
  - `#` = Obstacle  
  - `.` = Free cell
  - `*` = Occupied cell
---

## 📁 File Overview

- **`robot_simulation.cpp`**: Main source code for simulation logic.
- **`input.txt`**: Configuration for the board and robot.
- **`output.txt`**: Final results after running the program.

---

## 🎓 Project Context

Developed as the final assignment for **Fundamentos de la Programación** at URJC.  
This project helped consolidate key programming concepts and practical C++ experience.

---

## 🤝 Contributing

Contributions are welcome!  
- Fork this repository  
- Open issues for bugs or ideas  
- Submit pull requests to improve the project

---

## 📄 License

This project is licensed under the [GPL-3.0](LICENSE)
