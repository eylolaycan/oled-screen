#ifndef SSD1306_HPP
#define SSD1306_HPP

#include <string>
#include <cstdint>
#include <cstddef>

class SSD1306 {
public:
    SSD1306(uint8_t i2c_addr = 0x3C);
    ~SSD1306();

    void initialize();
    void clearDisplay();
    void display();
    void drawText(int x, int y, const std::string& text);

private:
    int file_i2c;
    uint8_t address;
    uint8_t framebuffer[1024];

    void sendCommand(uint8_t cmd);
    void sendData(uint8_t* data, size_t size);
};

#endif
