/* Once the header is included, 
 * it checks if a unique value 
 * (in this case HEADERFILE_H) 
 * is defined. Then if it's not 
 * defined, it defines it and 
 * continues to the rest of the page.
 */
#ifndef SSD1306_HPP
#define SSD1306_HPP

#include <string>  // std::string
#include <cstdint> // uint8_t : 8 bit, 16 bit...
#include <cstddef> // size_t : array size

class SSD1306 {
public:
    SSD1306(uint8_t i2c_addr = 0x3C); // constructor function
    ~SSD1306();                       // deconstructor function
    
    void initialize();
    void clearDisplay(); // cleans framebuffer[]
    void display();      // send framebuffer[] to OLED
    void drawText(int x, int y, const std::string& text);

private:
    int file_i2c;
    uint8_t address; // 0x30
    uint8_t framebuffer[1024]; // 1 byte = 8 pixels

    void sendCommand(uint8_t cmd);
    void sendData(uint8_t* data, size_t size);
};

#endif // closes head guard
