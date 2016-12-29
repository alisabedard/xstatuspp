// Copyright 2016, Jeffrey E. Bedard
#include "xstatus.h"
extern "C" {
#include "libjb/log.h"
#include "libjb/util.h"
#include "libjb/xcb.h"
}
#include <string>
#include "battery.h"
#include "clock.h"
#include "config.h"
#include "font.h"
#include "load.h"
#include "status_file.h"
#include "temperature.h"
#include "toolbar.h"
#include "util.h"
#include "window.h"
#include "xdata.h"
using namespace xstatus;
using namespace std;
void XStatus::setup_invert_gc(void)
{
	const uint32_t v = XCB_GX_INVERT;
	xcb_create_gc(xc, invert_gc, main_window, XCB_GC_FUNCTION, &v);
}
uint16_t XStatus::poll(void)
{
	const JBDim fsz = font->get_size();
	uint16_t offset = widget_start + XSTATUS_CONST_PAD;
	offset = load::draw(xc, offset, fsz);
	offset = temperature::draw(xc, offset, fsz);
	offset = status_file::draw(xc, offset, opt.filename, fsz);
	return offset;
}
// returns if update needed
bool XStatus::handle_events(xcb_generic_event_t * e)
{
	bool keep_going = true;
	switch (e->response_type) {
	case XCB_ENTER_NOTIFY:
	case XCB_LEAVE_NOTIFY:
		tb->focus(((xcb_enter_notify_event_t*)e)->event);
		break;
	case XCB_EXPOSE:
		if (!tb->expose(((xcb_expose_event_t*)e)->window))
			update();
		break;
	case XCB_BUTTON_PRESS:
		tb->button(((xcb_button_press_event_t *)e)->event,
			keep_going);
		break;
	default:
		LOG("event: %d", e->response_type);
	}
	free(e);
	return keep_going;
}
void XStatus::update(void)
{
	const Font f = *font;
	battery::draw(xc, f, poll(), clock::draw(xc, f));
}
XStatus::XStatus(XStatusOptions opt)
	: XData(jb_get_xcb_connection(NULL, NULL)), opt(opt)
{
	LOG("XStatus constructor");
	xcb_window_t w = Window::create_main_window(this);
	font = new Font(xc);
	jb_require(font->open(XSTATUS_FONT), "Could not load a font");
	const Font f = *font;
	create_gc(xc, gc, w, XSTATUS_PANEL_FOREGROUND,
		XSTATUS_PANEL_BACKGROUND, f);
	create_gc(xc, button_gc, w, XSTATUS_BUTTON_FG,
		XSTATUS_BUTTON_BG, f);
	setup_invert_gc();
	tb = new Toolbar(xc, font);
	widget_start = tb->get_offset();
}
XStatus::~XStatus(void)
{
	LOG("XStatus destructor");
	delete tb;
	delete font;
	xcb_destroy_window(xc, main_window);
	xcb_disconnect(xc);
}
void XStatus::run(void)
{
	LOG("XStatus::run()");
	bool keep_going =  true;
	while (keep_going) {
		xcb_generic_event_t * e;
		if (jb_next_event_timed(xc, &e, opt.get_delay() * 1000000) && e)
			keep_going = handle_events(e);
		else
			update();
	}
}
XStatusOptions::XStatusOptions(char * filename)
{
	LOG("XStatusOptions constructor");
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
XStatusOptions::XStatusOptions(const XStatusOptions& obj)
{
	LOG("XStatusOptions copy constructor");
	string s(obj.filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
XStatusOptions::~XStatusOptions(void)
{
	LOG("XStatusOptions destructor");
	delete filename;
}
void XStatusOptions::set_filename(char * filename)
{
	delete this->filename;
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
