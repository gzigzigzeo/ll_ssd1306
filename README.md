# LL_SSD1306

SSD1306 OLED display controller command generator.

[Datasheet](https://cdn-shop.adafruit.com/datasheets/LL_SSD1306.pdf)

# Motivation

I wanted to have library as tiny as possible to work with SSD1306 in my project. I also wanted to figure out for myself how this chip works and how in details.

There is an excellent library [u8g2](https://github.com/olikraus/u8g2) which supports lots if not all OLED monochrome displays. It also capable of drawing, displaying text, glyps, etc. The point is that in my project I use just one, specific OLED module, for debugging purposes mostly. I do not want any size or speed overhead from the universal library.

This library consists of chip command macro definitions. It does care about transport layer and even displaying text. You have to implement whatever transport and drawing functions you want in your firmware.

# Installation

```c
brew install clib && clib install gzigzigzeo/ll_ssd1306 -o vendor
```

or just copy `ll_ssd1306.*` to your dependency folder.

# Example (STM32, HAL, I2C)

```c
#define DISPLAY_INTERFACE  &hi2c2
#define DISPLAY_ADDRESS    (0x3C << 1)
#define DISPLAY_COMMAND_DR 0x0
#define DISPLAY_DATA_DR    0x40
#define DISPLAY_LINES      8
#define ARR_WITH_SIZE(A)   (A), sizeof(A)

// Sends command to the display.
HAL_StatusTypeDef display_send_cmd(uint8_t* cmd, uint8_t size) {
  // You might want to use _DMA or _IT
  HAL_I2C_Mem_Write(
    DISPLAY_INTERFACE,
    DISPLAY_ADDRESS,
    DISPLAY_COMMAND_DR,
    I2C_MEMADD_SIZE_8BIT,
    cmd->buffer,
    cmd->size
  );
}

// Writes display RAM
HAL_StatusTypeDef display_send_data(uint8_t* data, uint8_t size) {
  HAL_I2C_Mem_Write(
    DISPLAY_INTERFACE,
    DISPLAY_ADDRESS,
    DISPLAY_DATA_DR,
    I2C_MEMADD_SIZE_8BIT,
    data,
    size
  );
}

int main() {
  // Let's assume all perepherials are initialized already. Using HAL might be the bad
  // idea in terms of firmware size. Let's use it here for the sake of simplicity.

  // Sends the startup sequence
  display_send_cmd(ARR_WITH_SIZE(ll_ssd1306_128x64_startup_cmd));

  // Sets mirroring both vertical and horizontal (display upside down)
  display_send_cmd(ARR_WITH_SIZE(ll_ssd1306_cmd_mirror_hv));

  // Wakes display up
  display_send_cmd(ARR_WITH_SIZE(ll_ssd1306_cmd_display_on));

  uint8_t white_tile[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t black_tile[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  for (int i = 0; i < DISPLAY_LINES; i++) {
    display_send_cmd(ll_ssd1306_set_page_cmd(l));

    for (int n = 0; n < 4; n++) {
      dispaly_send_data(i % 1 == 0 & n % 1 == 0 ? ARR_WITH_SIZE(white_tile) : ARR_WITH_SIZE(black_tile));
    }
  }

  // ...
}
```
