# LL_SSD1306

SSD1306 OLED display controller command generator.

[Datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)

# Motivation

I wanted to have library as tiny as possible to work with SSD1306 in my project. I also wanted to figure out for myself how this chip works and in details.

There is an excellent library [u8g2](https://github.com/olikraus/u8g2) which supports lots if not all OLED monochrome displays. It also capable of drawing, displaying text, glyps, etc. The point is that in my project I use just one, specific OLED module, for debugging purposes mostly. I do not want any size or speed overhead from the universal library.

This library consists of chip command macro definitions. It does not care about transport layer and even displaying text. You have to implement whatever transport and drawing functions you want in your firmware.

# Installation

```c
brew install clib && clib install gzigzigzeo/ll_ssd1306 -o vendor
```

or just copy `ll_ssd1306.*` to your dependency folder.

# Example (STM32, HAL, I2C)

```c
#define DISPLAY_INTERFACE        &hi2c2       // IIC2
#define DISPLAY_ADDRESS          (0x3C << 1)  // 7-bit master address
#define DISPLAY_COMMAND_DR_VALUE 0x0          // Command prefix
#define DISPLAY_DATA_DR_VALUE    0x40         // RAM write prefix
#define DISPLAY_LINES            8            // Number of lines (64 px)
#define DISPLAY_WIDTH            128          // Width
#define ARR_WITH_SIZE(A)         (uint8_t*)A, sizeof(A)

// Sends command to the display.
HAL_StatusTypeDef display_send_cmd(uint8_t* cmd, uint8_t size) {
  // You might want to use _DMA or _IT
  return HAL_I2C_Mem_Write(
    DISPLAY_INTERFACE,
    DISPLAY_ADDRESS,
    DISPLAY_COMMAND_DR_VALUE,
    I2C_MEMADD_SIZE_8BIT,
    cmd,
    size,
    HAL_MAX_DELAY
  );
}

// Writes display RAM
HAL_StatusTypeDef display_send_data(uint8_t* data, uint8_t size) {
  return HAL_I2C_Mem_Write(
    DISPLAY_INTERFACE,
    DISPLAY_ADDRESS,
    DISPLAY_DATA_DR_VALUE,
    I2C_MEMADD_SIZE_8BIT,
    data,
    size,
    HAL_MAX_DELAY
  );
}

int main() {
  // Let's assume all perepherials are initialized already. Using HAL might be the bad
  // idea in terms of firmware size. Let's use it here for the sake of simplicity.

  // Startup cmd
  uint8_t display_startup_cmd[] = {
		  LL_SSD1306_CMD_STARTUP_128x64,
		  LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_ON,
		  LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_ON,
		  LL_SSD1306_CMD_SET_SLEEP_MODE_OFF
  };

  // Sends the startup sequence
  display_send(DISPLAY_COMMAND_DR_VALUE, ARR_WITH_SIZE(display_startup_cmd));

  while (1)
  {
    uint8_t white_tile[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t black_tile[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    for (int i = 0; i < DISPLAY_LINES; i++) {
      // Sets the display page (line of 8 px vertically)
      uint8_t set_page_cmd[] = { LL_SSD1306_SET_PAGE_CMD(i) };
      display_send_cmd(ARR_WITH_SIZE(set_page_cmd));

      // Displays line of chess board
      for (int n = 0; n < DISPLAY_WIDTH / sizeof(white_tile); n++) {
        if (i % 2 == n % 2) {
          display_send_data(white_tile, sizeof(white_tile));
        } else {
          display_send_data(black_tile, sizeof(black_tile));
        }
      }
    }

    // ...
  }
}
```
