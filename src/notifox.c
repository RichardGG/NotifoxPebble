#include "pebble.h"
#include "window_notif_list.h"
#include "message_manager.h"
#include "notif_data.h"

int main(void) {
	
	create_bitmaps();
	clear_data(0);
	
	notif_list_window = window_create();
	// Setup the window handlers
	window_set_window_handlers(notif_list_window, (WindowHandlers) {
		.load = window_notif_list_load,
		.unload = window_notif_list_unload,
	});
	window_stack_push(notif_list_window, true /* Animated */);
	
	setup_app_message();	

  app_event_loop();
}
