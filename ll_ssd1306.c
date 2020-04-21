#include <ll_1306.h>

// This is the default startup sequence from the datasheet for 128x64 screen.
// Display ON command is not included.
static const uint8_t ssd1306_128x64_startup_sequence_buffer[] = {
	SSD1306_CMD_SET_MULTIPLEX_RATIO(SSD1306_MULTIPLEX_RATIO_FOR_64_LINES),
	SSD1306_CMD_SET_DISPLAY_OFFSET(0),
	SSD1306_CMD_SET_DISPLAY_START_LINE(0),
	SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF,
	SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF,
	SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_64_LINES),
	SSD1306_CMD_SET_CONTRAST(SSD1306_CONTRAST_HIGH),
	SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF,
	SSD1306_CMD_INVERT_OFF,
	SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0x8, 0x0),
	SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(SSD1306_CHARGE_PUMP_ENABLED),
};

// This is the default startup sequence from the datasheet for 128x32 screen.
// Display ON command is not included.
const uint8_t ssd1306_128x32_startup_sequence_buffer[] = {
	SSD1306_CMD_SET_MULTIPLEX_RATIO(SSD1306_MULTIPLEX_RATIO_FOR_32_LINES),
	SSD1306_CMD_SET_DISPLAY_OFFSET(0),
	SSD1306_CMD_SET_DISPLAY_START_LINE(0),
	SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF,
	SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF,
	SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_32_LINES),
	SSD1306_CMD_SET_CONTRAST(SSD1306_CONTRAST_HIGH),
	SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF,
	SSD1306_CMD_INVERT_OFF,
	SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0xF, 0x0),
	SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(SSD1306_CHARGE_PUMP_ENABLED),
};

static uint8_t set_page_cmd_buffer[] = {
		SSD1306_CMD_SET_ADDRESSING_MODE(SSD1306_ADDRESSING_MODE_PAGE),
		SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(0),
		SSD1306_CMD_SET_LOW_PAM_START_ADDRESS(0),
		SSD1306_CMD_SET_HIGH_PAM_START_ADDRESS(0)
};

const ssd1306_buffer_t ssd1306_128x64_startup_cmd = {
	.buffer = ssd1306_128x64_startup_sequence_buffer,
	.size = sizeof(ssd1306_128x64_startup_sequence_buffer)
};

const ssd1306_buffer_t ssd1306_128x32_startup_cmd = {
	.buffer = ssd1306_128x32_startup_sequence_buffer,
	.size = sizeof(ssd1306_128x32_startup_sequence_buffer)
};

const ssd1306_buffer_t ssd1306_set_page_and_zero_address_cmd = {
	.buffer = set_page_cmd_buffer,
	.size = sizeof(set_page_cmd_buffer)
}

uint8_t* ssd1306_set_page_cmd(uint8_t page) {
	*(ssd1306_set_page_and_zero_address_cmd+2) =
		SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(page);

	return set_page_cmd;
}
