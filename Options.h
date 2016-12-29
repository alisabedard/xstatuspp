// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSPP_OPTIONS_H
#define XSPP_OPTIONS_H
namespace xstatus {
	class XStatusOptions {
		protected:
			unsigned short delay = 1;
		public:
			XStatusOptions(char * filename);
			XStatusOptions(const XStatusOptions& obj);
			~XStatusOptions(void);
			void set_filename(char * filename);
			unsigned short get_delay(void) { return delay; }
			char * filename;
	};
}
#endif//!XSPP_OPTIONS_H

