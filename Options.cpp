// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Options.h"
#include <string>
#include "libjb/log.h"
using namespace std;
using namespace xstatus;
Options::Options(char * filename)
{
	LOG("Options constructor");
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
Options::Options(const Options& obj)
{
	LOG("Options copy constructor");
	string s(obj.filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
Options::~Options(void)
{
	LOG("Options destructor");
	delete filename;
}
void Options::set_filename(char * filename)
{
	delete this->filename;
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
