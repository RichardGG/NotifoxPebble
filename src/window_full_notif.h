#pragma once

#include "pebble.h"
	
Window* full_notif_window; //self


//this will need to be multiple layers (2?)
static ScrollLayer *full_notif_scroll_layer;

TextLayer *title_text_layer;
	
void window_full_notif_load(Window *window) {
	
	//get window layer and bounds
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);
	
	//CREATE scroll layer
	full_notif_scroll_layer = scroll_layer_create(bounds);
	
	//CREATE test text layer
	title_text_layer = text_layer_create(GRect(0, 0, bounds.size.w, 500));
    text_layer_set_text(title_text_layer, 
						"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus elementum laoreet diam, ultricies convallis nibh sagittis et. Pellentesque ex velit, condimentum sit amet felis in, lobortis rutrum lectus. Nullam dictum sit amet urna ut dictum. Vivamus vulputate purus non odio tincidunt tempus. Nullam at arcu maximus, semper purus non, dapibus dui. Curabitur sed massa sodales, posuere neque nec, euismod nibh. Nunc convallis suscipit felis, a aliquam nibh. Quisque ullamcorper risus ac velit ultrices, venenatis pulvinar est porta. Praesent vel mattis nunc. Integer pellentesque risus eu quam aliquet molestie. Donec dictum massa eget felis sodales, mattis vehicula quam pellentesque. Nullam suscipit ornare elit sed tristique. Cras id velit justo. Vestibulum accumsan purus vel elit mattis ultrices. Pellentesque congue, turpis non blandit rutrum, dolor mi sodales elit, id dapibus lorem ex ut ante. Mauris aliquam dui vitae metus lobortis aliquam."
						);
	//add text layer to scroll layer and set size
    scroll_layer_add_child(full_notif_scroll_layer, text_layer_get_layer(title_text_layer));
	scroll_layer_set_content_size(full_notif_scroll_layer, text_layer_get_content_size(title_text_layer));
	
	//allow scroll layer to control buttons
	scroll_layer_set_click_config_onto_window(full_notif_scroll_layer, window);
	
	//add scroll layer to window
	layer_add_child(window_layer, scroll_layer_get_layer(full_notif_scroll_layer));
}

void window_full_notif_unload(Window *window) {
	//DESTROY scroll layer
	scroll_layer_destroy(full_notif_scroll_layer);
	//DESTROY text layer
	text_layer_destroy(title_text_layer);
	
	//DESTROY self
	window_destroy(full_notif_window);
}