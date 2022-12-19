// Copyright 2017, Alisa Bedard
#ifndef XSTATUS_WINDOW_H
#define XSTATUS_WINDOW_H
#include <xcb/xcb.h>
namespace xstatus {
  class XData;
  class Window {
  private:
  xcb_connection_t * xc;
  bool created = false;
  protected:
  xcb_window_t window;
  xcb_rectangle_t geometry;
  public:
  Window(xcb_connection_t * xc);
  ~Window(void);
  void create(xcb_window_t const parent,
    xcb_rectangle_t const & geometry,
    uint8_t const border_width,
    uint32_t const value_mask,
    uint32_t const * value_list);
  operator xcb_window_t(void) const { return window; }
  // Keep this accessor for subclasses:
  xcb_window_t get_window(void) const { return window; }
  static xcb_window_t create_main_window(XData * X);
  void map(void);
  void unmap(void);
  void destroy(void);
  };
}
#endif//!XSTATUS_WINDOW_H
