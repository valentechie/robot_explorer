# 🤖 Simulation of a Robot Explorer on a Board with Obstacles

[![GPL-3.0 License](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
![Language](https://img.shields.io/badge/C%2B%2B-purple)
![Status](https://img.shields.io/badge/status-active-brightgreen)

---

## 📚 Table of Contents
- [Introduction](#-introduction)
- [Quick Start](#-quick-start)
- [Demo](#-demo)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [File Overview](#-file-overview)
- [Example Input/Output](#-example-inputoutput)
- [Project Context](#-project-context)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🚀 Introduction

C++ program that simulates a robot moving around a map. The dimensions of the board, the initial position of the robot and the obstacles can be found in the **`input.txt`** file. The user **can modify the data** in the input.txt file to make the game more dynamic.

The program will terminate when all the cells of the board have been visited or when the robot cannot move to any free cell. The number of free and occupied cells of the board should be displayed on the screen.

In addition, the final result of the program must be printed in a file called **`output.txt`**.

---

## ⚡ Quick Start

```bash
git clone https://github.com/valentechie/robot_explorer.git
cd robot_explorer
g++ robot_simulation.cpp -o robot_simulation
./robot_simulation
```
Edit **`input.txt`** as needed before running.  
See **`output.txt`** for the results.

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
- Run the program.  
- Results are displayed on the terminal and saved in **`output.txt`**.

---

## 📁 File Overview

- **`robot_simulation.cpp`**: Main source code for simulation logic.
- **`input.txt`**: Configuration for the board and robot.
- **`output.txt`**: Final results after running the program.

---

## 📝 Example Input/Output

**Example `input.txt`:**
```
5 5          # Board size (rows cols)
2 2          # Robot starting position (row col)
1 0 0        # Obstacle at (row col)
1 3 1        # Obstacle at (row col)
```

**Example `output.txt`:**
```
Total free cells visited: 23
Total obstacles encountered: 2
Final board state:
. . X . .
. . . . .
. . R . .
. . . . .
. X . . .
```
Legend:  
- `R` = Robot  
- `X` = Obstacle  
- `.` = Free cell

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

This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.  
See the [LICENSE](LICENSE) file for details.

---
