// Copyright 2017, Alisa Bedard <alisabedard@gmail.com>
#include "Options.h"
#include <string>
#include "libjb/cpp.h"
#include "libjb/log.h"
using namespace std;
using namespace xstatus;
int Options::instances = 0;
Options::Options(char * filename)
{
	JB_LOG_ADD(Options, instances);
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
Options::Options(const Options& obj)
{
	JB_LOG_ADD(Options, instances);
	string s(obj.filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
Options::~Options(void)
{
	JB_LOG_DEL(Options, instances);
	delete filename;
}
void Options::set_filename(char * filename)
{
	JB_LOG_OP(Options, "set_filename()");
	delete this->filename;
	string s(filename);
	this->filename = new char[s.size()];
	s.copy(this->filename, s.size());
}
