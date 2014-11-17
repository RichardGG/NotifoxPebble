#pragma once

#include <pebble.h>
#include <notif_data.h>

void in_received_handler(DictionaryIterator *iter, void *context) {
	
	
	
	//type 
	Tuple *tuple = dict_find(iter, 0);
	int type = tuple->value->int8;
	
	tuple = dict_find(iter, 1);
	
	if(type == 0)
	{
		char* value = tuple->value->cstring;
		strcpy(title[0], value);
	}
	else
	{
		int ICON_MESSAGE_ROWS = 16;
		
		uint8_t* byteArray = tuple->value->data;
		tuple = dict_find(iter, 2);

		int starting_row = tuple->value->int32;

		for(int additional_rows = 0; additional_rows < ICON_MESSAGE_ROWS; additional_rows++)
		{
			for(int i =0; i < 6; i++)
			{
				icon_data[0][i + (64/8)*(starting_row+additional_rows)] = byteArray[i+(48/8)*additional_rows];
			}
		}
	}
	
}

void out_sent_handler(DictionaryIterator *sent, void *context) {
	// outgoing message was delivered
}
void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
	// outgoing message failed
}
void in_dropped_handler(AppMessageResult reason, void *context) {
	// incoming message dropped
}


void setup_app_message()
{
	//callbacks
	app_message_register_inbox_received(in_received_handler);
	app_message_register_inbox_dropped(in_dropped_handler);
	app_message_register_outbox_sent(out_sent_handler);
	app_message_register_outbox_failed(out_failed_handler);

	//set size
	const uint32_t inbound_size = 512;
	const uint32_t outbound_size = 64;
	app_message_open(inbound_size, outbound_size);
	
	//fix this, based on time
	app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	
	//send a message
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
	Tuplet value = TupletInteger(0, 42);
	dict_write_tuplet(iter, &value);
	app_message_outbox_send();
	
}