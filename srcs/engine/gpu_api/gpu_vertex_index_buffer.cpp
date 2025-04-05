
#include "engine/gpu_api/gpu_vertex_index_buffer.hpp"

GPU_Vertex_index_buffer::GPU_Vertex_index_buffer()
{
	//ENGINE_INFO_LOG("create vertex_index_buffer");
	GL_CALL(glGenBuffers(1, &(this->_id)));
	return ;
}

GPU_Vertex_index_buffer::GPU_Vertex_index_buffer(const Mesh &mesh)
{
	//ENGINE_INFO_LOG("create vertex_index_buffer");
	GL_CALL(glGenBuffers(1, &(this->_id)));
	setup(mesh);
	return ;
}

GPU_Vertex_index_buffer::~GPU_Vertex_index_buffer()
{
	//ENGINE_INFO_LOG("delete vertex_index_buffer");
	GL_CALL(glDeleteBuffers(1, &(this->_id)));
	return ;
}

int
GPU_Vertex_index_buffer::setup(const Mesh &mesh)
{
	//ENGINE_INFO_LOG("setup vertex_index_buffer");
	this->_count = mesh.index->size();
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SAULE_ENGINE_UINT) * mesh.index->size(), mesh.index->data(), GL_STATIC_DRAW));
	return 0;
}

int
GPU_Vertex_index_buffer::bind() const
{
	//ENGINE_INFO_LOG("bind vertex_index_buffer");
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id));
	return 0;
}

int
GPU_Vertex_index_buffer::unbind() const
{
	//ENGINE_INFO_LOG("unbind vertex_index_buffer");
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	return 0;
}

size_t
GPU_Vertex_index_buffer::count() const
{
	return this->_count;
}