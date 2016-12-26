// Copyright 2016, Jeffrey E. Bedard
#include <iostream>
#include <unistd.h>
#include "config.h"
#include "xstatus.h"
using namespace std;
static void usage(void)
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
static void parse_command_line(int argc, char ** argv, XStatusOptions * o)
{
	int8_t opt;
	while((opt = getopt(argc, argv, "d:f:h")) != -1) {
		switch(opt) {
		case 'd':
			o->delay = atoi(optarg);
			break;
		case 'f':
			o->filename = optarg;
			break;
		case 'h':
		default:
			usage();
		}
	}
}
int main(int argc, char ** argv)
{
	char default_filename[] = XSTATUS_STATUS_FILE;
	XStatusOptions o = {.filename = default_filename,
		.delay = 1};
	parse_command_line(argc, argv, &o);
	xstatus::start(&o);
}
