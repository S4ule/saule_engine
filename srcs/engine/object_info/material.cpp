
#include "engine/object_info/material.hpp"

size_t Material::_total_id = 0;

Material::Material()
	:	texture(NULL),
		specular_highlights(SAULE_ENGINE_DEFAULT_SPECULAR_HIGHLIGHTS),
		ambient_color(SAULE_ENGINE_DEFAULT_AMBIENT_COLOR),
		diffuse_color(SAULE_ENGINE_DEFAULT_DIFFUSE_COLOR),
		specular_color(SAULE_ENGINE_DEFAULT_SPECULAR_COLOR),
		emissive_color(SAULE_ENGINE_DEFAULT_EMISSIVE_COLOR),
		optical_density(SAULE_ENGINE_DEFAULT_OPTICAL_DENSITY),
		dissolve(SAULE_ENGINE_DEFAULT_DISSOLVE)
{
	this->id = Material::_total_id;
	Material::_total_id += 1;
	return ;
}

Material::~Material()
{
	return ;
}

void
Material::set_texture(Texture &user_texture)
{
	this->texture = &user_texture;
	return ;
}