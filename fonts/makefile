# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I. -Iimgui -Iimgui-sfml

# Libraries
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lfreetype -lGL

# ImGui sources
IMGUI_SRC := imgui/imgui.cpp \
             imgui/imgui_draw.cpp \
             imgui/imgui_tables.cpp \
             imgui/imgui_widgets.cpp \
             imgui/imgui_demo.cpp \
             imgui-sfml/imgui-SFML.cpp

# Source files (all project .cpp + ImGui)
SRC := $(wildcard *.cpp) $(IMGUI_SRC)

# Object files in build folder
OBJ := $(patsubst %.cpp, build/%.o, $(SRC))

# Output binary
TARGET := build/app

# Default rule
all: $(TARGET)

# Build target
$(TARGET): $(OBJ)
	@echo "Linking $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Compile .cpp to .o inside build/
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program
run: $(TARGET)
	./$(TARGET)

# Clean build
clean:
	rm -rf build
