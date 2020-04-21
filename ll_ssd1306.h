// SSD1306 command sequence generator and predefined commands.
// Refer to the SSD1306 data sheet for details https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
#ifndef __SSD1306_CMD
#define __SSD1306_CMD

#include <stdint.h>
#include <_ansi.h>

_BEGIN_STD_C

// Utility macros
#define SSD1306_ARG_2BITS(A) ((A) & 0b11)
#define SSD1306_ARG_3BITS(A) ((A) & 0b111)
#define SSD1306_ARG_4BITS(A) ((A) & 0b1111)
#define SSD1306_ARG_6BITS(A) ((A) & 0b111111)

// Command buffer
typedef struct  = {
	uint8_t *buffer;
	uint8_t size;
} ssd1306_buffer_t;

// Code: 3Eh
// NOP
#define SSD1306_CMD_NOP 0xE3

// Code: 00~0Fh
// Sets the lower nibble of column start, 0..0xF
#define SSD1306_CMD_SET_LOW_PAM_START_ADDRESS(n) SSD1306_ARG_4BITS(n)

// Code: 10~1Fh
// Sets the higher nibble of column start, 0..0xF
#define SSD1306_CMD_SET_HIGH_PAM_START_ADDRESS(n) SSD1306_ARG_4BITS(n) | 0x10

// Code: 20h, A[1:0]
// Sets the addressing mode
enum {
	SSD1306_ADDRESSING_MODE_HORIZONTAL = 0b00,
	SSD1306_ADDRESSING_MODE_VERTICAL   = 0b01,
	SSD1306_ADDRESSING_MODE_PAGE       = 0b10
};

#define SSD1306_CMD_SET_ADDRESSING_MODE(mode) 0x20, SSD1306_ARG_2BITS(mode)

// Code: 21h, A[5:0], B[5:0]
// Sets the column start and end addresses
#define SSD1306_CMD_SET_COLUMN_ADDRESS(start, end) 0x24, SSD1306_ARG_6BITS(start), SSD1306_ARG_6BITS(end)

// Code: 22h, A[2:0], B[2:0]
// Sets the page address
#define SSD1306_CMD_SET_PAGE_ADDRESS(start, end) 0x22, SSD1306_ARG_3BITS(start), SSD1306_ARG_3BITS(end)

// Code: 40h~7Fh, A[5:0]
// Sets display start line
#define SSD1306_CMD_SET_DISPLAY_START_LINE(number) (0x40 + (SSD1306_ARG_6BITS(number)))

// Code: 81h
// Sets contrast, A[7:0]
enum {
	SSD1306_CONTRAST_LOW = 5,
	SSD1306_CONTRAST_MEDIUM = 127,
	SSD1306_CONTRAST_HIGH = 255,
};

#define SSD1306_CMD_SET_CONTRAST(contrast) 0x81, contrast

// Code: A0h/A1h
// Segment remap (practically means horizontal mirroring)
#define SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF 0xA0
#define SSD1306_CMD_SET_HORIZONTAL_MIRRORING_ON  0xA1

// Code: A4h/A5h
// Turns entire display ON
#define SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF 0xA4
#define SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_ON  0xA5

// Code: A6h/A7h
// Sets Normal/Inverse display
#define SSD1306_CMD_INVERT_OFF 0xA6
#define SSD1306_CMD_INVERT_ON  0xA7

// Code: A8h, A[5:0]
// Sets multiplex ratio (number of COM pads on the screen cable)
enum {
	SSD1306_MULTIPLEX_RATIO_FOR_32_LINES = 0x1F,
	SSD1306_MULTIPLEX_RATIO_FOR_64_LINES = 0x3F
};

#define SSD1306_CMD_SET_MULTIPLEX_RATIO(ratio) 0xA8, SSD1306_ARG_6BITS(ratio)

// Code: AEh/AFh
// Sets display ON/OFF (essentially sleep mode/normal mode)
#define SSD1306_CMD_SET_SLEEP_MODE_OFF 0xAF
#define SSD1306_CMD_SET_SLEEP_MODE_ON  0xAE

// Code: B0h~B7h, A[2:0]
// Sets page start address in page addressing mode
#define SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(page) (0xB0 + (SSD1306_ARG_3BITS(page)))

// Code: C0h/C8h
// Sets COM output scan direction (practically means vertical mirroring)
#define SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF 0xC0
#define SSD1306_CMD_SET_VERTICAL_MIRRORING_ON  0xC8

// Code: D3h, A[5:0]
// Sets display offset, vertical shift by COM
#define SSD1306_CMD_SET_DISPLAY_OFFSET(shift) 0xD3, SSD1306_ARG_6BITS(shift)

// Code: D5h, A[7:0] (4 + 4 bits)
// Sets display clock divide ratio and oscillator frequency (practically means
// refresh rate, see data sheet for the formula).
#define SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(d, fosc) \
	0xD5, (SSD1306_ARG_4BITS(d) << 4) | SSD1306_ARG_4BITS(fosc)

// Code: D9h, A[7:0] (4 + 4 bits)
// Sets pre-charge period
#define SSD1306_CMD_SET_PRE_CHARGE_PERIOD(phase1, phase2) \
	0xD9, SSD1306_ARG_4BITS(phase2) << 4 | SSD1306_ARG_4BITS(phase1)

// Code: DAh, A[5:4]
// Set COM pins hardware configuration
enum {
	SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_32_LINES = 0x02,
	SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_64_LINES = 0x12
};

#define SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(config) 0xDA, config

// Code: DBh, A[6::4]
// Sets Vcomh deselect level
enum {
	SSD1306_DESELECT_LEVEL_0_65VCC = 0x0,
	SSD1306_DESELECT_LEVEL_0_77VCC = 0x20, // Default/Reset
	SSD1306_DESELECT_LEVEL_0_83VCC = 0x30
};

#define SSD1306_CMD_SET_DESELECT_LEVEL(level) 0xDB, level

// Code: 8Dh, A[7:0]
// Enables charge pump regulator
enum {
	SSD1306_CHARGE_PUMP_ENABLED  = 0x14,
	SSD1306_CHARGE_PUMP_DISABLED = 0x10
};

#define SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(enable) 0x8D, enable

extern const ssd1306_buffer_t ssd1306_128x64_startup_cmd;
extern const ssd1306_buffer_t ssd1306_128x32_startup_cmd;

uint8_t* ssd1306_set_page_cmd(uint8_t page);

_END_STD_C

#endif
