// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSPP_OPTIONS_H
#define XSPP_OPTIONS_H
namespace xstatus {
	class Options {
		protected:
			unsigned short delay = 1;
		public:
			Options(char * filename);
			Options(const Options& obj);
			~Options(void);
			void set_filename(char * filename);
			unsigned short get_delay(void) { return delay; }
			char * filename;
	};
}
#endif//!XSPP_OPTIONS_H

