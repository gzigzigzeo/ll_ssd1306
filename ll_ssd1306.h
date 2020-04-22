// (c) Viktor Sokolov, https://github.com/gzigzigzeo
// MIT license

// LL_SSD1306 command sequence generator and predefined commands.
// Refer to the LL_SSD1306 data sheet for details
// https://cdn-shop.adafruit.com/datasheets/LL_SSD1306.pdf
#ifndef __LL_SSD1306_CMD
#define __LL_SSD1306_CMD

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Utility macros
#define LL_SSD1306_ARG_2BITS(A) ((A) & 0b11)
#define LL_SSD1306_ARG_3BITS(A) ((A) & 0b111)
#define LL_SSD1306_ARG_4BITS(A) ((A) & 0b1111)
#define LL_SSD1306_ARG_6BITS(A) ((A) & 0b111111)

// Code: 3Eh
// NOP
#define LL_SSD1306_CMD_NOP 0xE3

// Code: 00~0Fh
// Sets the lower nibble of column start, 0..0xF
#define LL_SSD1306_CMD_SET_LOW_PAM_START_ADDRESS(n) LL_SSD1306_ARG_4BITS(n)

// Code: 10~1Fh
// Sets the higher nibble of column start, 0..0xF
#define LL_SSD1306_CMD_SET_HIGH_PAM_START_ADDRESS(n) LL_SSD1306_ARG_4BITS(n) | 0x10

// Code: 20h, A[1:0]
// Sets the addressing mode
enum {
	LL_SSD1306_ADDRESSING_MODE_HORIZONTAL = 0b00,
	LL_SSD1306_ADDRESSING_MODE_VERTICAL   = 0b01,
	LL_SSD1306_ADDRESSING_MODE_PAGE       = 0b10
};

#define LL_SSD1306_CMD_SET_ADDRESSING_MODE(mode) 0x20, LL_SSD1306_ARG_2BITS(mode)

// Code: 21h, A[5:0], B[5:0]
// Sets the column start and end addresses
#define LL_SSD1306_CMD_SET_COLUMN_ADDRESS(start, end) 0x24, LL_SSD1306_ARG_6BITS(start), LL_SSD1306_ARG_6BITS(end)

// Code: 22h, A[2:0], B[2:0]
// Sets the page address
#define LL_SSD1306_CMD_SET_PAGE_ADDRESS(start, end) 0x22, LL_SSD1306_ARG_3BITS(start), LL_SSD1306_ARG_3BITS(end)

// Code: 40h~7Fh, A[5:0]
// Sets display start line
#define LL_SSD1306_CMD_SET_DISPLAY_START_LINE(number) (0x40 + (LL_SSD1306_ARG_6BITS(number)))

// Code: 81h
// Sets contrast, A[7:0]
enum {
	LL_SSD1306_CONTRAST_LOW = 5,
	LL_SSD1306_CONTRAST_MEDIUM = 127,
	LL_SSD1306_CONTRAST_HIGH = 255,
};

#define LL_SSD1306_CMD_SET_CONTRAST(contrast) 0x81, contrast

// Code: A0h/A1h
// Segment remap (practically means horizontal mirroring)
#define LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF 0xA0
#define LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_ON  0xA1

// Code: A4h/A5h
// Turns entire display ON
#define LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF 0xA4
#define LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_ON  0xA5

// Code: A6h/A7h
// Sets Normal/Inverse display
#define LL_SSD1306_CMD_INVERT_OFF 0xA6
#define LL_SSD1306_CMD_INVERT_ON  0xA7

// Code: A8h, A[5:0]
// Sets multiplex ratio (number of COM pads on the screen cable)
enum {
	LL_SSD1306_MULTIPLEX_RATIO_FOR_32_LINES = 0x1F,
	LL_SSD1306_MULTIPLEX_RATIO_FOR_64_LINES = 0x3F
};

#define LL_SSD1306_CMD_SET_MULTIPLEX_RATIO(ratio) 0xA8, LL_SSD1306_ARG_6BITS(ratio)

// Code: AEh/AFh
// Sets display ON/OFF (essentially sleep mode/normal mode)
#define LL_SSD1306_CMD_SET_SLEEP_MODE_OFF 0xAF
#define LL_SSD1306_CMD_SET_SLEEP_MODE_ON  0xAE

// Code: B0h~B7h, A[2:0]
// Sets page start address in page addressing mode
#define LL_SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(page) (0xB0 + (LL_SSD1306_ARG_3BITS(page)))

// Code: C0h/C8h
// Sets COM output scan direction (practically means vertical mirroring)
#define LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF 0xC0
#define LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_ON  0xC8

// Code: D3h, A[5:0]
// Sets display offset, vertical shift by COM
#define LL_SSD1306_CMD_SET_DISPLAY_OFFSET(shift) 0xD3, LL_SSD1306_ARG_6BITS(shift)

// Code: D5h, A[7:0] (4 + 4 bits)
// Sets display clock divide ratio and oscillator frequency (practically means
// refresh rate, see data sheet for the formula).
#define LL_SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(d, fosc) \
	0xD5, (LL_SSD1306_ARG_4BITS(d) << 4) | LL_SSD1306_ARG_4BITS(fosc)

// Code: D9h, A[7:0] (4 + 4 bits)
// Sets pre-charge period
#define LL_SSD1306_CMD_SET_PRE_CHARGE_PERIOD(phase1, phase2) \
	0xD9, LL_SSD1306_ARG_4BITS(phase2) << 4 | LL_SSD1306_ARG_4BITS(phase1)

// Code: DAh, A[5:4]
// Set COM pins hardware configuration
enum {
	LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_32_LINES = 0x02,
	LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_64_LINES = 0x12
};

#define LL_SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(config) 0xDA, config

// Code: DBh, A[6::4]
// Sets Vcomh deselect level
enum {
	LL_SSD1306_DESELECT_LEVEL_0_65VCC = 0x0,
	LL_SSD1306_DESELECT_LEVEL_0_77VCC = 0x20, // Default/Reset
	LL_SSD1306_DESELECT_LEVEL_0_83VCC = 0x30
};

#define LL_SSD1306_CMD_SET_DESELECT_LEVEL(level) 0xDB, level

// Code: 8Dh, A[7:0]
// Enables charge pump regulator
enum {
	LL_SSD1306_CHARGE_PUMP_ENABLED  = 0x14,
	LL_SSD1306_CHARGE_PUMP_DISABLED = 0x10
};

#define LL_SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(enable) 0x8D, enable

#define LL_SSD1306_CMD_STARTUP_128x64 \
	LL_SSD1306_CMD_SET_MULTIPLEX_RATIO(LL_SSD1306_MULTIPLEX_RATIO_FOR_64_LINES), \
	LL_SSD1306_CMD_SET_DISPLAY_OFFSET(0), \
	LL_SSD1306_CMD_SET_DISPLAY_START_LINE(0), \
	LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF, \
	LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF, \
	LL_SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_64_LINES), \
	LL_SSD1306_CMD_SET_CONTRAST(LL_SSD1306_CONTRAST_HIGH), \
	LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF, \
	LL_SSD1306_CMD_INVERT_OFF, \
	LL_SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0x8, 0x0), \
	LL_SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(LL_SSD1306_CHARGE_PUMP_ENABLED)

#define LL_SSD1306_CMD_STARTUP_128x32 \
	LL_SSD1306_CMD_SET_MULTIPLEX_RATIO(LL_SSD1306_MULTIPLEX_RATIO_FOR_32_LINES), \
	LL_SSD1306_CMD_SET_DISPLAY_OFFSET(0), \
	LL_SSD1306_CMD_SET_DISPLAY_START_LINE(0), \
	LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF, \
	LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF, \
	LL_SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_32_LINES), \
	LL_SSD1306_CMD_SET_CONTRAST(LL_SSD1306_CONTRAST_HIGH), \
	LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF, \
	LL_SSD1306_CMD_INVERT_OFF, \
	LL_SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0xF, 0x0), \
	LL_SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(LL_SSD1306_CHARGE_PUMP_ENABLED)

#define LL_SSD1306_CMD_SET_PAGE(page) \
	LL_SSD1306_CMD_SET_ADDRESSING_MODE(LL_SSD1306_ADDRESSING_MODE_PAGE), \
	LL_SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(page), \
	LL_SSD1306_CMD_SET_LOW_PAM_START_ADDRESS(0), \
	LL_SSD1306_CMD_SET_HIGH_PAM_START_ADDRESS(0)

#ifdef __cplusplus
}
#endif

#endif
