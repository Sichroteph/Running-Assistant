#include <pebble.h>
#include "custom.h"
#include "exercice_window.h"
#include "storage.h"

void custom_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  
  uint8_t increment=0;
  
  switch (field) {
    case 1:
      if (custom_run < 1200) {
      increment = 10;
      custom_run += increment;  
      }
      
    break;  
    case 2:
      if (custom_walk < 1200) {
      increment = 10;
      custom_walk += increment;  
      }
      
    break;
    case 3:
      if (custom_repeat < 21) {
        custom_repeat++;
  
      }
    
    break;
    default:
    break;
  
  }
  
  APP_LOG (APP_LOG_LEVEL_INFO, "Increment : %u", increment);  
  custom_update_view ();
  
}

void custom_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG (APP_LOG_LEVEL_INFO,"Select button pressed !"); 
  field++;
  if (field > max_fields) {
    field = 1;
  }
  custom_update_view();
  
}

void custom_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  uint8_t increment=0;
  
  switch (field) {
    case 1:
      if (custom_run > 0) {
        increment = 10;
        custom_run -= increment;
      }
      break;  
    case 2:
      if (custom_walk > 0) {
        increment = 10;
        custom_walk -= increment;
      }
      break;
    case 3:
      if (custom_repeat > 0){
        custom_repeat--;
      }
    break;
    default:
    break;
  
  }
  APP_LOG (APP_LOG_LEVEL_INFO, "Increment : %u", increment);
  custom_update_view ();
  
}

void custom_launch_workout (ClickRecognizerRef recognizer, void *context) {
  
  start_workout(0);
  
}

void custom_click_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, custom_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, custom_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, custom_down_click_handler);
  
  window_long_click_subscribe (BUTTON_ID_SELECT, 500, custom_launch_workout, NULL );
  
  APP_LOG (APP_LOG_LEVEL_INFO,"Done registering handlers");
}


void custom_update_view () {
  
  uint8_t custom_run_min, custom_run_sec, custom_walk_min, custom_walk_sec;

  switch (field) {
    case 1:
      text_layer_set_background_color (s_repeat, GColorWhite);
      text_layer_set_background_color (s_run_min, GColorPictonBlue);
      text_layer_set_text (s_label,label_run);
    break;
    case 2:
      text_layer_set_background_color (s_run_min, GColorWhite);
      text_layer_set_background_color (s_walk_min, GColorPictonBlue);
      text_layer_set_text (s_label,label_walk);
    break;
    case 3:
      text_layer_set_background_color (s_walk_min, GColorWhite);
      text_layer_set_background_color (s_repeat, GColorPictonBlue);  
      text_layer_set_text (s_label,label_repeat);
    break;
    default:
      APP_LOG (APP_LOG_LEVEL_INFO, "Field %u unknow", field);
    break;
  }
  
  // Displaying the data taken from permanent storage
  
  custom_run_min = custom_run / 60;
  custom_run_sec = custom_run % 60;
  APP_LOG (APP_LOG_LEVEL_INFO, "Custom run : %u, Min : %u, Seconds : %u", custom_run, custom_run_min, custom_run_sec);
  
  snprintf (buffer_run, sizeof(buffer_run), "%02u:%02u", custom_run_min, custom_run_sec);
    
  text_layer_set_text(s_run_min, buffer_run);
  
  custom_walk_min = custom_walk / 60;
  custom_walk_sec = custom_walk % 60;
  
  snprintf (buffer_walk, sizeof(buffer_walk), "%02u:%02u", custom_walk_min, custom_walk_sec);
  
  text_layer_set_text(s_walk_min, buffer_walk);
  
  snprintf (buffer_repeat, sizeof(buffer_repeat), "%u", custom_repeat);
  
  text_layer_set_text(s_repeat, buffer_repeat);
  
  APP_LOG (APP_LOG_LEVEL_INFO, "Done init buttons");
  
}

void custom_window_load (Window *window) {
  
  Layer *window_layer = window_get_root_layer (window);
  GRect bounds = layer_get_bounds(window_layer);
  
  uint8_t custom_run_min, custom_run_sec, custom_walk_min, custom_walk_sec;

  s_label  = text_layer_create(GRect(0,130,bounds.size.w, 25));
  s_run_min       = text_layer_create(GRect(bounds.size.w/4,15,bounds.size.w/2,32));
  s_walk_min      = text_layer_create(GRect(bounds.size.w/4,50,bounds.size.w/2,32));
  s_repeat        = text_layer_create(GRect(bounds.size.w/4,90,bounds.size.w/2,32));
  
  
  text_layer_set_text(s_label, "Walking time");

  APP_LOG (APP_LOG_LEVEL_INFO, "Done init text layers");
  
  // Displaying the data taken from permanent storage
  
  custom_run_min = custom_run / 60;
  custom_run_sec = custom_run % 60;
  APP_LOG (APP_LOG_LEVEL_INFO, "Custom run : %u, Min : %u, Seconds : %u", custom_run, custom_run_min, custom_run_sec);
  
  snprintf (buffer_run, sizeof(buffer_run), "%02u:%02u", custom_run_min, custom_run_sec);
    
  text_layer_set_text(s_run_min, buffer_run);
  
  custom_walk_min = custom_walk / 60;
  custom_walk_sec = custom_walk % 60;
  
  snprintf (buffer_walk, sizeof(buffer_walk), "%02u:%02u", custom_walk_min, custom_walk_sec);
  
  text_layer_set_text(s_walk_min, buffer_walk);
  
  snprintf (buffer_repeat, sizeof(buffer_repeat), "%u", custom_repeat);
  
  text_layer_set_text(s_repeat, buffer_repeat);
  
  APP_LOG (APP_LOG_LEVEL_INFO, "Done init buttons");
  
  text_layer_set_text_alignment(s_label, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_run_min, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_walk_min, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_repeat, GTextAlignmentCenter);

  APP_LOG (APP_LOG_LEVEL_INFO, "Done text alignments");
  
  text_layer_set_font(s_run_min, fonts_get_system_font(FONT_KEY_GOTHIC_28));
   text_layer_set_font(s_walk_min, fonts_get_system_font(FONT_KEY_GOTHIC_28)); 
  text_layer_set_font(s_repeat, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_label));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_run_min));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_walk_min));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_repeat));
  
  field = 1;
  
  custom_update_view ();
  
}

void custom_window_unload () {
  text_layer_destroy(s_label);
  text_layer_destroy(s_run_min);
  text_layer_destroy(s_walk_min);
  text_layer_destroy(s_repeat);
  
  window_destroy(s_custom_window);
  
}

void custom_window_init () {
  APP_LOG(APP_LOG_LEVEL_INFO,"Custom workout");
  s_custom_window = window_create();
  
  WindowHandlers handlers = {
      .load = custom_window_load,
      .unload = custom_window_unload
  };
  
  window_set_window_handlers(s_custom_window, (WindowHandlers) handlers);
  window_set_click_config_provider(s_custom_window, custom_click_provider);
  
  window_stack_push(s_custom_window, true);  
  
}

void start_custom (void) {
  
  custom_window_init ();
  
}
