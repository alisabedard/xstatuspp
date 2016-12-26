// Copyright 2016, Jeffrey E. Bedard
#include <iostream>
#include <unistd.h>
#include "config.h"
#include "xstatus.h"
#include <cstring>
using namespace std;
using namespace xstatus;
class Main {
	XStatusOptions options;
	static void usage(void);
	public:
		Main(void);
		~Main(void);
		void parse(int argc, char ** argv);
		XStatusOptions * get_options(void) {return &options;}
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
			options.delay = atoi(optarg);
			break;
		case 'f':
			free(options.filename);
			options.filename = strdup(optarg);
			break;
		case 'h':
		default:
			usage();
		}
}
Main::Main(void)
{
	options.delay = 1;
	options.filename = strdup(XSTATUS_STATUS_FILE);
}
Main::~Main(void)
{
	free(options.filename);
}
int main(int argc, char ** argv)
{
	Main app;
	app.parse(argc, argv);
	XStatus::instance(app.get_options());
}
