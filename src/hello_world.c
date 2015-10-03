#include <pebble.h>

Window *window;
TextLayer *text_layer;

static void data_handler(AccelData *data, uint32_t num_samples) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Entered data_handler()");  
  static char s_buffer[128];
  snprintf(s_buffer, sizeof(s_buffer),
          "N X,Y,Z\n0 %d,%d,%d\n1 %d,%d,%d\n2 %d,%d,%d",
          data[0].x, data[0].y, data[0].z,
          data[1].x, data[1].y, data[1].z,
          data[2].x, data[2].y, data[2].z);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", s_buffer);
}

void handle_init(void) {
  uint32_t num_samples = 3;
  accel_data_service_subscribe(num_samples, data_handler);
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
  accel_data_service_unsubscribe();
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
