
#include "engine/gpu_api/gpu_vertex_buffer.hpp"

GPU_Vertex_buffer::GPU_Vertex_buffer()
{
	// SAULE_ENGINE_INFO_LOG("create vertex_buffer");
	GL_CALL(glGenVertexArrays(1, &(this->_vertex_array_buffer_id)));
	GL_CALL(glGenBuffers(1, &this->_vertex_buffer_id));
	return ;
}

GPU_Vertex_buffer::~GPU_Vertex_buffer()
{
	// SAULE_ENGINE_INFO_LOG("delete vertex_buffer");
	GL_CALL(glDeleteVertexArrays(1, &(this->_vertex_array_buffer_id)));
	GL_CALL(glDeleteBuffers(1, &this->_vertex_buffer_id));
	return ;
}

int
GPU_Vertex_buffer::setup(const Mesh &mesh)
{
	size_t offset;

	// SAULE_ENGINE_INFO_LOG("setup vertex_buffer");
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->_vertex_buffer_id));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices->size(), mesh.vertices->data(), GL_STATIC_DRAW));

	// Setup Vertex Array and layout
	offset = 0;
	GL_CALL(glBindVertexArray(this->_vertex_array_buffer_id));
	for (size_t i = 0; i < mesh.layout->format_list.size(); i++)
	{
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(glVertexAttribPointer(i, mesh.layout->format_list[i].count, mesh.layout->format_list[i].type, mesh.layout->format_list[i].normalize, mesh.layout->stride, (const void *)offset));
		offset += mesh.layout->format_list[i].count * mesh.layout->format_list[i].size;
	}
	return 0;
}

int
GPU_Vertex_buffer::bind() const
{
	//ENGINE_INFO_LOG("bind vertex_buffer");
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->_vertex_buffer_id));
	GL_CALL(glBindVertexArray(this->_vertex_array_buffer_id));
	return 0;
}

int
GPU_Vertex_buffer::unbind() const
{
	//ENGINE_INFO_LOG("unbind vertex_buffer");
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindVertexArray(0));
	return 0;
}
