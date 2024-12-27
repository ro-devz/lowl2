# Final Project - Stellar Simulation

This project simulates stellar objects using SFML graphics. Follow the instructions below to set up the necessary development environment and execute the project on your system.

## Prerequisites

- **MinGW** (Minimalist GNU for Windows) for GCC
- **SFML** (Simple and Fast Multimedia Library)

### 1. Install MinGW (GCC)

MinGW is a minimalist development environment for native Microsoft Windows applications. It provides the GCC (GNU Compiler Collection) necessary to compile C++ code.

#### Steps to Install MinGW for VS code:

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


### 2. Install SFML

SFML is the library used for graphics, window management, and system interaction. Here’s how to install the right version.

#### Steps to Install SFML:

1. **Download SFML**:
   - Visit the [SFML Downloads page](https://www.sfml-dev.org/download.php) and download the version **2.6.2** x64 for **MinGW**.
   
2. **Extract SFML**:
   - Extract the contents of the downloaded SFML zip file to a folder inside of your project directory

3. **Set up SFML for Compilation**:
   - In your project directory, create the following folder structure (if it doesn't exist):
     - `bin/` - Will contain the SFML dynamic link libraries (`*.dll`).

4. **Copy SFML DLLs**:
   - From the `\SFML-2.6.2\bin` folder, **copy the `.dll` files** and paste them into the root directory of your project (same location as your compiled executable).

### 3. Compile the Project

Once you’ve installed MinGW and set up SFML, you can compile the project using the  `make` or the `g++` command in the **Terminal** of VS code.

#### Commands to Compile:



Navigate to the folder containing your source files and run the following command:

```bash
make
```
If you can't use the make command, compile the project manually

```bash
g++ -IC:\SFML-2.6.2\include -I.\include -LC:\SFML-2.6.2\lib -o bin\FinalProject.exe .\src\Final-project.cpp .\src\StellarObject.cpp .\src\ArtificalObject.cpp .\src\SpaceObject.cpp .\src\legend.cpp .\src\simulation.cpp -lsfml-graphics -lsfml-window -lsfml-system
```


### 4. Run the code:

```.\bin\FinalProject.exe```


