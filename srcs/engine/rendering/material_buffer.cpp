
#include "engine/rendering/material_buffer.hpp"

Material_buffer::Material_buffer()
{
	SAULE_ENGINE_INFO_LOG("create material_buffer");
	return ;
}

Material_buffer::Material_buffer(const Material *material)
{
	SAULE_ENGINE_INFO_LOG("create material_buffer");
	this->setup(material);
	return ;
}

Material_buffer::~Material_buffer()
{
	SAULE_ENGINE_INFO_LOG("delete material_buffer");
	return ;
}

int
Material_buffer::setup(const Material *material)
{
	SAULE_ENGINE_INFO_LOG("setup material_buffer");
	this->_texture_buffer.setup(material);
	return 0;
}

int
Material_buffer::bind() const
{
	this->_texture_buffer.bind();
	return 0;
}

int
Material_buffer::unbind() const
{
	this->_texture_buffer.unbind();
	return 0;
}