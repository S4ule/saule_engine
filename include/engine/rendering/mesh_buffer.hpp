#ifndef __MESH_BUFFER_HPP__
# define __MESH_BUFFER_HPP__ 1

# include <stddef.h>

# include "engine/object_info/mesh.hpp"
# include "engine/gpu_api/gpu_vertex_buffer.hpp"
# include "engine/gpu_api/gpu_vertex_index_buffer.hpp"

class Mesh_buffer
{
	private:
		GPU_Vertex_buffer		_vertex_buffer;
		GPU_Vertex_index_buffer	_vertex_index_buffer;

	public:
		Mesh_buffer();
		Mesh_buffer(const Mesh *mesh);
		virtual ~Mesh_buffer();

	public:
		int setup(const Mesh *mesh);

	public:
		int bind() const;
		int unbind() const;

		size_t count() const;
};

#endif /* __MESH_BUFFER_HPP__ */