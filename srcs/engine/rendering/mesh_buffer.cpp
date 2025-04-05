
#include "engine/rendering/mesh_buffer.hpp"

Mesh_buffer::Mesh_buffer()
{
	SAULE_ENGINE_INFO_LOG("create mesh_buffer");
	return ;
}

Mesh_buffer::Mesh_buffer(const Mesh *mesh)
{
	SAULE_ENGINE_INFO_LOG("create mesh_buffer");
	this->setup(mesh);
	return ;
}


Mesh_buffer::~Mesh_buffer()
{
	SAULE_ENGINE_INFO_LOG("delete mesh_buffer");
	return ;
}

int
Mesh_buffer::setup(const Mesh *mesh)
{
	SAULE_ENGINE_INFO_LOG("setup mesh_buffer");
	this->_vertex_buffer.setup(*mesh);
	this->_vertex_index_buffer.setup(*mesh);
	return 0;
}

int
Mesh_buffer::bind() const
{
	this->_vertex_buffer.bind();
	this->_vertex_index_buffer.bind();
	return 0;
}

int
Mesh_buffer::unbind() const
{
	this->_vertex_buffer.unbind();
	this->_vertex_index_buffer.unbind();
	return 0;
}

size_t
Mesh_buffer::count() const
{
	return this->_vertex_index_buffer.count();
}