// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_BUTTON_H
#define XSTATUS_BUTTON_H
#include <xcb/xcb.h>
class XSButton {
	public:
		XSButton * next;
		void (*cb)(XSButton *);
		void (*draw) (XSButton *);
		void (*enter) (XSButton *);
		void (*leave) (XSButton *);
		char * cb_data;
		char * label;
		xcb_connection_t * xc;
		xcb_window_t window;
		int16_t x;
		uint16_t width;
};
XSButton * xstatus_create_button(xcb_connection_t *  xc,
	const int16_t x, char * label);
#endif//XSTATUS_BUTTON_H
