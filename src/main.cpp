#include <iostream>
#include <unistd.h>
#include "SSD1306.hpp"
#include "fonts5x7.hpp"

int main() {
    SSD1306 oled(0x3C);

    std::cout << "OLED is initialized..." << std::endl;
    oled.initialize();

    std::cout << "cleaning the display..." << std::endl;
    oled.clearDisplay();

    std::cout << "preparing the text..." << std::endl;
    oled.drawText(0, 0, "Merhaba EYLÜL!");

    std::cout << "writing on the display..." << std::endl;
    oled.display();

    sleep(60);
    return 0;
}
