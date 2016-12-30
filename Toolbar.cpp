// Copyright 2017, Jeffrey E. Bedard
#include "Toolbar.h"
#include <iostream>
#include "config.h"
#include "libjb/cpp.h"
using namespace std;
using namespace xstatus;
int Toolbar::instances = 0;
namespace {
	bool system_cb(XSButton * b)
	{
		const char *cmd = b->cb_data;
		if (system(cmd))
			cerr << "Cannot execute " << cmd << '\n';
		return true;
	}
	bool exit_cb(XSButton * b)
	{
		return false;
	}
}
void Toolbar::btn(const char label[], const char cb_data[],
	bool (*cb)(XSButton *))
{
	string s(label);
	XSButton * b = new XSButton(*this, *font, offset, s);
	b->cb = cb;
	size_t sz = 0;
	if (cb_data) {
		while (cb_data[++sz]);
		b->cb_data = new char[sz];
		for (int i = sz; i >= 0; --i)
			b->cb_data[i] = cb_data[i];
	}
	offset += b->get_geometry().width + XSTATUS_CONST_PAD;
	buttons.push_front(b);
}
void Toolbar::btn(const char label[], const char cmd[])
{
	btn(label, cmd, system_cb);
}
bool Toolbar::do_cb(const xcb_window_t ewin, bool & keep_going)
{
	for(list<XSButton *>::iterator i = buttons.begin();
		i != buttons.end(); ++i) {
		if ((*i)->get_window() == ewin) {
			keep_going = (*i)->cb(*i);
			return true;
		}
	}
	return false;
}
bool Toolbar::iterate_buttons_member(const xcb_window_t ewin,
	void (XSButton::*func)(void))
{
	for(list<XSButton *>::iterator i = buttons.begin(); i != buttons.end();
		++i) {
		if ((*i)->get_window() == ewin) {
			((*i)->*func)();
			return true;
		}
	}
	return false;
}
bool Toolbar::expose(const xcb_window_t event_window)
{
	return iterate_buttons_member(event_window,
		&XSButton::draw);
}
bool Toolbar::button(const xcb_window_t event_window,
	bool & keep_going)
{
	return do_cb(event_window, keep_going);
}
bool Toolbar::focus(const xcb_window_t event_window)
{
	return iterate_buttons_member(event_window,
		&XSButton::invert);
}
Toolbar::Toolbar(xcb_connection_t * xc, Font * f)
	: XData(xc), offset(0), font(f)
{
	JB_LOG_ADD(Toolbar, instances);
	btn("Menu", XSTATUS_MENU_COMMAND);
	btn("Terminal", XSTATUS_TERMINAL);
	btn("Editor", XSTATUS_EDITOR_COMMAND);
	btn("WWW", XSTATUS_BROWSER_COMMAND);
	btn("Mixer", XSTATUS_MIXER_COMMAND);
	btn("Lock", XSTATUS_LOCK_COMMAND);
	btn("Exit", NULL, exit_cb);
}
Toolbar::~Toolbar(void)
{
	JB_LOG_DEL(Toolbar, instances);
	for (list<XSButton *>::iterator i = buttons.begin(); i !=
		buttons.end(); ++i) {
		delete *i;
	}
}
