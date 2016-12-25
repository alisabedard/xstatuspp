extern "C" {
#include "xdata.h"
#include "libjb/xcb.h"
}
namespace xstatus {
	xcb_screen_t * get_screen(xcb_connection_t * xc)
	{
		static xcb_screen_t * s;
		return s ? s : (s = jb_get_xcb_screen(xc));
	}
	xcb_colormap_t get_colormap(xcb_connection_t * xc)
	{
		static xcb_colormap_t c;
		return c ? c : (c = get_screen(xc)->default_colormap);
	}
	xcb_gcontext_t get_gc(xcb_connection_t * xc)
	{
		static xcb_gcontext_t g;
		return g ? g : (g = xcb_generate_id(xc));
	}
	xcb_gcontext_t get_button_gc(xcb_connection_t * xc)
	{
		static xcb_gcontext_t g;
		return g ? g : (g = xcb_generate_id(xc));
	}
	xcb_gcontext_t get_invert_gc(xcb_connection_t * xc)
	{
		static xcb_gcontext_t g;
		return g ? g : (g = xcb_generate_id(xc));
	}
	xcb_window_t get_window(xcb_connection_t *  xc)
	{
		static xcb_window_t w;
		return w ? w : (w = xcb_generate_id(xc));
	}
}
