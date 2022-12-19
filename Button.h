// Copyright 2017, Alisa Bedard
#ifndef XSTATUS_BUTTON_H
#define XSTATUS_BUTTON_H
#include <string>
#include <xcb/xcb.h>
#include "Font.h"
#include "Window.h"
#include "XData.h"
#include "libjb/JBDim.h"
namespace xstatus {
	class Button : public Window {
		private:
			static short instances;
			static xcb_gcontext_t button_gc;
			XData & X;
			const Font & font;
			short x;
			FontSize font_size;
			std::string label;
			void set_geometry(void);
			void create_window(void);
		public:
			Button(XData & X, const Font & f,
				const short x, std::string & label);
			~Button(void);
			xcb_gcontext_t get_button_gc(void);
			xcb_window_t get_window(void) const
			{ return window; }
			xcb_rectangle_t get_geometry(void) const
			{ return geometry; }
			void draw(void);
			void invert(void);
			bool (*cb)(Button *);
			char * cb_data = NULL;
	};
}
#endif//XSTATUS_BUTTON_H
