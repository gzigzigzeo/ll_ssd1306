// (c) Viktor Sokolov, https://github.com/gzigzigzeo
// MIT license

#include <ll_ssd1306.h>

// This is the default startup sequence from the datasheet for 128x64 screen.
// Display ON command is not included.
static uint8_t ll_ssd1306_128x64_startup_sequence_buffer[] = {
	LL_SSD1306_CMD_SET_MULTIPLEX_RATIO(LL_SSD1306_MULTIPLEX_RATIO_FOR_64_LINES),
	LL_SSD1306_CMD_SET_DISPLAY_OFFSET(0),
	LL_SSD1306_CMD_SET_DISPLAY_START_LINE(0),
	LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF,
	LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF,
	LL_SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_64_LINES),
	LL_SSD1306_CMD_SET_CONTRAST(LL_SSD1306_CONTRAST_HIGH),
	LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF,
	LL_SSD1306_CMD_INVERT_OFF,
	LL_SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0x8, 0x0),
	LL_SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(LL_SSD1306_CHARGE_PUMP_ENABLED),
};

// This is the default startup sequence from the datasheet for 128x32 screen.
// Display ON command is not included.
static uint8_t ll_ssd1306_128x32_startup_sequence_buffer[] = {
	LL_SSD1306_CMD_SET_MULTIPLEX_RATIO(LL_SSD1306_MULTIPLEX_RATIO_FOR_32_LINES),
	LL_SSD1306_CMD_SET_DISPLAY_OFFSET(0),
	LL_SSD1306_CMD_SET_DISPLAY_START_LINE(0),
	LL_SSD1306_CMD_SET_HORIZONTAL_MIRRORING_OFF,
	LL_SSD1306_CMD_SET_VERTICAL_MIRRORING_OFF,
	LL_SSD1306_CMD_SET_COM_PIN_HARDWARE_CONFIG(LL_SSD1306_COM_PIN_HARDWARE_CONFIG_FOR_32_LINES),
	LL_SSD1306_CMD_SET_CONTRAST(LL_SSD1306_CONTRAST_HIGH),
	LL_SSD1306_CMD_ENABLE_ENTIRE_DISPLAY_OFF,
	LL_SSD1306_CMD_INVERT_OFF,
	LL_SSD1306_CMD_SET_CLK_RATIO_AND_OSC_FRQ(0xF, 0x0),
	LL_SSD1306_CMD_ENABLE_CHARGE_PUMP_REGULATOR(LL_SSD1306_CHARGE_PUMP_ENABLED),
};

static uint8_t set_page_cmd_buffer[] = {
	LL_SSD1306_CMD_SET_ADDRESSING_MODE(LL_SSD1306_ADDRESSING_MODE_PAGE),
	LL_SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(0),
	LL_SSD1306_CMD_SET_LOW_PAM_START_ADDRESS(0),
	LL_SSD1306_CMD_SET_HIGH_PAM_START_ADDRESS(0)
};

const ll_ssd1306_buffer_t ll_ssd1306_128x64_startup_cmd = {
	.buffer = ll_ssd1306_128x64_startup_sequence_buffer,
	.size = sizeof(ll_ssd1306_128x64_startup_sequence_buffer)
};

const ll_ssd1306_buffer_t ll_ssd1306_128x32_startup_cmd = {
	.buffer = ll_ssd1306_128x32_startup_sequence_buffer,
	.size = sizeof(ll_ssd1306_128x32_startup_sequence_buffer)
};

const ll_ssd1306_buffer_t ll_ssd1306_set_page_and_zero_address_cmd = {
	.buffer = set_page_cmd_buffer,
	.size = sizeof(set_page_cmd_buffer)
};

ll_ssd1306_buffer_t ll_ssd1306_set_page_cmd(uint8_t page) {
	*(set_page_cmd_buffer+2) =
		LL_SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(page);

	return ll_ssd1306_set_page_and_zero_address_cmd;
};
