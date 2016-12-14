#include <pebble.h>
#include "storage.h"


void load_datas (void) {
  custom_run = persist_exists(KEY_CUSTOM_RUN) ? persist_read_int(KEY_CUSTOM_RUN) : 60;
  custom_walk = persist_exists(KEY_CUSTOM_WALK) ? persist_read_int(KEY_CUSTOM_WALK) : 60;
  custom_repeat = persist_exists(KEY_CUSTOM_REPEAT) ? persist_read_int(KEY_CUSTOM_REPEAT) : 10;
}
void save_datas (void) {
  persist_write_int (KEY_CUSTOM_RUN, custom_run);  
  persist_write_int (KEY_CUSTOM_WALK, custom_walk);  
  persist_write_int (KEY_CUSTOM_REPEAT, custom_repeat);  
}
  