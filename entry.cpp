#include "entry.h"



entry::entry()
{
}

entry::entry(const entry &in)
{
	this->filename = in.filename;
}

entry::entry(string in)
{
	filename = in;
}

