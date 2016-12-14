#include <pebble.h>
#include "exercice_window.h"
#include "storage.h"
#include "custom.h"

void init_workouts () {

  All[0].run = custom_run;
  All[0].walk = custom_walk;
  All[0].repeat = custom_repeat;

  All[1].run = 120;
  All[1].walk = 60;
  All[1].repeat = 10;
  All[2].run = 180;
  All[2].walk = 60;
  All[2].repeat = 10;
  All[3].run = 300;
  All[3].walk = 120;
  All[3].repeat = 10;
  All[4].run = 600;
  All[4].walk = 180;
  All[4].repeat = 10;
  All[5].run = 900;
  All[5].walk = 300;
  All[5].repeat = 3;


}

static void workout_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG (APP_LOG_LEVEL_INFO, "UP button pressed");
}

static void workout_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (is_counting) {
    tick_timer_service_unsubscribe();
    is_counting = false;

  } else {
    tick_timer_service_subscribe (SECOND_UNIT, &do_workout);
    is_counting = true;


  }
}

static void workout_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG (APP_LOG_LEVEL_INFO,"Down button pressed !") ;
}

static void workout_click_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, workout_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, workout_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, workout_down_click_handler);
  APP_LOG (APP_LOG_LEVEL_INFO,"Done registering handlers");
}

void update_screen (Layer *me, GContext *ctx) {

  uint8_t i;

  uint16_t total; 
  uint32_t start_angle_run, stop_angle_run, start_angle_walk; 

  GRect bounds = layer_get_bounds (me);
  total = time_run + time_walk;

  start_angle_run = 360*(time_run-seconds_to_go)/total;
  stop_angle_run = 360*time_run/total;
  if (is_running) {
    start_angle_walk = 360*time_run/total;
  } else {
    start_angle_walk = 360*(total-seconds_to_go)/total;
  }

  ;

  graphics_context_set_antialiased(ctx, true);

  if (is_running) {
#ifdef PBL_COLOR 
    graphics_context_set_fill_color (ctx,GColorGreen);
#else
    graphics_context_set_fill_color (ctx,GColorWhite);

    #endif
    GRect frame = grect_inset(bounds, GEdgeInsets(26));
    graphics_fill_radial(ctx, frame, GOvalScaleModeFitCircle, 65,
                         DEG_TO_TRIGANGLE(start_angle_run), DEG_TO_TRIGANGLE(stop_angle_run));

  }
#ifdef PBL_COLOR 
    graphics_context_set_fill_color (ctx,GColorOrange);
#else
    graphics_context_set_fill_color (ctx,GColorWhite);

    #endif
  GRect frame = grect_inset(bounds, GEdgeInsets(26));
  graphics_fill_radial(ctx, frame, GOvalScaleModeFitCircle, 65,
                       DEG_TO_TRIGANGLE(start_angle_walk), DEG_TO_TRIGANGLE(360));

  graphics_context_set_fill_color (ctx,GColorBlack);


  for (i=1; i<=All[number].repeat; i++) {

    uint16_t start_angle, stop_angle;

    start_angle = 360*i/All[number].repeat - 360/All[number].repeat;
    stop_angle = 360*i/All[number].repeat-5;
    if (i < current_cycle) {
      graphics_context_set_fill_color (ctx, GColorBlack);
    } else if (i == current_cycle) {
      graphics_context_set_fill_color (ctx, GColorRed);
    } else {
      graphics_context_set_fill_color (ctx,GColorLightGray);
    }

    GRect frame = grect_inset(bounds, GEdgeInsets(0));
    graphics_fill_radial(ctx, frame, GOvalScaleModeFitCircle, 20,
                         DEG_TO_TRIGANGLE(start_angle), DEG_TO_TRIGANGLE(stop_angle));

  }

  graphics_context_set_text_color(ctx, GColorBlack);
  
#ifdef PBL_COLOR 
  
#else
   if (is_running) {
      graphics_draw_text(ctx, "W",  fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), 
                     GRect((bounds.size.w-100)/2-1, bounds.size.h/2-58, 100, 63), 
                     GTextOverflowModeWordWrap,
                     GTextAlignmentCenter, NULL);
      } else {
          graphics_draw_text(ctx, "R",  fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), 
                     GRect((bounds.size.w-100)/2-1, bounds.size.h/2-58, 100, 63), 
                     GTextOverflowModeWordWrap,
                     GTextAlignmentCenter, NULL);
      } 
     
     
     
#endif  
  
  
  graphics_draw_text(ctx, buffer,  fonts_get_system_font(FONT_KEY_LECO_32_BOLD_NUMBERS), 
                     GRect((bounds.size.w-100)/2, bounds.size.h/2-35, 100, 60), 
                     GTextOverflowModeWordWrap,
                     GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, cycle,  fonts_get_system_font(FONT_KEY_LECO_32_BOLD_NUMBERS), 
                     GRect((bounds.size.w-100)/2,bounds.size.h/2,100,60), 
                     GTextOverflowModeWordWrap,
                     GTextAlignmentCenter, NULL);

}

void start_workout (uint8_t which) {

  number = which;

  workout_window_init ();  


}

void do_workout (struct tm *tick_time, TimeUnits units_changed) {

  if (seconds_to_go>0) {

    minutes = seconds_to_go / 60;
    seconds = seconds_to_go % 60;
    snprintf (buffer,sizeof(buffer), "%u:%02u", minutes,seconds);

    snprintf (cycle,sizeof(cycle),"%u/%u", current_cycle,All[number].repeat);

    seconds_to_go--;

  } else {

    // Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:
    static const uint32_t const segments[] = { 200, 100, 200,100,200, 100, 200,100,1000 };
    VibePattern pat = {
      .durations = segments,
      .num_segments = ARRAY_LENGTH(segments),
    };
    vibes_enqueue_custom_pattern(pat);
    switch (is_running) {
      case 0:

      is_running = 1;
      seconds_to_go = All[number].run;
      current_cycle++;
      break;
      case 1:

      is_running = 0;
      seconds_to_go = All[number].walk;
      break;

    }
  }
  layer_mark_dirty (s_funky_layer);
}

void workout_window_load (Window *window) {

  Layer *window_layer = window_get_root_layer (window);
  GRect bounds = layer_get_bounds(window_layer);
  s_funky_layer = layer_create (bounds);

  layer_set_update_proc (s_funky_layer,update_screen);

  window_set_background_color(s_workout_window, GColorWhite);


  layer_add_child(window_get_root_layer(s_workout_window), s_funky_layer); 
  layer_add_child(window_get_root_layer(s_workout_window), s_funky_layer); 

  init_workouts () ;

  seconds_to_go = All[number].run;
  is_running = 1;
  current_cycle = 1;

  time_run = All[number].run;
  time_walk = All[number].walk;

  minutes = seconds_to_go / 60;
  seconds = seconds_to_go % 60;

  is_counting = 1;




  tick_timer_service_subscribe (SECOND_UNIT, &do_workout);

}

void workout_window_unload () {

  tick_timer_service_unsubscribe ();  

  layer_destroy (s_funky_layer);

  window_destroy(s_workout_window);

}

void workout_window_init () {

  s_workout_window = window_create();
  WindowHandlers handlers = {
    .load = workout_window_load,
    .unload = workout_window_unload
  };

  window_set_window_handlers(s_workout_window, (WindowHandlers) handlers);
  window_set_click_config_provider(s_workout_window, workout_click_provider);

  window_stack_push(s_workout_window, true);  

}