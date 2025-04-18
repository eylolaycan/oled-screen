CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Ifonts

SRC = src/main.cpp lib/SSD1306.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = oled_test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
