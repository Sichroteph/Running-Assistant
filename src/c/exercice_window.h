#pragma once

typedef struct  {
  uint16_t run;
  uint16_t walk;
  uint8_t repeat;
} workout; 

static workout      All[6]; 

static Window       *s_workout_window;
static TextLayer    *l_timetogo;
static TextLayer    *l_mode;
static TextLayer    *l_repeat;
static Layer        *s_funky_layer;
static BitmapLayer  *s_icon_layer;

static bool         is_running;
static bool         is_counting;

static uint8_t      number;
static uint8_t      current_cycle;
static uint16_t     seconds_to_go;
static uint16_t     time_run,time_walk;
static uint8_t      minutes, seconds;

static char         buffer[] = "00:00";
static char         cycle[] = "10/10";

GBitmap             *s_icon;

void init_workouts ();
void start_workout (uint8_t);
void update_screen (Layer *, GContext *);
void workout_window_load ();
void workout_window_unload ();
void workout_window_init();
void do_workout(struct tm *, TimeUnits );