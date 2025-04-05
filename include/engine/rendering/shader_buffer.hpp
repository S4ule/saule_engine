#ifndef __SHADER_BUFFER_HPP__
# define __SHADER_BUFFER_HPP__ 1

# include <vector>

# include "engine/object_info/shader.hpp"
# include "engine/gpu_api/gpu_program_buffer.hpp"

class Shader_buffer
{
	public:
		GPU_Program_buffer	_program_buffer;

	public:
		Shader_buffer();
		Shader_buffer(const Shader *shader);
		~Shader_buffer();

	public:
		int setup(const Shader *shader);
		int add_uniform_float(const std::string &name, const float &data);
		int add_uniform_float(const std::string &name, const Vector_2 &data);
		int add_uniform_float(const std::string &name, const Vector_3 &data);
		int add_uniform_float(const std::string &name, const Vector_4 &data);
		int add_uniform_int(const std::string &name, const int &data);

	public:
		int bind() const;
		int unbind() const;
};

#endif /* __SHADER_BUFFER_HPP__ */