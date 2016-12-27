// Copyright 2016, Jeffrey E. Bedard
#ifndef XSTATUS_BUTTON_H
#define XSTATUS_BUTTON_H
#include <string>
#include <xcb/xcb.h>
#include "xdata.h"
namespace xstatus {
	class XSButton : public XData {
		private:
			std::string * label;
			xcb_window_t window;
			xcb_rectangle_t geometry;
			int16_t x;
			void set_geometry(void);
			void create_window(void);
		public:
			XSButton(xcb_connection_t * xc,
				const int16_t x, char * label);
			~XSButton(void);
			xcb_window_t get_window(void){return window;}
			xcb_rectangle_t get_geometry(void){return geometry;}
			bool (*cb)(XSButton *);
			void draw(void);
			void invert(void);
			char * cb_data;
	};
	XSButton * xstatus_create_button(xcb_connection_t * xc,
		const int16_t x, char * label);
}
#endif//XSTATUS_BUTTON_H
