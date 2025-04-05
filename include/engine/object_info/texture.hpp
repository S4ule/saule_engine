#ifndef __TEXTURE_HPP__
# define __TEXTURE_HPP__

# include <string>

# include "stbi/stb_image.hpp"
# include "saule_engine_debug_tool.hpp"

class Texture
{
	public:
		stbi_uc	*data_buffer;
		int		width;
		int		hight;
		int		bpp;

	public:
		Texture();
		Texture(const std::string &file_path);
		~Texture();

	public:
		int	import_file(const std::string &file_path);
};

#endif /* __TEXTURE_HPP__ */