// Copyright 2016, Jeffrey E. Bedard
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "config.h"
#include "Options.h"
#include "XStatus.h"
using namespace std;
using namespace xstatus;
namespace {
	static XStatus * xstatus_ptr;
	void signal_cb(int sig)
	{
		cerr << "Caught signal " << sig << '\n';
		if (xstatus_ptr) {
			delete xstatus_ptr;
			xstatus_ptr = nullptr;
		}
		exit(0);
	}
	void catch_signals()
	{
		signal(SIGHUP, &signal_cb);
		signal(SIGINT, &signal_cb);
		signal(SIGKILL, &signal_cb);
		signal(SIGTERM, &signal_cb);
	}
}
class Main : public Options {
	static void usage(void);
	public:
		Main(char * filename);
		void parse(int argc, char ** argv);
};
void Main::usage(void)
{
	cout << "DESCRIPTION: Simple X toolbar for minimalistic "
		"window managers.\n"
		"USAGE: xstatus [-d DELAY][-f FILE][-h]\n"
		"\t-d DELAY\tSet delay between status updates, in seconds.\n"
		"\t-f FILE\t\tSet FILE to be continuously polled "
		"and displayed.\n"
		"\t-h\t\tPrint this usage information.\n"
		"Copyright 2016, Jeffrey E. Bedard <jefbed@gmail.com>\n"
		"Project page: https://github.com/jefbed/xstatus\n";
	exit(1);
}
void Main::parse(int argc, char ** argv)
{
	char o;
	while ((o = getopt(argc, argv, "d:f:h:")) >= 0)
		switch (o) {
		case 'd':
			delay = atoi(optarg);
			break;
		case 'f':
			set_filename(optarg);
			break;
		case 'h':
		default:
			usage();
		}
}
Main::Main(char * filename) : Options(filename) {}
int main(int argc, char ** argv)
{
	char f[] = XSTATUS_STATUS_FILE;
	Main app(f);
	app.parse(argc, argv);
	xstatus_ptr = new XStatus(app);
	catch_signals();
	xstatus_ptr->run();
	delete xstatus_ptr;
	return 0;
}
