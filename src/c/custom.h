#pragma once


static Window *s_custom_window;

static uint8_t field;
static uint8_t max_fields = 3;

static TextLayer *s_label;
static TextLayer *s_run_min;
static TextLayer *s_walk_min;
static TextLayer *s_repeat;
static TextLayer *s_start_button;
char buffer_run[6];
char buffer_walk[6];
char buffer_repeat[6];

static char label_run [] = "Walking time";
static char label_walk [] = "Running time";
static char label_repeat [] = "number of repetitions";

void custom_up_click_handler(ClickRecognizerRef, void *) ;
void custom_select_click_handler(ClickRecognizerRef, void *) ;
void custom_down_click_handler(ClickRecognizerRef, void *);
void custom_click_provider(void *);
void custom_update_view (void);
void custom_window_load ();
void custom_window_unload ();
void custom_window_init ();
void start_custom (void); 
void custom_launch_workout (ClickRecognizerRef , void *);