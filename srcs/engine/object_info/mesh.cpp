
#include "engine/object_info/mesh.hpp"

size_t Mesh::_total_id = 0;

Mesh::Mesh()
{
	this->id = Mesh::_total_id;
	Mesh::_total_id += 1;
	return ;
}

Mesh::Mesh(const Mesh &ref)
{
	*this = ref;
	return ;
}

Mesh &
Mesh::operator=(const Mesh &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->vertices = ref.vertices;
	this->index = ref.index;
	this->layout = ref.layout;
	this->id = ref.id;
	return *this;
}

Mesh::~Mesh()
{
	return ;
}