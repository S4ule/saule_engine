#ifndef __FILE_READER__
# define __FILE_READER__

# include <string>
# include <vector>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "saule_engine_debug_tool.hpp"

class File
{
	private:
		int		_fd;
		bool	_is_open;
		std::vector<unsigned char>	_file_data;
		std::string		_file_path;

	public:
		File();
		virtual ~File();

	public:
		int open_file(const std::string &file_path);
		int	read_all();
		int get_next_line(std::string &line, size_t &offset);
		std::string get_file_path() const;
		int read_bytes(std::vector<unsigned char> &bytes, size_t &offset, size_t size);
		void close_file();
		const std::vector<unsigned char> &data() const;
		size_t size() const;
};

#endif	/* __FILE_READER__ */