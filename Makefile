CXX = g++

# flags
# -std=c++17 C++17 standard
# -Wall 	 show all warnings
# -Wextra    show all extra warnings
# -Iinclude  search header files
# -Ifonts 	 search fonts hader files
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Ifonts

# source files
SRC = src/main.cpp lib/SSD1306.cpp

# changes all .cpp to .o
OBJ = $(SRC:.cpp=.o)

# file to run
TARGET = oled_test

# run when "make"
all: $(TARGET)

# $@ target file
# $^ all o.s
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# $< → source file (src/main.cpp)
# $@ → target file (src/main.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# for make clean
clean:
	rm -f $(OBJ) $(TARGET)
