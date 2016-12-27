// Copyright 2016, Jeffrey E. Bedard
#include "xstatus.h"
extern "C" {
#include "libjb/log.h"
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
	xcb_create_gc(xc, get_invert_gc(xc),
		win, XCB_GC_FUNCTION, &v);
}
uint16_t XStatus::poll(void)
{
	uint16_t offset = widget_start + XSTATUS_CONST_PAD;
	offset = load::draw(xc, offset);
	offset = temperature::draw(xc, offset);
	offset = status_file::draw(xc, offset, opt.filename);
	return offset;
}
// returns if update needed
bool XStatus::handle_events(xcb_generic_event_t * e)
{
	bool keep_going = true;
	switch (e->response_type) {
	case XCB_ENTER_NOTIFY:
		toolbar::handle_button_enter(
			((xcb_enter_notify_event_t*)e)->event);
		break;
	case XCB_LEAVE_NOTIFY:
		toolbar::handle_button_leave(
			((xcb_leave_notify_event_t*)e)->event);
		break;
	case XCB_EXPOSE:
		if (!toolbar::handle_expose(((xcb_expose_event_t*)e)
			->window))
			update();
		break;
	case XCB_BUTTON_PRESS:
		toolbar::handle_button_press(
			((xcb_button_press_event_t *)e)->event, &keep_going);
		break;
	default:
		LOG("event: %d", e->response_type);
	}
	free(e);
	return keep_going;
}
void XStatus::update(void)
{
	Battery::draw(xc, poll(), clock::draw(xc));
}
XStatus::XStatus(XStatusOptions opt)
	: XData(jb_get_xcb_connection(NULL, NULL)), opt(opt)
{
	xstatus_create_window(xc);
	if (!open_font(xc, XSTATUS_FONT)) // default
		if (!open_font(xc, "fixed")) // fallback
			LIBJB_ERROR("Could not load any font");
	xstatus_create_gc(xc, get_gc(xc), win,
		XSTATUS_PANEL_FOREGROUND, XSTATUS_PANEL_BACKGROUND);
	xstatus_create_gc(xc, get_button_gc(xc), win,
		XSTATUS_BUTTON_FG, XSTATUS_BUTTON_BG);
	setup_invert_gc();
	widget_start = toolbar::initialize(xc);
}
XStatus::~XStatus(void)
{
	xcb_destroy_window(xc, win);
	xcb_disconnect(xc);
}
void XStatus::run(void)
{
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
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
XStatusOptions::XStatusOptions(const XStatusOptions& obj)
{
	string s(obj.filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
XStatusOptions::~XStatusOptions(void)
{
	delete filename;
}
void XStatusOptions::set_filename(char * filename)
{
	delete this->filename;
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
