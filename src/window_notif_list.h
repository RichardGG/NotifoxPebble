#pragma once
#include "pebble.h"
#include "window_full_notif.h"

static MenuLayer *notif_list_menu_layer;

static int16_t notif_list_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  return 48;
}

static uint16_t notif_list_num_rows(MenuLayer *menu_layer, uint16_t section_index, void *data) {
 return 4;
}

static void notif_list_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	menu_cell_basic_draw(ctx, cell_layer, "Basic Item", "With a subtitle", NULL);
}

void notif_list_select(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	Window *window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_full_notif_load,
    .unload = window_full_notif_unload,
  });

  window_stack_push(window, true /* Animated */);
}
	
void window_notif_list_load(Window *window) {
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);
	
	notif_list_menu_layer = menu_layer_create(bounds);
	
	menu_layer_set_callbacks(notif_list_menu_layer, NULL, (MenuLayerCallbacks){
		.get_num_rows = notif_list_num_rows,
		.get_cell_height = notif_list_cell_height,
		.draw_row = notif_list_draw_row,
		.select_click = notif_list_select,
	});
	
	//allow menu layer to handle buttons
	menu_layer_set_click_config_onto_window(notif_list_menu_layer, window);
	
	//add it to window
	layer_add_child(window_layer, menu_layer_get_layer(notif_list_menu_layer));
}

void window_notif_list_unload(Window *window) {
	menu_layer_destroy(notif_list_menu_layer);
}