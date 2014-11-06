#pragma once
#include "pebble.h"
	
static MenuLayer *action_list_menu_layer;

static int16_t action_list_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  return 48;
}

static uint16_t action_list_num_rows(MenuLayer *menu_layer, uint16_t section_index, void *data) {
 return 4;
}

static void action_list_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	menu_cell_basic_draw(ctx, cell_layer, "Basic Item", "With a subtitle", NULL);
}

void action_list_select(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	//any window created here must be destroyed!
}
	
void window_action_list_load(Window *window) {
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);
	
	action_list_menu_layer = menu_layer_create(bounds);
	
	menu_layer_set_callbacks(action_list_menu_layer, NULL, (MenuLayerCallbacks){
		.get_num_rows = action_list_num_rows,
		.get_cell_height = action_list_cell_height,
		.draw_row = action_list_draw_row,
		.select_click = action_list_select,
	});
	
	//allow menu layer to handle buttons
	menu_layer_set_click_config_onto_window(action_list_menu_layer, window);
	
	//add it to window
	layer_add_child(window_layer, menu_layer_get_layer(action_list_menu_layer));
}

void window_action_list_unload(Window *window) {
	menu_layer_destroy(action_list_menu_layer);
}