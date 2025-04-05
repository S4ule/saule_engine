
#include "engine/rendering/shader_buffer.hpp"

Shader_buffer::Shader_buffer()
{
	SAULE_ENGINE_INFO_LOG("create shader_buffer");
	return ;
}

Shader_buffer::Shader_buffer(const Shader *shader)
{
	SAULE_ENGINE_INFO_LOG("create shader_buffer");
	this->setup(shader);
	return ;
}

Shader_buffer::~Shader_buffer()
{
	SAULE_ENGINE_INFO_LOG("delete shader_buffer");
	return ;
}

int
Shader_buffer::setup(const Shader *shader)
{
	SAULE_ENGINE_INFO_LOG("setup shader_buffer");
	this->_program_buffer.setup(shader);
	return 0;
}

int
Shader_buffer::add_uniform_float(const std::string &name, const float &data)
{
	return this->_program_buffer.add_uniform_float(name, data);
}

int
Shader_buffer::add_uniform_float(const std::string &name, const Vector_2 &data)
{
	return this->_program_buffer.add_uniform_float(name, data);
}

int
Shader_buffer::add_uniform_float(const std::string &name, const Vector_3 &data)
{
	return this->_program_buffer.add_uniform_float(name, data);
}

int
Shader_buffer::add_uniform_float(const std::string &name, const Vector_4 &data)
{
	return this->_program_buffer.add_uniform_float(name, data);
}

int
Shader_buffer::add_uniform_int(const std::string &name, const int &data)
{
	return this->_program_buffer.add_uniform_int(name, data);
}

int
Shader_buffer::bind() const
{
	this->_program_buffer.bind();
	return 0;
}

int
Shader_buffer::unbind() const
{
	this->_program_buffer.unbind();
	return 0;
}