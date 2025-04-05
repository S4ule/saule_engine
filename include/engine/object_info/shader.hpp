#ifndef __SHADER_HPP__
# define __SHADER_HPP__

# include <string>
# include <map>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "engine_tool/file.hpp"
# include "saule_engine_debug_tool.hpp"

class Shader
{
	public:
		std::map<unsigned int, std::string>	shader_src; // unsigned int = shader_type / std::string = shader_src
	
	public:
		size_t	id;

	private:
		static size_t	_total_id;

	public:
		Shader();
		virtual ~Shader();

	public:
		int import_file(const std::string &file_path, unsigned int shader_type);
};

#endif /* __SHADER_HPP__ */