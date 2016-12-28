// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BUTTON_H
#define XSTATUS_BUTTON_H
#include <string>
#include <xcb/xcb.h>
#include "font.h"
#include "libjb/JBDim.h"
#include "xdata.h"
namespace xstatus {
	class XSButton : public XData {
		private:
			int16_t x;
			JBDim font_size;
			std::string * label;
			xcb_window_t window;
			xcb_rectangle_t geometry;
			void set_geometry(void);
			void create_window(void);
		public:
			XSButton(xcb_connection_t * xc, const Font & f,
				const int16_t x, char * label);
			~XSButton(void);
			xcb_window_t get_window(void){return window;}
			xcb_rectangle_t get_geometry(void){return geometry;}
			void draw(void);
			void invert(void);
			bool (*cb)(XSButton *);
			char * cb_data;
	};
}
#endif//XSTATUS_BUTTON_H
