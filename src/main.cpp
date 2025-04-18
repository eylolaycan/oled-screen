#include <iostream>
#include <unistd.h>
#include "SSD1306.hpp"
#include "fonts5x7.hpp"

int main() {
    SSD1306 oled(0x3C);

    std::cout << "OLED başlatılıyor..." << std::endl;
    oled.initialize();

    std::cout << "Temizleniyor..." << std::endl;
    oled.clearDisplay();

    std::cout << "Yazı hazırlanıyor..." << std::endl;
    oled.drawText(0, 0, "Merhaba EYLÜL!");

    std::cout << "Ekrana yaziliyor..." << std::endl;
    oled.display();

    sleep(60);
    return 0;
}
