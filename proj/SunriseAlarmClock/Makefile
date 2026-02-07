# ==========================================
#   PROJECT PROXY MAKEFILE
# ==========================================
ROOT_DIR := ../..
PROJECT  := $(notdir $(CURDIR))

.PHONY: default
default:
	$(MAKE) -C $(ROOT_DIR) compile s=$(PROJECT)

%:
	$(MAKE) -C $(ROOT_DIR) $@ s=$(PROJECT)
