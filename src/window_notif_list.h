#pragma once
#include "pebble.h"
#include "notif_data.h"
#include "window_full_notif.h"
	
Window* notif_list_window; //self

static MenuLayer *notif_list_menu_layer;

static int16_t notif_list_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  return 60;
}

static uint16_t notif_list_num_rows(MenuLayer *menu_layer, uint16_t section_index, void *data) {
 return 4;
}

static void notif_list_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	//menu_cell_basic_draw(ctx, cell_layer, title[0], "With a subtitle", &icon[0]);
	graphics_context_set_compositing_mode(ctx, GCompOpAssignInverted);
	graphics_draw_bitmap_in_rect(ctx, &icon[0], GRect(0,6,48,48));
	graphics_context_set_compositing_mode(ctx, GCompOpAssign);
	graphics_context_set_text_color(ctx, GColorBlack);
	
	char test[100];
	
	test[0] = '-';
	test[1] = '\0';
	
	snprintf(test, 100, "%d: %d, %d, %d, %d", total_notifications, ids[0], ids[1], ids[2], ids[3]);
	
	graphics_draw_text(ctx, test, fonts_get_system_font(FONT_KEY_GOTHIC_18), GRect(48,0,96,16), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
	
	//graphics_draw_text(ctx, "title", fonts_get_system_font(FONT_KEY_GOTHIC_18), GRect(48,0,96,16), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
	//graphics_draw_text(ctx, "text", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(48,18,96,48), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
}

void notif_list_select(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	
	//CREATE window
	full_notif_window = window_create();

  // Setup the window handlers
  window_set_window_handlers(full_notif_window, (WindowHandlers) {
    .load = window_full_notif_load,
    .unload = window_full_notif_unload,
  });

  window_stack_push(full_notif_window, true /* Animated */);
}
	
void window_notif_list_load(Window *window) {
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);
	
	//CREATE menu layer
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
	//DESTROY menu layer
	menu_layer_destroy(notif_list_menu_layer);
	
	//DESTROY self
	window_destroy(notif_list_window);
}