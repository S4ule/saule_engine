
#include "engine/gpu_api/gpu_program_buffer.hpp"


GPU_Program_buffer::GPU_Program_buffer()
{
	//SAULE_ENGINE_INFO_LOG("create program_buffer");
	GL_CALL(this->_id = glCreateProgram());
	return ;
}

GPU_Program_buffer::GPU_Program_buffer(const Shader *shader)
{
	//SAULE_ENGINE_INFO_LOG("create program_buffer");
	GL_CALL(this->_id = glCreateProgram());
	this->setup(shader);
	return ;

}

GPU_Program_buffer::~GPU_Program_buffer()
{
	//SAULE_ENGINE_INFO_LOG("delete program_buffer");
	GL_CALL(glDeleteProgram(this->_id));
	return ;
}

int
GPU_Program_buffer::get_uniform_location(const std::string &name)
{
	std::map<std::string, int>::iterator	it;
	int										location;

	it = this->_uniform.find(name);
	if (it != this->_uniform.end())
	{
		location = it->second;
	}
	else
	{
		GL_CALL(location = glGetUniformLocation(this->_id, name.c_str()));
		this->_uniform[name] = location;
	}
	if (location == -1)
	{
		// ENGINE_WARNING_LOG("uniform is loaded but not used:");
		// ENGINE_WARNING_LOG(name.c_str());			
	}
	return location;
}

int
GPU_Program_buffer::add_uniform_float(const std::string &name, const float &data)
{
	GL_CALL(glUniform1f(get_uniform_location(name), data));
	return 0;
}

int
GPU_Program_buffer::add_uniform_float(const std::string &name, const Vector_2 &data)
{
	GL_CALL(glUniform2f(get_uniform_location(name), data.x, data.y));
	return 0;
}

int
GPU_Program_buffer::add_uniform_float(const std::string &name, const Vector_3 &data)
{
	GL_CALL(glUniform3f(get_uniform_location(name), data.x, data.y, data.z));
	return 0;
}

int
GPU_Program_buffer::add_uniform_float(const std::string &name, const Vector_4 &data)
{
	GL_CALL(glUniform4f(get_uniform_location(name), data.x, data.y, data.z, data.w));
	return 0;
}

int
GPU_Program_buffer::add_uniform_int(const std::string &name, const int &data)
{
	GL_CALL(glUniform1i(get_uniform_location(name), data));
	return 0;
}

int
GPU_Program_buffer::setup(const Shader *shader)
{
	int	err;

	// Compile shader
	//ENGINE_INFO_LOG("setup program_buffer");
	{
		std::map<unsigned int, std::string>::const_iterator it = shader->shader_src.begin();
		std::map<unsigned int, std::string>::const_iterator ite = shader->shader_src.end();
		size_t i = 0;

		this->_shader.resize(shader->shader_src.size());
		while (it != ite)
		{
			err = this->_shader[i].setup(it->second, it->first);
			if (err != 0)
			{
				this->_shader.clear();
				return -1;
			}
			++it;
			++i;
		}
	}

	// Attach Shader to program
	for (size_t i = 0; i < this->_shader.size(); i++)
	{
		GL_CALL(glAttachShader(this->_id, this->_shader[i].get_id()));
	}
	GL_CALL(glLinkProgram(this->_id));

	
	glGetProgramiv(this->_id, GL_LINK_STATUS, &err);
	if (err == 0)
	{
		char info_log[512];

		glGetProgramInfoLog(this->_id, 512, NULL, info_log);
		SAULE_ENGINE_ERROR_LOG("fail to link program_buffer");
		SAULE_ENGINE_ERROR_LOG(info_log);
		return -1;
	}

	// Clean shader after linking
	this->_shader.clear();

	GL_CALL(glValidateProgram(this->_id));
	glGetProgramiv(this->_id, GL_VALIDATE_STATUS, &err);
	if (err == 0)
	{
		char info_log[512];

		glGetProgramInfoLog(this->_id, 512, NULL, info_log);
		SAULE_ENGINE_ERROR_LOG("fail to validate program_buffer");
		SAULE_ENGINE_ERROR_LOG(info_log);
		return -1;
	}
	return 0;
}

int
GPU_Program_buffer::bind() const
{
	// SAULE_ENGINE_INFO_LOG("bind program_buffer");
	GL_CALL(glUseProgram(this->_id));
	return 0;
}

int
GPU_Program_buffer::unbind() const
{
	//ENGINE_INFO_LOG("unbind program_buffer");
	GL_CALL(glUseProgram(0));
	return 0;
}