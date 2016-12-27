// Copyright 2016, Jeffrey E. Bedard
#include "toolbar.h"
extern "C" {
#include "libjb/log.h"
}
#include <cstdlib>
#include <list>
#include "button.h"
#include "config.h"
using namespace std;
using namespace xstatus;
#if 0
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
#endif
static bool system_cb(XSButton * b)
{
	const char *cmd = b->cb_data;
	if (system(cmd))
		LIBJB_WARN("Cannot execute %s", cmd);
	return true;
}
void xstatus::Toolbar::btn(char * label, char * cb_data,
	bool (*cb)(XSButton *))
{
	XSButton * b = new XSButton(xc, offset, label);
	b->cb = cb;
	b->cb_data = cb_data;
	offset += b->get_geometry().width + XSTATUS_CONST_PAD;
	buttons.push_front(b);
}
void xstatus::Toolbar::btn(char * label, char * cmd)
{
	btn(label, cmd, system_cb);
}
static bool exit_cb(XSButton * b)
{
	delete b;
	return false;
}
#if 0
static uint16_t exit_btn(xcb_connection_t * xc,
	const int16_t offset)
{
	XSButton * i = get_last_button();
	static char label[] = "Exit";
	XSButton * b = new XSButton(xc, offset, label);
	b->cb = exit_cb;
	b->cb_data = NULL;
	*(i ? &i->next : &xstatus_head_button) = b;
	return offset + b->get_geometry().width +
		XSTATUS_CONST_PAD;
}
#endif
#if 0
static XSButton * find_button_r(const xcb_window_t w, XSButton
	* i)
{
	return i ? i->get_window() == w ? i : find_button_r(w,
		i->next) : NULL;
}
#endif
bool xstatus::Toolbar::do_cb(const xcb_window_t ewin, bool & keep_going)
{
	for(list<XSButton *>::iterator i = buttons.begin();
		i != buttons.end(); ++i) {
		if ((*i)->get_window() == ewin) {
			keep_going = (*i)->cb(*i);
			return true;
		}
	}
	return false;
#if 0

	XSButton * f = buttons.front();
	XSButton * b = find_button_r(ewin, f);
	if (b) {
		keep_going = b->cb(b);
		return true;
	}
	return false;
#endif
}
bool xstatus::Toolbar::iterate_buttons_member(const xcb_window_t ewin,
	void (XSButton::*func)(void))
{
	for(list<XSButton *>::iterator i = buttons.begin(); i != buttons.end();
		++i) {
		if ((*i)->get_window() == ewin) {
			XSButton * b = *i;
			//(i->*func)();
			(b->*func)();
			return true;
		}
	}
	return false;
#if 0
	XSButton * b = find_button_r(ewin, xstatus_head_button);
	if (b) {
		(b->*func)();
		return true;
	}
	return false;
#endif
}
bool xstatus::Toolbar::expose(const xcb_window_t event_window)
{
	return iterate_buttons_member(event_window,
		&XSButton::draw);
}
bool xstatus::Toolbar::button(const xcb_window_t event_window,
	bool & keep_going)
{
	return do_cb(event_window, keep_going);
}
bool xstatus::Toolbar::focus(const xcb_window_t event_window)
{
	return iterate_buttons_member(event_window,
		&XSButton::invert);
}
xstatus::Toolbar::Toolbar(xcb_connection_t * xc)
	: XData(xc), offset(0)
{
	static char menu[] = "Menu",
		  menu_cmd[]= XSTATUS_MENU_COMMAND;
	btn(menu, menu_cmd);
//	offset = btn(xc, offset, menu, menu_cmd);
	static char term[] = "Terminal",
		  term_cmd[] = XSTATUS_TERMINAL;
	btn(term, term_cmd);
//	offset = btn(xc, offset, term, term_cmd);
	static char edit[] = "Editor",
		  edit_cmd[] = XSTATUS_EDITOR_COMMAND;
	btn(edit, edit_cmd);
//	offset = btn(xc, offset, edit, edit_cmd);
	{ // * browser scope
		static char www_env[] = "XSTATUS_BROWSER_COMMAND",
			  www[] = "Browser",
			  default_www_cmd[]
				  = XSTATUS_BROWSER_COMMAND;
		char * browser=getenv(www_env);
		if (!browser)
			browser = default_www_cmd;
//		offset = btn(xc, offset, www, browser);
		btn(www, browser);
	}
	static char mix[] = "Mixer",
		  mix_cmd[] = XSTATUS_MIXER_COMMAND;
//	offset = btn(xc, offset, mix, mix_cmd);
	btn(mix, mix_cmd);
	static char lock[] = "Lock",
		  lock_cmd[] = XSTATUS_LOCK_COMMAND;
//	offset = btn(xc, offset, lock, lock_cmd);
	btn(lock, lock_cmd);
//	offset = exit_btn(xc, offset);
	static char exit_label[] = "Exit";
	btn(exit_label, NULL, exit_cb);
}
