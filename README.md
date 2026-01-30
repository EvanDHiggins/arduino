# Arduino CLI Monorepo

A lightweight, automated build system for managing multiple Arduino projects, shared local libraries, and hardware configurations without the Arduino IDE.

## Quick Start
How to create and run a new project:

1.  **Run the Generator:**
    ```bash
    ./new_project.sh
    ```
    (Follow the prompts to name your project and select your board/port)

2.  **Enter the Directory:**
    ```bash
    cd proj/MyNewProject
    ```

3.  **Build & Upload:**
    ```bash
    make upload
    ```

---

## Directory Structure

```text
RepoRoot/
├── Makefile               # The Master Build System (Logic lives here)
├── new_project.sh         # Interactive script to generate new projects
├── build/                 # Auto-generated build artifacts (.hex/.elf files)
├── lib/                   # Shared Local Libraries
│   └── MyCustomLib/       # Note: Libraries must be in subfolders!
│       ├── MyCustomLib.h
│       └── MyCustomLib.cpp
└── proj/                  # Source code for all projects
    ├── Project1/
    │   ├── Project1.ino
    │   ├── config.mk      # Board & Port configuration
    │   └── Makefile       # Proxy file (forwards commands to Root)
    └── Project2/
        ├── ...
        └── ...
```

## Configuration Reference

These variables are defined in `proj/<ProjectName>/config.mk`, but can be overridden from the command line (e.g., `make upload PORT=/dev/ttyUSB0`).

| Variable | Description | Example |
| :--- | :--- | :--- |
| `BOARD` | The Fully Qualified Board Name (FQBN). | `arduino:avr:nano:cpu=atmega328old` |
| `PORT` | The serial port for uploading and monitoring. | `/dev/cu.usbmodem1101` (Mac) or `COM3` (Win) |
| `BAUD` | The baud rate for the Serial Monitor. | `9600` (Default), `115200` |
| `LIB_DIR` | The path to shared local libraries. | `lib` (Default) |

### Custom Libraries
The system is configured to treat the root `lib/` folder as a standard library path.

1.  **Structure:** You **must** create a subfolder for each library. The CLI will not find loose files.
    * ✅ `lib/MyMotor/MyMotor.h`
    * ❌ `lib/MyMotor.h`
2.  **Usage:** Include them in your sketch using angle brackets, just like a system library.
    ```cpp
    #include <MyMotor.h>
    ```


### The Proxy Makefile
Each project folder contains a small `Makefile`. It contains no build logic itself. Its only job is to forward your commands up to the Root Makefile, passing the current directory name as the project target.

**How it works:**
When you run `make upload` inside `proj/SunriseAlarm/`, the proxy file executes:
```bash
make -C ../.. upload s=SunriseAlarm
