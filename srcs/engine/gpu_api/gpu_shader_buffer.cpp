
#include "engine/gpu_api/gpu_shader_buffer.hpp"


GPU_Shader_buffer::GPU_Shader_buffer()
	:	_is_create(false)
{
	return ;
}

GPU_Shader_buffer::GPU_Shader_buffer(const std::string shader_src, const unsigned int shader_type)
	:	_is_create(false)
{
	this->setup(shader_src, shader_type);
	return ;
}

GPU_Shader_buffer::~GPU_Shader_buffer()
{
	if (this->_is_create == true)
	{
		//ENGINE_INFO_LOG("delete shader_buffer");
		GL_CALL(glDeleteShader(this->_id));
		this->_is_create = false;
	}
	return ;
}

int
GPU_Shader_buffer::setup(std::string shader_src, unsigned int shader_type)
{
	const char *src;
	int			err;

	if (this->_is_create == true)
	{
		//ENGINE_INFO_LOG("delete shader_buffer");
		GL_CALL(glDeleteShader(this->_id));
		this->_is_create = false;
	}

	//ENGINE_INFO_LOG("create shader_buffer");
	// Complie Shader
	src = shader_src.c_str();

	GL_CALL(this->_id = glCreateShader(shader_type));
	GL_CALL(glShaderSource(this->_id, 1, &src, NULL));
	GL_CALL(glCompileShader(this->_id));
	this->_is_create = true;

	// check error
	GL_CALL(glGetShaderiv(this->_id, GL_COMPILE_STATUS, &err));
	if (err == GL_FALSE)
	{
		char info_log[512];

		GL_CALL(glGetShaderInfoLog(this->_id, 512, NULL, info_log));
		SAULE_ENGINE_ERROR_LOG("fail to compile shader:");
		SAULE_ENGINE_ERROR_LOG(info_log);

		//ENGINE_INFO_LOG("delete shader_buffer");
		GL_CALL(glDeleteShader(this->_id));
		this->_is_create = false;

		return -1;
	}
	return 0;
}

unsigned int
GPU_Shader_buffer::get_id() const
{
	return this->_id;
}