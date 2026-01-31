#!/bin/bash

# ==========================================
#   ARDUINO PROJECT GENERATOR (Interactive)
# ==========================================
# Usage: ./new_project.sh

# --- 0. Safety Check: Ensure execution from script root ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CURRENT_DIR="$(pwd)"

if [ "$SCRIPT_DIR" != "$CURRENT_DIR" ]; then
    echo "❌ Error: Safety Check Failed."
    echo "   Please 'cd' into the script directory before running it."
    exit 1
fi

PROJ_ROOT="proj"

# --- 1. Get Project Name ---
echo "----------------------------------------"
read -p "Enter new project name (e.g., SunriseAlarm): " PROJ_NAME

if [ -z "$PROJ_NAME" ]; then
    echo "❌ Error: Project name cannot be empty."
    exit 1
fi

TARGET_DIR="$PROJ_ROOT/$PROJ_NAME"

if [ -d "$TARGET_DIR" ]; then
    echo "❌ Error: Directory '$TARGET_DIR' already exists."
    exit 1
fi

# --- 2. Get Board FQBN ---
echo "----------------------------------------"
echo "Scanning for connected boards to help you..."
echo ""
arduino-cli board list
echo ""
echo "Examples:"
echo "  - Standard Uno:  arduino:avr:uno"
echo "  - Nano (Old):    arduino:avr:nano:cpu=atmega328old"
echo "  - ESP32:         esp32:esp32:esp32"
echo "----------------------------------------"
read -p "Enter Board FQBN (Default: arduino:avr:uno): " BOARD_FQBN

if [ -z "$BOARD_FQBN" ]; then
    BOARD_FQBN="arduino:avr:uno"
fi

# --- 3. Get Serial Port (Numeric Selection) ---
echo "----------------------------------------"
echo "Select Upload Port:"

# Get list of ports (looking for /dev/ devices)
# We handle Bash 3.2 (macOS default) compatibility by avoiding 'mapfile'
PORTS=()
while IFS= read -r line; do
    PORTS+=("$line")
done < <(arduino-cli board list | grep "/dev/" | awk '{print $1}')

# Check if we found any ports
if [ ${#PORTS[@]} -eq 0 ]; then
    echo "⚠️  No ports found automatically."
    echo "   (Make sure your device is plugged in)"
    echo ""
    read -p "Enter Port Manually (e.g. /dev/cu.usbmodem1101): " UPLOAD_PORT
else
    # Print the menu
    i=1
    for port in "${PORTS[@]}"; do
        echo "  $i) $port"
        ((i++))
    done
    echo "  M) Manual Entry"
    echo ""
    read -p "Enter number (Default: 1): " PORT_SELECTION

    # Default to 1 if empty
    if [ -z "$PORT_SELECTION" ]; then
        PORT_SELECTION=1
    fi

    if [[ "$PORT_SELECTION" =~ ^[0-9]+$ ]] && [ "$PORT_SELECTION" -le "${#PORTS[@]}" ] && [ "$PORT_SELECTION" -gt 0 ]; then
        # Array index is selection - 1
        INDEX=$((PORT_SELECTION-1))
        UPLOAD_PORT="${PORTS[$INDEX]}"
        
        # --- MAC SPECIFIC FIX ---
        # If the user selected a /dev/tty port, switch it to /dev/cu to avoid ser_open errors
        if [[ "$UPLOAD_PORT" == /dev/tty.* ]]; then
            CU_PORT="${UPLOAD_PORT/tty/cu}"
            echo "ℹ️  Auto-fixing port for macOS upload..."
            echo "   Changed $UPLOAD_PORT -> $CU_PORT"
            UPLOAD_PORT="$CU_PORT"
        fi
    else
        read -p "Enter Port Manually: " UPLOAD_PORT
    fi
fi

if [ -z "$UPLOAD_PORT" ]; then
    echo "❌ Error: Port cannot be empty."
    exit 1
fi

# --- 4. Summary & Confirmation ---
echo ""
echo "========================================"
echo "       PROJECT SUMMARY"
echo "========================================"
echo "Name:      $PROJ_NAME"
echo "Location:  $TARGET_DIR"
echo "Board:     $BOARD_FQBN"
echo "Port:      $UPLOAD_PORT"
echo "========================================"
read -p "Create this project? (y/N): " CONFIRM

if [[ "$CONFIRM" != "y" && "$CONFIRM" != "Y" ]]; then
    echo "❌ Aborted. No changes made."
    exit 0
fi

# --- 5. Create Directories & Files ---
echo ""
echo "Creating project '$PROJ_NAME'..."

mkdir -p "$TARGET_DIR"

# A. Create the main .ino file
cat <<EOF > "$TARGET_DIR/$PROJ_NAME.ino"
void setup() {
  // Setup code here, to run once:
}

void loop() {
  // Main code here, to run repeatedly:
}
EOF

# B. Create the config.mk
cat <<EOF > "$TARGET_DIR/config.mk"
# Configuration for $PROJ_NAME
BOARD := $BOARD_FQBN
PORT  := $UPLOAD_PORT
# BAUD  := 9600
EOF

# C. Create the Proxy Makefile
cat <<EOF > "$TARGET_DIR/Makefile"
# ==========================================
#   PROJECT PROXY MAKEFILE
# ==========================================
ROOT_DIR := ../..
PROJECT  := \$(notdir \$(CURDIR))

.PHONY: default
default:
	\$(MAKE) -C \$(ROOT_DIR) compile s=\$(PROJECT)

%:
	\$(MAKE) -C \$(ROOT_DIR) \$@ s=\$(PROJECT)
EOF

# --- 6. Final Output ---
echo "✅ Project created successfully at: $TARGET_DIR"
echo ""
echo "Next steps:"
echo "  1. cd $TARGET_DIR"
echo "  2. make upload"
