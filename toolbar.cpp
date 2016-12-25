// Copyright 2016, Jeffrey E. Bedard
extern "C" {
#include "toolbar.h"
}
#include <cstdlib>
#include <string>
#include "button.h"
#include "config.h"
#include "libjb/log.h"
using namespace std;
static XSButton * xstatus_head_button;
static XSButton * get_last_button_r(XSButton * i)
{
	return i->next ? get_last_button_r(i->next) : i;
}
static XSButton * get_last_button(void)
{
	return xstatus_head_button ? get_last_button_r(xstatus_head_button)
		: NULL;
}
static void system_cb(XSButton * b)
{
	const char *cmd = b->cb_data;
	if (system(cmd))
		LIBJB_WARN("Cannot execute %s", cmd);
}
static uint16_t btn(xcb_connection_t * xc, const int16_t offset,
	char *  label, char *  cmd)
{
	XSButton * i = get_last_button();
	XSButton * b = new XSButton(xc, offset, label);
	b->cb = system_cb;
	b->cb_data = cmd;
	*(i ? &i->next : &xstatus_head_button) = b;
	return offset + b->get_geometry().width + XSTATUS_CONST_PAD;
}
/* Returns x offset after all buttons added.  */
uint16_t xstatus_initialize_toolbar(xcb_connection_t * xc)
{
	uint16_t off = 0;
	static char menu[] = "Menu", menu_cmd[] = XSTATUS_MENU_COMMAND;
	off = btn(xc, off, menu, menu_cmd);
	static char term[] = "Terminal", term_cmd[] = XSTATUS_TERMINAL;
	off = btn(xc, off, term, term_cmd);
	static char edit[] = "Editor", edit_cmd[] = XSTATUS_EDITOR_COMMAND;
	off = btn(xc, off, edit, edit_cmd);
	{ // * browser scope
		static char www_env[] = "XSTATUS_BROWSER_COMMAND",
			    www[] = "Browser",
			    default_www_cmd[] = XSTATUS_BROWSER_COMMAND;
		char * browser=getenv(www_env);
		if (!browser)
			browser = default_www_cmd;
		off = btn(xc, off, www, browser);
	}
	static char mix[] = "Mixer", mix_cmd[] = XSTATUS_MIXER_COMMAND;
	off = btn(xc, off, mix, mix_cmd);
	static char lock[] = "Lock", lock_cmd[] = XSTATUS_LOCK_COMMAND;
	off = btn(xc, off, lock, lock_cmd);
	return off;
}
static XSButton * find_button_r(const xcb_window_t w,
	XSButton * i)
{
	return i ? i->get_window() == w ? i : find_button_r(w, i->next) : NULL;
}
static bool iterate_buttons(const xcb_window_t ewin,
	void (*func)(XSButton * ))
{
	XSButton * b = find_button_r(ewin, xstatus_head_button);
	if (b) {
		func(b);
		return true;
	}
	return false;
}
bool xstatus_toolbar_handle_expose(const xcb_window_t event_window)
{
	return iterate_buttons(event_window, xstatus_head_button->draw);
}
bool xstatus_toolbar_handle_button_press(const xcb_window_t event_window)
{
	return iterate_buttons(event_window, xstatus_head_button->cb);
}
bool xstatus_toolbar_handle_button_enter(const xcb_window_t event_window)
{
	return iterate_buttons(event_window, xstatus_head_button->enter);
}
bool xstatus_toolbar_handle_button_leave(const xcb_window_t event_window)
{
	return iterate_buttons(event_window, xstatus_head_button->leave);
}
