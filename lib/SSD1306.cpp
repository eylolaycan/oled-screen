#include "SSD1306.hpp"
#include "fonts5x7.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstring>
#include <iostream>

SSD1306::SSD1306(uint8_t i2c_addr) : address(i2c_addr) {
    file_i2c = open("/dev/i2c-1", O_RDWR);
    if (file_i2c < 0) {
        std::cerr << "I2C interface cannot be opened!\n";
        exit(1);
    }

    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
        std::cerr << "Cannot connect to OLED!\n";
        exit(1);
    }

    memset(framebuffer, 0x00, sizeof(framebuffer));
}

SSD1306::~SSD1306() {
    if (file_i2c >= 0) close(file_i2c);
}

void SSD1306::sendCommand(uint8_t cmd) {
    uint8_t buffer[2] = {0x00, cmd};
    write(file_i2c, buffer, 2);
}

void SSD1306::sendData(uint8_t* data, size_t size) {
    uint8_t buffer[129];
    buffer[0] = 0x40;

    while (size > 0) {
        size_t chunkSize = (size > 128) ? 128 : size;
        memcpy(&buffer[1], data, chunkSize);
        write(file_i2c, buffer, chunkSize + 1);
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
    sendCommand(0x21); sendCommand(0); sendCommand(127);
    sendCommand(0x22); sendCommand(0); sendCommand(7);

    for (int i = 0; i < 8; ++i) {
        sendData(&framebuffer[i * 128], 128);
    }
}

void SSD1306::drawText(int x, int y, const std::string& text) {
    int col = 0;
    for (char c : text) {
        if (c < 32 || c > 127) c = '?';
        if (col + 6 > 1024) break;

        for (int i = 0; i < 5; ++i)
            framebuffer[col++] = font5x7[c - 32][i];

        framebuffer[col++] = 0x00;
    }
}
