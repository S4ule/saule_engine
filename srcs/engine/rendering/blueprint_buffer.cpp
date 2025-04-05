
#include "engine/rendering/blueprint_buffer.hpp"

std::map<size_t, Mesh_buffer *>		Blueprint_buffer::_mesh_buffer;		// size_t = id
std::map<size_t, Material_buffer *>	Blueprint_buffer::_material_buffer;	// size_t = id
std::map<size_t, Shader_buffer *>	Blueprint_buffer::_shader_buffer;	// size_t = id

Blueprint_buffer::Blueprint_buffer()
{
	return ;
}

Blueprint_buffer::Blueprint_buffer(const Blueprint &blueprint)
{
	this->setup(blueprint);
	return ;
}

Blueprint_buffer::~Blueprint_buffer()
{
	return ;
}

int
Blueprint_buffer::setup(const Blueprint &blueprint)
{
	if (blueprint.mesh == NULL || blueprint.material == NULL || blueprint.shader == NULL)
	{
		SAULE_ENGINE_WARNING_LOG("fail to create Blueprint_buffer:");
		if (blueprint.mesh == NULL)
		{
			SAULE_ENGINE_WARNING_LOG("blueprint.mesh is missing");
		}
		if (blueprint.material == NULL)
		{
			SAULE_ENGINE_WARNING_LOG("blueprint.material is missing");
		}
		if (blueprint.shader == NULL)
		{
			SAULE_ENGINE_WARNING_LOG("blueprint.shader is missing");
		}
		return -1;
	}
	this->_mesh_id = blueprint.mesh->id;
	this->_material_id = blueprint.material->id;
	this->_shader_id = blueprint.shader->id;

	// Check if not already buffered, and setup if needed
	if (Blueprint_buffer::_mesh_buffer.find(this->_mesh_id) == Blueprint_buffer::_mesh_buffer.end())
	{
		Mesh_buffer *ptr = new Mesh_buffer();

		Blueprint_buffer::_mesh_buffer[this->_mesh_id] = ptr;
		ptr->setup(blueprint.mesh);
	}
	if (Blueprint_buffer::_material_buffer.find(this->_material_id) == Blueprint_buffer::_material_buffer.end())
	{
		Material_buffer *ptr = new Material_buffer();

		Blueprint_buffer::_material_buffer[this->_material_id] = ptr;
		ptr->setup(blueprint.material);
	}
	if (Blueprint_buffer::_shader_buffer.find(this->_shader_id) == Blueprint_buffer::_shader_buffer.end())
	{
		Shader_buffer *ptr = new Shader_buffer();

		Blueprint_buffer::_shader_buffer[this->_shader_id] = ptr;
		ptr->setup(blueprint.shader);
	}
	return 0;
}

int
Blueprint_buffer::add_uniform_float(const std::string &name, const float &data)
{
	return Blueprint_buffer::_shader_buffer[this->_shader_id]->add_uniform_float(name, data);
}

int
Blueprint_buffer::add_uniform_float(const std::string &name, const Vector_2 &data)
{
	return Blueprint_buffer::_shader_buffer[this->_shader_id]->add_uniform_float(name, data);
}

int
Blueprint_buffer::add_uniform_float(const std::string &name, const Vector_3 &data)
{
	return Blueprint_buffer::_shader_buffer[this->_shader_id]->add_uniform_float(name, data);
}

int
Blueprint_buffer::add_uniform_float(const std::string &name, const Vector_4 &data)
{
	return Blueprint_buffer::_shader_buffer[this->_shader_id]->add_uniform_float(name, data);
}

int
Blueprint_buffer::add_uniform_int(const std::string &name, const int &data)
{
	return Blueprint_buffer::_shader_buffer[this->_shader_id]->add_uniform_int(name, data);
}

int
Blueprint_buffer::bind() const
{
	Blueprint_buffer::_mesh_buffer[this->_mesh_id]->bind();
	Blueprint_buffer::_material_buffer[this->_material_id]->bind();
	Blueprint_buffer::_shader_buffer[this->_shader_id]->bind();
	return 0;
}

int
Blueprint_buffer::unbind() const
{
	Blueprint_buffer::_mesh_buffer[this->_mesh_id]->unbind();
	Blueprint_buffer::_material_buffer[this->_material_id]->unbind();
	Blueprint_buffer::_shader_buffer[this->_shader_id]->unbind();
	return 0;
}

size_t
Blueprint_buffer::count() const
{
	return Blueprint_buffer::_mesh_buffer[this->_mesh_id]->count();
}

void
Blueprint_buffer::clean()
{
	std::map<size_t, Mesh_buffer *>::iterator mesh_it = Blueprint_buffer::_mesh_buffer.begin();
	std::map<size_t, Material_buffer *>::iterator material_it = Blueprint_buffer::_material_buffer.begin();
	std::map<size_t, Shader_buffer *>::iterator shader_it = Blueprint_buffer::_shader_buffer.begin();

	std::map<size_t, Mesh_buffer *>::iterator mesh_ite = Blueprint_buffer::_mesh_buffer.end();
	std::map<size_t, Material_buffer *>::iterator material_ite = Blueprint_buffer::_material_buffer.end();
	std::map<size_t, Shader_buffer *>::iterator shader_ite = Blueprint_buffer::_shader_buffer.end();

	while (mesh_it != mesh_ite)
	{
		delete mesh_it->second;
		++mesh_it;
	}

	while (material_it != material_ite)
	{
		delete material_it->second;
		++material_it;
	}

	while (shader_it != shader_ite)
	{
		delete shader_it->second;
		++shader_it;
	}
	return ;
}