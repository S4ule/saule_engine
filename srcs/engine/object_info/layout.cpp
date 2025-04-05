
#include "engine/object_info/layout.hpp"


Layout::Layout()
	:	stride(0)
{
	return ;
}

Layout::~Layout()
{
	return ;
}

void
Layout::add_layout(size_t count, unsigned int type, unsigned int size, unsigned int normalize)
{
	Layout::Format format;

	format.count = count;
	format.type = type;
	format.size = size;
	format.normalize = normalize;
	this->format_list.push_back(format);
	this->stride += size * count;
	return ;
}

void
Layout::clear()
{
	this->format_list.clear();
	this->stride = 0;
}