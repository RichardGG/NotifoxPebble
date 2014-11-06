#include "pebble.h"
#include "window_notif_list.h"

int main(void) {
  Window *window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_notif_list_load,
    .unload = window_notif_list_unload,
  });

	window_stack_push(window, true /* Animated */);

  app_event_loop();

  window_destroy(window);
}
