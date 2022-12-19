// Copyright 2016, Alisa Bedard
#include "Statusbar.h"
#include <fstream>
#include <iostream>
#include "config.h"
using namespace std;
using namespace xstatus;
namespace {
	class StatusBuffer : public Buffer {
		private:
			const char * filename;
			void warn_no_data(void);
			ssize_t poll_status_file(void);
		public:
			bool poll(void);
			StatusBuffer(const char * filename)
				: Buffer(XSTATUS_CONST_BUFFER_SIZE),
				filename(filename)
		{}
	};
	void StatusBuffer::warn_no_data(void)
	{
		static bool warned;
		if (warned)
			return;
		cerr << "No data in status file " << filename << '\n';
		warned = true;
	}
	ssize_t StatusBuffer::poll_status_file(void)
	{
		ifstream f;
		string s;
		f.open(filename);
		if (f.rdstate())
			return -1; // Could not open file.
		getline(f, s);
		f.close();
		return s.copy(buffer, get_max_size());
	}
	bool StatusBuffer::poll(void)
	{
		const ssize_t s = poll_status_file();
		if (s <= 0) {
			set_size(0);
			warn_no_data();
			return false;
		}
		set_size(s);
		return true;
	}
}
class StatusWidget : public Widget {
	private:
		FontSize f;
	public:
		void draw(void)
		{
			enum { PAD = XSTATUS_CONST_PAD << 1 };
			xcb_image_text_8(*this, buffer, main_window,
				get_gc(), offset + PAD, f.height, buffer);
			width = f.width * buffer + PAD + PAD;
		}
		StatusWidget(xcb_connection_t * xc, Buffer & b,
			const Font & font, const int offset)
			: Widget(xc, b, font), f(font.get_size())
		{
			this->offset = offset;
		}
};
Statusbar::Statusbar(xcb_connection_t * xc, const Font & font,
	const int x, const char * filename)
{
	StatusBuffer * sb = new StatusBuffer(filename);
	buffer = sb;
	widget = new StatusWidget(xc, *buffer, font, x);
	if (sb->poll()) // success
		widget->draw();
}
