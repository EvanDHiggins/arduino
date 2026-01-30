# ==========================================
#   MASTER ARDUINO MONOREPO MAKEFILE
# ==========================================

# --- Directory Paths ---
PROJ_DIR  := proj
LIB_DIR   := lib
BUILD_DIR := build

# --- Input Parsing & Configuration ---
# 1. Check if 's' (sketch) was passed.
#    If not, we can't load specific configs yet.
ifdef s
    # 2. Try to load per-project config (config.mk)
    #    This allows each project to define its own BOARD, PORT, etc.
    -include $(PROJ_DIR)/$(s)/config.mk
endif

# --- Defaults ---
# These apply if the project's config.mk doesn't override them.
BOARD    ?= arduino:avr:uno
PORT     ?= /dev/cu.usbmodem1101
BAUD     ?= 9600

# --- Helper Functions ---
# A macro to check if 's' is defined before running target-specific commands
define check_sketch
    @if [ -z "$(s)" ]; then \
        echo "⚠️  Error: No project specified."; \
        echo "   Usage: make <command> s=<project_name>"; \
        echo "   Or run 'make' from inside a project directory."; \
        exit 1; \
    fi
endef

# ==========================================
#   MAIN TARGETS
# ==========================================

.PHONY: all
all: help

.PHONY: help
help:
	@echo "Arduino Monorepo Manager"
	@echo "------------------------"
	@echo "Targets:"
	@echo "  compile s=<proj>   : Compile a specific project"
	@echo "  upload s=<proj>    : Upload to board (compiles first)"
	@echo "  monitor            : Open serial monitor"
	@echo "  clean              : Remove all build artifacts"
	@echo ""
	@echo "Projects found in /$(PROJ_DIR):"
	@ls $(PROJ_DIR)

# --- 1. COMPILE ---
.PHONY: compile
compile:
	$(call check_sketch)
	@echo "🔨 Compiling project: $(s)..."
	@echo "   Board: $(BOARD)"
	@mkdir -p $(BUILD_DIR)/$(s)
	arduino-cli compile \
		--fqbn $(BOARD) \
		--libraries $(LIB_DIR) \
		--output-dir $(BUILD_DIR)/$(s) \
		$(PROJ_DIR)/$(s)

# --- 2. UPLOAD ---
.PHONY: upload
upload: compile
	$(call check_sketch)
	@echo "🚀 Uploading $(s) to $(PORT)..."
	arduino-cli upload \
		-p $(PORT) \
		--fqbn $(BOARD) \
		--input-dir $(BUILD_DIR)/$(s)

# --- 3. MONITOR ---
.PHONY: monitor
monitor:
	@echo "📺 Opening Serial Monitor on $(PORT) at $(BAUD) baud..."
	arduino-cli monitor -p $(PORT) --config baudrate=$(BAUD)

# --- 4. CLEAN ---
.PHONY: clean
clean:
	@echo "🧹 Removing build artifacts..."
	rm -rf $(BUILD_DIR)

# ==========================================
#   SHORTCUTS
# ==========================================
# Allows typing "make SunriseAlarm" from the root to compile it.
PROJECTS := $(shell ls $(PROJ_DIR))

.PHONY: $(PROJECTS)
$(PROJECTS):
	@$(MAKE) compile s=$@
