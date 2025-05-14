# 🖥️ OLED Screen Writer – Raspberry Pi Zero 2 W

A simple and lightweight C++ project for writing text to an **SSD1306 OLED screen** using Raspberry Pi Zero 2 W. The project is designed for **headless SSH development** and directly communicates with the OLED screen over **I2C**.

---

## ✅ Features

- Text rendering on 128x64 SSD1306 OLED display
- Framebuffer-based character drawing using custom 5x7 font
- Basic graphics primitives (horizontal lines, pixel control)
- Built with `g++` and standard Makefile
- SSH-based deployment and execution (no GUI required)

---

## 💡 Project Structure


```

oled-screen/
├── fonts/ # 5x7 bitmap fonts used for rendering
├── include/ # Header files for display and utilities
├── lib/ # OLED screen driver implementation
├── src/ # Main application (entry point)
├── oled_test # Compiled binary for quick testing
└── Makefile # Build configuration

---

## 🧰 Requirements

- Raspberry Pi Zero 2 W (or any Pi with I2C)
- SSD1306 OLED screen (128x64, I2C interface)
- C++17 compiler (e.g., `g++`)
- Wiring:


```

| OLED Pin | Raspberry Pi Pin |
|----------|------------------|
| GND      | GND              |
| VCC      | 3.3V             |
| SDA      | GPIO 2 (SDA)     |
| SCL      | GPIO 3 (SCL)     |

---

## 🛠️ How to Build & Run

### Build

```bash
make
```

Run (over SSH or terminal)
```
./oled_test
```
