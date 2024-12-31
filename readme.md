# Final Project - Stellar Simulation

# Table of Contents
1. [Project Overview](#project-overview)
2. [Project Deliverables](#project-deliverables)
   - [Planets, Moons, and Satellites](#planets-moons-and-satellites)
   - [Core Simulation Features](#core-simulation-features)
   - [User Interactions Deliverables](#user-interactions-deliverables)
3. [Compile the Project](#compile-the-project)
   - [Commands to Compile](#commands-to-compile)
4. [Run the Code](#run-the-code)
5. [Installation and Configuration](#installation-and-configuration)
   - [Prerequisites](#prerequisites)
     - [MinGW (GCC)](#mingw-gcc)
     - [SFML (Simple and Fast Multimedia Library)](#sfml-simple-and-fast-multimedia-library)
   - [Steps to Install MinGW](#steps-to-install-mingw)
   - [Steps to Install SFML](#steps-to-install-sfml)

---

### 1. Project Overview
This project simulates stellar objects using SFML graphics. Follow the instructions below to set up the necessary development environment and execute the project on your system.

There are 2 ways to start the project:

- **No Client / Server** :  `.\bin\FinalProject.exe`
- **Client and Server** :  `.\bin\FinalProject.exe server` AND `.\bin\FinalProject.exe client localhost`

---

### 2. Project Deliverables

#### Planets, Moons, and Satellites 

| **Name**     | **Added to System** | **Type**   | **Associated Planet**  |
|--------------|---------------------|------------|------------------------|
| Sun          | ✔️                  | Star       | N/A                    |
| Mercury      | ✔️                  | Planet     | N/A                    |
| Venus        | ✔️                  | Planet     | N/A                    |
| Earth        | ✔️                  | Planet     | N/A                    |
| Mars         | ✔️                  | Planet     | N/A                    |
| Jupiter      | ✔️                  | Planet     | N/A                    |
| Saturn       | ✔️                  | Planet     | N/A                    |
| Uranus       | ✔️                  | Planet     | N/A                    |
| Neptune      | ✔️                  | Planet     | N/A                    |
| Moon         | ✔️                  | Moon       | Earth                  |
| Europa       | ✔️                  | Moon       | Jupiter                |
| Io           | ✔️                  | Moon       | Jupiter                |
| Ganymede     | ✔️                  | Moon       | Jupiter                |
| Callisto     | ✔️                  | Moon       | Jupiter                |
| Titan        | ✔️                  | Moon       | Saturn                 |
| Rhea         | ❌                  | Moon       | Saturn                 |
| Phobos       | ❌                  | Moon       | Mars                   |
| Deimos       | ❌                  | Moon       | Mars                   |
| Mimas        | ❌                  | Moon       | Saturn                 |
| Enceladus    | ❌                  | Moon       | Saturn                 |
| Tethys       | ❌                  | Moon       | Saturn                 |
| Iapetus      | ❌                  | Moon       | Saturn                 |
| Pan          | ❌                  | Satellite  | Saturn                 |
| Atlas        | ❌                  | Satellite  | Saturn                 |
| Prometheus   | ❌                  | Satellite  | Saturn                 |
| Pandora      | ❌                  | Satellite  | Saturn                 |
| Epimetheus   | ❌                  | Satellite  | Saturn                 |

---

#### Core Simulation Features

| **Feature**                                                                 | **Status**  | **Comments**                                                                 |
|-----------------------------------------------------------------------------|-------------|-----------------------------------------------------------------------------|
| **1. Object Creation (Stellar and Artificial Objects)**                      | ✔️ Completed |                                                                             |
| **2. Gravitational Forces Calculation (Between Objects)**                   | ✔️ Completed |                                                                             |
| **3. Update Object Positions Based on Gravitational Forces**                 | ✔️ Completed |                                                                             |
| **4. Handling Orbital Mechanics (Objects Follow orbits based on forces)**    | ✔️ Completed |                                                                             |
| **5. Object Collision Handling (Gravitational Pull Impact)**                | ✔️ Completed |                                                                             |
| **6. Time and Real-Time Step Calculation**                                   | ✔️ Completed |                                                                             |
| **7. Stellar Object Rendering (Drawing Objects to the Window)**                      | ✔️ Completed |                                                                             |
| **8. Artificial Object Rendering (Drawing Objects to the Window)**                      | ✔️ Completed |                                                                             |
| **9. Update Object Size and Position (based on mass, distance, etc.)**      | ✔️ Completed |                                                                             |
| **10. Simulation Scaling (Distance and Size Scale)**                          | ✔️ Completed |                                                                             |
| **11. Dynamic Object Interaction (Mass Changes, Movements, etc.)**           | ✔️ Completed |                                                                             |
| **12. Legend and Information Details (Display Object Info)**                           | ✔️ Completed |                                                                             |

---

#### User Interactions Deliverables

| **Interaction**                                                            | **Status**  | **Comments**                                                                   |
|----------------------------------------------------------------------------|-------------|-----------------------------------------------------------------------------   |
| **1. Navigation (Pan map using mouse)**                                     | ✔️ Completed |                                                                             |
| **2. Reset center of map (using `*` key)**                                  | ✔️ Completed |                                                                             |
| **3. Zoom in (mouse wheel upward)**                                         | ✔️ Completed |`viewScale` is increased by 10%                                              |
| **4. Zoom out (mouse wheel downward)**                                      | ✔️ Completed |`viewScale` is increased by 10%                                              |
| **5. Increase time factor (using `+` key when no object is selected)**       | ✔️ Completed | `realTimeStep` is increased by 3600 seconds (1 hour)                       |
| **6. Decrease time factor (using `-` key when no object is selected)**       | ✔️ Completed | `realTimeStep` is decreased by 3600 seconds (1 hour)                       |
| **7. Select object (clicking with left mouse button)**                      | ✔️ Completed |                                                                             |
| **8. Delete selected object (using `Delete` key)**                          | ✔️ Completed |                                                                             |
| **9. Move selected object (dragging with left mouse button)**               | ✔️ Completed | !! The object must be selected first !! <br> Then, you can click again on the object and drag it to move it |
| **10. Apply thrust to selected artificial object (arrow keys)**             | ❌ In Progress |                                                                           |
| **11. Increase mass of selected object (using `+` key)**                    | ✔️ Completed | Selected object mass is multiplied by 1.1 (10% increase)                    |
| **12. Decrease mass of selected object (using `-` key)**                    | ✔️ Completed | Selected object mass is multiplied by 0.9 (10% decrease)                    |
| **13. Deselect object (using Escape key)**	                                |✔️ Completed	| While Escape not pressed, the object will remain selected and you won't be able to change the selected object |

---

### 3. Compile the Project

Once you’ve installed MinGW and set up SFML, you can compile the project using the `make` or the `g++` command in the **Terminal** of VS Code.

#### Commands to Compile:
Navigate to the folder containing your source files and run the following command:

```bash
make
```
If you can't use the make command, compile the project manually:

```bash
g++ -IC:\SFML-2.6.2\include -I.\include -LC:\SFML-2.6.2\lib -o bin\FinalProject.exe .\src\Final-project.cpp .\src\StellarObject.cpp .\src\ArtificalObject.cpp .\src\SpaceObject.cpp .\src\legend.cpp .\src\simulation.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

or

```bash
g++ -IC:\SFML-2.6.2\include -I.\include -LC:\SFML-2.6.2\lib -o bin\FinalProject.exe .\src\Final-project
```

## 4. Run the Code

    No Client / Server : `.\bin\FinalProject.exe`
    Client and Server : `.\bin\FinalProject.exe` server AND `.\bin\FinalProject.exe` client localhost


## 5. Installation and Configuration
### Prerequisites

- **MinGW** (Minimalist GNU for Windows) for GCC
- **SFML** (Simple and Fast Multimedia Library)

#### 1. Install MinGW (GCC)

MinGW is a minimalist development environment for native Microsoft Windows applications. It provides the GCC (GNU Compiler Collection) necessary to compile C++ code.

##### Steps to Install MinGW for VS code:

2. **Install MinGW**:
     - Install **MinGW-w64** by downloading it from the official site: [MinGW-w64](https://sourceforge.net/projects/mingw-w64/).
     - Run the command ` pacman -S --needed base-devel mingw-w64-x86_64-toolchain `

3. **Add MinGW to your system’s PATH**:
   - Add`C:\msys64\mingw64\bin`.

4. **Verify Installation**:
   - Open a **Command Prompt** or **VS Code terminal** and run the following command to check if MinGW was installed correctly:
     ```bash
     g++ --version
     ```
     If the command returns the version information for GCC, MinGW has been installed successfully.


#### 2. Install SFML

SFML is the library used for graphics, window management, and system interaction. Here’s how to install the right version.

##### Steps to Install SFML:

1. **Download SFML**:
   - Visit the [SFML Downloads page](https://www.sfml-dev.org/download.php) and download the version **2.6.2** x64 for **MinGW**.
   
2. **Extract SFML**:
   - Extract the contents of the downloaded SFML zip file to a folder inside of your project directory

3. **Set up SFML for Compilation**:
   - In your project directory, create the following folder structure (if it doesn't exist):
     - `bin/` - Will contain the SFML dynamic link libraries (`*.dll`).

4. **Copy SFML DLLs**:
   - From the `\SFML-2.6.2\bin` folder, **copy the `.dll` files** and paste them into the root directory of your project (same location as your compiled executable).




