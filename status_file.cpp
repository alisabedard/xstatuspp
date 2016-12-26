// Copyright 2016, Jeffrey E. Bedard
#include "status_file.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/file.h"
#include "libjb/util.h"
}
#include <cstdio>
#include <sys/stat.h> // include per man page of fchmod()
#include <unistd.h> // include per man page of read()
#include "config.h"
#include "font.h"
#include "xdata.h"
static ssize_t poll_status_file(const char *  filename,
	char *  buf)
{
	fd_t fd = jb_open(filename, O_RDONLY | O_CREAT);
	if (fd < 0)
		return -1;
	fchmod(fd, 0600);
	ssize_t r = read(fd, buf, XSTATUS_CONST_BUFFER_SIZE);
	jb_check(r != -1, "Could not read status file");
	close(fd);
	return r;
}
static void warn_no_data(const char *  fn)
{
	static bool warned;
	if (warned)
		return;
	fprintf(stderr, "No data in status file: %s\n", fn);
	warned = true;
}
static void draw_text(xcb_connection_t *  xc, const int16_t x,
	const int8_t len, char * buf)
{
	xcb_image_text_8(xc, len, xstatus::get_window(xc),
		xstatus::get_gc(xc), x + (XSTATUS_CONST_PAD << 1),
		xstatus::get_font_size().h, buf);
}
static uint16_t get_offset(const uint16_t x, const ssize_t len)
{
	return xstatus::get_font_size().w * len + x
		+ (XSTATUS_CONST_PAD << 2);
}
// Returns offset for next widget
uint16_t draw_status_file(xcb_connection_t * xc,
	const uint16_t x_offset,
	const char *  filename)
{
	char buf[XSTATUS_CONST_BUFFER_SIZE];
	const ssize_t s = poll_status_file(filename, buf) - 1;
	if (s <= 0) { // empty or error
		warn_no_data(filename);
		return x_offset + XSTATUS_CONST_PAD;
	}
	draw_text(xc, x_offset, s, buf);
	return get_offset(x_offset, s);
}
