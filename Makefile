CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2 SDL2_image)
LIBS     := $(shell pkg-config --libs sdl2 SDL2_image)

PREFIX     ?= /usr/local
BINDIR     ?= $(PREFIX)/bin
DATADIR    ?= $(PREFIX)/share
DESKTOPDIR ?= $(DATADIR)/applications

SRC_DIR   := src
BUILD_DIR := build

SRCS   := $(wildcard $(SRC_DIR)/*.cpp)
OBJS   := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET := $(BUILD_DIR)/vivy

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(ARGS)

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/vivy
	@if [ -f vivy.desktop ]; then \
		install -Dm644 vivy.desktop $(DESTDIR)$(DESKTOPDIR)/vivy.desktop; \
	fi

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/vivy
	rm -f $(DESTDIR)$(DESKTOPDIR)/vivy.desktop

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run install uninstall
