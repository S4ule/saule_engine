
#include "engine/object_info/texture.hpp"

Texture::Texture()
	:	data_buffer(NULL),
		width(0),
		hight(0),
		bpp(0)
{
	return ;
}

Texture::Texture(const std::string &file_path)
{
	this->import_file(file_path);
	return ;
}

Texture::~Texture()
{
	if (this->data_buffer != NULL)
	{
		stbi_image_free(this->data_buffer);
	}
	return ;
}

int
Texture::import_file(const std::string &file_path)
{
	if (this->data_buffer != NULL)
	{
		stbi_image_free(this->data_buffer);
	}

	//stbi_set_flip_vertically_on_load(1);
	this->data_buffer = stbi_load(file_path.c_str(), &(this->width), &(this->hight), &(this->bpp), 4);
	if (this->data_buffer == NULL)
	{
		SAULE_ENGINE_ERROR_LOG("fail to load texture file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	SAULE_ENGINE_INFO_LOG("import texture file:");
	SAULE_ENGINE_INFO_LOG(file_path.c_str());
	return 0;
}