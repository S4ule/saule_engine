
#include "engine_tool/file.hpp"

File::File()
	:	_fd(-1),
		_is_open(false)
{
	return ;
}

File::~File()
{
	if (this->_is_open == true)
	{
		close(this->_fd);
	}
	return ;
}


int
File::open_file(const std::string &file_path)
{
	this->_file_path = file_path;
	this->_fd = open(file_path.c_str(), O_RDONLY);
	if (this->_fd < 0)
	{
		SAULE_ENGINE_ERROR_LOG("fail to open file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	this->_is_open = true;
	if (this->read_all() == -1)
	{
		SAULE_ENGINE_ERROR_LOG("fail to read file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	return 0;
}

int
File::read_all()
{
	if (this->_is_open == false)
	{
		return -1;
	}
	ssize_t			read_value;
	std::vector<unsigned char>	buf;

	buf.resize(10240);

	this->_file_data.clear();
	read_value = read(this->_fd, buf.data(), 10239);
	if (read_value == -1)
	{
		return -1;
	}
	while (read_value != 0)
	{
		buf[read_value] = '\0';
		this->_file_data.insert(this->_file_data.end(), buf.begin(), buf.begin() + read_value);
		read_value = read(this->_fd, buf.data(), 10239);
		if (read_value == -1)
		{
			return -1;
		}
	}
	return 0;
}

int
File::get_next_line(std::string &line, size_t &offset)
{
	if (this->_is_open == false || offset > this->_file_data.size())
	{
		line = "";
		return -1;
	}
	size_t pos;

	line = "";
	for (pos = offset; pos < this->_file_data.size(); pos++)
	{
		if (this->_file_data[pos] == '\n')
		{
			break ;
		}
	}

	if (pos == this->_file_data.size())
	{
		line.insert(line.begin(), this->_file_data.begin() + offset, this->_file_data.end());
		offset = this->_file_data.size();
	}
	else
	{
		line.insert(line.begin(), this->_file_data.begin() + offset, this->_file_data.begin() + pos);
		offset = pos + 1;
		if (line[line.size() - 1] == '\r')
		{
			line.erase(line.size() - 1);
		}
	}
	return 0;
}

std::string
File::get_file_path() const
{
	return this->_file_path;
}


int
File::read_bytes(std::vector<unsigned char> &bytes, size_t &offset, size_t size)
{
	if (this->_is_open == false || offset + size > this->_file_data.size())
	{
		return -1;
	}

	bytes.insert(bytes.begin(), this->_file_data.begin() + offset, this->_file_data.begin() + offset + size);
	offset += size;
	return 0;
}

void
File::close_file()
{
	if (this->_is_open == true)
	{
		close(this->_fd);
	}
	this->_is_open = false;
	return ;
}

const std::vector<unsigned char> &
File::data() const
{
	return this->_file_data;
}

size_t
File::size() const
{
	return this->_file_data.size();
}