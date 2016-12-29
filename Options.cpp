// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Options.h"
#include <string>
#include "libjb/log.h"
using namespace std;
using namespace xstatus;
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
