#include <ll_ssd1306.h>
#include <assert.h>
#include <stdio.h>

void assert_page_select_works() {
  ll_ssd1306_buffer_t buf = ll_ssd1306_set_page_cmd(1);
  assert(buf.buffer[2] == LL_SSD1306_CMD_SET_PAM_PAGE_START_ADDRESS(1));
  printf("assert_page_select()");
}

int main() {
  assert_page_select_works();
}
