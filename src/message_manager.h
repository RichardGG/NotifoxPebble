#pragma once

#include <pebble.h>
#include <notif_data.h>

//incoming message types
enum {
	IDS,				//count, position, nID, nID, nID, nID
	NOTIFICATION,		//nID, vibrate, title, text
	ICON_DATA,			//nID, section, bits
	IMAGE_DATA,			//nID, total, section, png
	
	ACTIONS,			//nID?, title, title, title, page, page, page
	ACTION_ICON_DATA,	//nID?, aID, section, bits
	PAGE_DATA,			//nID?, pID?, text?
};

//outgoing message types
enum{
	REQUEST_ACTIVE, 		//position
	REQUEST_PAGE,			//nID, pID
	DISMISS_NOTIFICATION, 	//nID
	TAKE_ACTION				//nID, aID
};

int bytes_to_int(uint8_t* pointer){
	return ((int)pointer[0]<<3*8) + ((int)pointer[1]<<2*8) + ((int)pointer[2]<<8) + ((int)pointer[3]);
}

void in_received_handler(DictionaryIterator *iter, void *context) {
	
	//Parse message
	
	Tuple *tuple = dict_find(iter, 0);
	uint8_t* message_data = tuple->value->data;
	
	uint8_t metadata = message_data[0];
	
	total_notifications = message_data[1];
	
	for(int i=0; i<4; i++) {
		ids[i] = bytes_to_int(&(message_data[i*4+3]));
	}
	
	update_callback();
	
	
	/*
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
	}*/
	
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

void request_ids(int pos)
{
	//send a message
	DictionaryIterator *iter;
 	app_message_outbox_begin(&iter);
	Tuplet value = TupletInteger(0, REQUEST_ACTIVE);
	dict_write_tuplet(iter, &value);
	Tuplet value2 = TupletInteger(1,pos);
	dict_write_tuplet(iter, &value2);
	app_message_outbox_send();
}


void setup_app_message()
{
	//callbacks
	app_message_register_inbox_received(in_received_handler);
	app_message_register_inbox_dropped(in_dropped_handler);
	app_message_register_outbox_sent(out_sent_handler);
	app_message_register_outbox_failed(out_failed_handler);

	//set size
	const uint32_t inbound_size = app_message_inbox_size_maximum();
	const uint32_t outbound_size = 32;
	
	APP_LOG(APP_LOG_LEVEL_INFO, "inbox size: %lu", inbound_size);
	
	app_message_open(inbound_size, outbound_size);
	
	//fix this, based on time
	app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	
	
	//initial request (SHOULDN'T BE CALLED ON NEW NOTIFICATION)
	request_ids(0);
	
}