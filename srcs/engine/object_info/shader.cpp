
#include "engine/object_info/shader.hpp"

size_t Shader::_total_id = 0;

Shader::Shader()
{
	this->id = Shader::_total_id;
	Shader::_total_id += 1;
	return ;
}

Shader::~Shader()
{
	return ;
}

int
Shader::import_file(const std::string &file_path, unsigned int shader_type)
{
	File	file;
	int		err;

	SAULE_ENGINE_INFO_LOG("import shader file:");
	SAULE_ENGINE_INFO_LOG(file_path.c_str());

	err = file.open_file(file_path);
	if (err == -1)
	{
		SAULE_ENGINE_ERROR_LOG("can't use shader file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	this->shader_src[shader_type].insert(this->shader_src[shader_type].begin(), file.data().begin(), file.data().end());
	file.close_file();
	return 0;
}