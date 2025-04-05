#ifndef __GPU_SHADER_BUFFER_HPP__
# define __GPU_SHADER_BUFFER_HPP__ 1

# include <glad/glad.h>
# include <string>

# include "engine/object_info/shader.hpp"
# include "saule_engine_define.hpp"
# include "saule_engine_debug_tool.hpp"

class GPU_Shader_buffer
{
	private:
		unsigned int	_id;
		bool			_is_create;

	public:
		GPU_Shader_buffer();
		GPU_Shader_buffer(std::string shader_src, unsigned int shader_type);
		virtual ~GPU_Shader_buffer();

	public:
		int setup(std::string shader_src, unsigned int shader_type);

	public:
		unsigned int get_id() const;
};

#endif /* __GPU_SHADER_BUFFER_HPP__ */