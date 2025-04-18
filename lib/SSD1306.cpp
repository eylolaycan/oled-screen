#include "SSD1306.hpp"
#include "fonts5x7.hpp"

#include <fcntl.h>          // open()
#include <unistd.h>         // write(), close(), sleep()
#include <sys/ioctl.h>      // ioctl()
#include <linux/i2c-dev.h>  // for I2C 
#include <cstring>          // memset(), memcpy()
#include <iostream>         // std:cerr, std::cout

/*
 * constructor function
 * i2c_adrr = OLED's address
 * address(...) = initializer list
 */
SSD1306::SSD1306(uint8_t i2c_addr) : address(i2c_addr) {
    file_i2c = open("/dev/i2c-1", O_RDWR);                // /dev/i2c-1 is path of I2C port, O_RDWR : for reading and writing
    if (file_i2c < 0) {                                   // if cant open, file_i2c is assigned -1
        std::cerr << "I2C interface cannot be opened!\n"; // error msg
        exit(1);
    }

    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) { // input/output control, sets device as slave, if does not work, assigned -1
        std::cerr << "Cannot connect to OLED!\n";  // error msg
        exit(1);
    }

    /*
     * void* memset(void* ptr, int value, size_t num);
     * fill the address with the value in size of num
     */
    memset(framebuffer, 0x00, sizeof(framebuffer)); // framebuffer = OLED, 0x00 : all bits are 0 = screen is completely black, framebuffer size
}

// deconstructor
SSD1306::~SSD1306() {
    if (file_i2c >= 0) close(file_i2c);
}

// command
void SSD1306::sendCommand(uint8_t cmd) {
    uint8_t buffer[2] = {0x00, cmd}; // 0x00 : command, cmd : is the command to send
    write(file_i2c, buffer, 2);      // writes these 2 bytes to I2C
}

void SSD1306::sendData(uint8_t* data, size_t size) {
    uint8_t buffer[129]; // I am sending data to + the data from the framebuffer
    buffer[0] = 0x40;    // sending data 

    // divides data to parts 
    while (size > 0) {
        size_t chunkSize = (size > 128) ? 128 : size; // size left from division

        /*
         * void* memcpy(void* destination, const void* source, size_t num);
         * destionation = where datas are copied
         * source = where datas are taken
         * num = byte number
         */
        memcpy(&buffer[1], data, chunkSize);
        write(file_i2c, buffer, chunkSize + 1);       // data + control 
        data += chunkSize;
        size -= chunkSize;
    }
}

void SSD1306::initialize() {
    sendCommand(0xAE);
    sendCommand(0xD5); sendCommand(0x80);
    sendCommand(0xA8); sendCommand(0x3F);
    sendCommand(0xD3); sendCommand(0x00);
    sendCommand(0x40);
    sendCommand(0x8D); sendCommand(0x14);
    sendCommand(0x20); sendCommand(0x00);
    sendCommand(0xA1);
    sendCommand(0xC8);
    sendCommand(0xDA); sendCommand(0x12);
    sendCommand(0x81); sendCommand(0xCF);
    sendCommand(0xD9); sendCommand(0xF1);
    sendCommand(0xDB); sendCommand(0x40);
    sendCommand(0xA4);
    sendCommand(0xA6);
    sendCommand(0xAF);
}

void SSD1306::clearDisplay() {
    memset(framebuffer, 0x00, sizeof(framebuffer));
}

void SSD1306::display() {
    sendCommand(0x21); sendCommand(0); sendCommand(127); // column address, starting col, finishing col
    sendCommand(0x22); sendCommand(0); sendCommand(7);   // page address, startign page, ending page

    for (int i = 0; i < 8; ++i) {
        sendData(&framebuffer[i * 128], 128);            // 128 byte per page, 8 * 128 = 1024 byte (whole screen)
    }
}

void SSD1306::drawText(int x, int y, const std::string& text) {
    int col = 0;
    for (char c : text) {
        if (c < 32 || c > 127) c = '?';              // ASCII only supports 32 tp 127
        if (col + 6 > 1024) break;                   // 5 byte font + 1 byte space, to prevent overrun

        for (int i = 0; i < 5; ++i)                  // every char ahs 5 col bitmap
            framebuffer[col++] = font5x7[c - 32][i]; // writes every byte to framebuffer

        framebuffer[col++] = 0x00;                   // space between chars 
    }
}
