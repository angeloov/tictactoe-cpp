all: build run

GTKMM_FLAGS := `pkg-config gtkmm-4.0 --cflags --libs | sed 's/ -I/ -isystem /g'`

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := bin

build:
	g++ -std=c++17 -o $(BUILD_DIR)/client $(SRC_DIR)/*.cpp  $(GTKMM_FLAGS) -I$(INCLUDE_DIR) /c/Windows/System32/ws2_32.dll

run:
	$(BUILD_DIR)/client.exe
