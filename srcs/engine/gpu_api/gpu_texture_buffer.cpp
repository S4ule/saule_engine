
#include "engine/gpu_api/gpu_texture_buffer.hpp"

GPU_Texture_buffer::GPU_Texture_buffer()
	:	_id(0),
		_slot(0),
		_is_create(false)
{
	return ;
}

GPU_Texture_buffer::GPU_Texture_buffer(const Material *material)
	:	_id(0),
		_slot(0),
		_is_create(false)
{
	this->setup(material);
	return ;
}

GPU_Texture_buffer::~GPU_Texture_buffer()
{
	if (this->_is_create == true)
	{
		GL_CALL(glDeleteTextures(1, &(this->_id)));
	}
	return ;
}

int
GPU_Texture_buffer::setup(const Material *material)
{
	if (material == NULL || material->texture == NULL)
	{
		return -1;
	}

	if (this->_is_create == true)
	{
		GL_CALL(glDeleteTextures(1, &(this->_id)));
		this->_is_create = false;
	}

	// Create GL Texture
	GL_CALL(glGenTextures(1, &(this->_id)));
	GL_CALL(glActiveTexture(GL_TEXTURE0 + this->_slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->_id));

	// Setup default texture behavior
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	// GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, material->texture->width, material->texture->hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, material->texture->data_buffer));
	//GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	
	this->_is_create = true;
	return 0;
}

unsigned int
GPU_Texture_buffer::slot(void) const
{
	return this->_slot;
}

void
GPU_Texture_buffer::set_slot(unsigned int slot)
{
	this->_slot = slot;
	return ;
}

void
GPU_Texture_buffer::bind(void) const
{
	GL_CALL(glActiveTexture(GL_TEXTURE0 + this->_slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, this->_id));
	return ;
}

void
GPU_Texture_buffer::unbind(void) const
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	return ;
}