// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BUTTON_H
#define XSTATUS_BUTTON_H
#include <string>
#include <xcb/xcb.h>
#include "font.h"
#include "libjb/JBDim.h"
#include "window.h"
#include "xdata.h"
namespace xstatus {
	class XSButton : public Window {
		private:
			XData & X;
			int16_t x;
			JBDim font_size;
			std::string * label;
			void set_geometry(void);
			void create_window(void);
		public:
			XSButton(XData & X, const Font & f,
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
