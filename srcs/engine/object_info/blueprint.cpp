
#include "engine/object_info/blueprint.hpp"

Blueprint::Blueprint()
	:	shader(NULL),
		mesh(NULL),
		material(NULL)
{
	return ;
}

Blueprint::~Blueprint()
{
	return ;
}

void
Blueprint::set_shader(const Shader &user_shader)
{
	this->shader = &user_shader;
	return ;
}

void
Blueprint::set_material(const Material &user_material)
{
	this->material = &user_material;
}

void
Blueprint::set_mesh(const Mesh &user_mesh)
{
	this->mesh = &user_mesh;
}

