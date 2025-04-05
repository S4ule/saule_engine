#ifndef __GPU_PROGRAM_BUFFER_HPP__
# define __GPU_PROGRAM_BUFFER_HPP__ 1

# include <map>
# include <string>
# include <vector>

# include "engine/object_info/shader.hpp"
# include "engine_tool/vector_2.hpp"
# include "engine_tool/vector_3.hpp"
# include "engine_tool/vector_4.hpp"
# include "engine/gpu_api/gpu_shader_buffer.hpp"
# include "saule_engine_debug_tool.hpp"

class GPU_Program_buffer
{
	private:
		unsigned int	_id;

		std::map<std::string, int>		_uniform;
		std::vector<GPU_Shader_buffer>	_shader;

	public:
		GPU_Program_buffer();
		GPU_Program_buffer(const Shader *shader);
		virtual ~GPU_Program_buffer();

	private:
		int get_uniform_location(const std::string &name);

	public:
		int add_uniform_float(const std::string &name, const float &data);
		int add_uniform_float(const std::string &name, const Vector_2 &data);
		int add_uniform_float(const std::string &name, const Vector_3 &data);
		int add_uniform_float(const std::string &name, const Vector_4 &data);
		int add_uniform_int(const std::string &name, const int &data);

	public:
		int setup(const Shader *shader);

	public:
		int bind() const;
		int unbind() const;	
};

#endif /* __GPU_PROGRAM_BUFFER_HPP__ */