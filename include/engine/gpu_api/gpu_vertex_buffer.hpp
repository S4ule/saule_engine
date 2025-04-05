#ifndef __GPU_VERTEX_BUFFER_HPP__
# define __GPU_VERTEX_BUFFER_HPP__ 1

# include <glad/glad.h>
# include <vector>

# include "engine/object_info/mesh.hpp"
# include "saule_engine_debug_tool.hpp"

class GPU_Vertex_buffer
{
	private:
		unsigned int	_vertex_buffer_id;
		unsigned int	_vertex_array_buffer_id;

	public:
		GPU_Vertex_buffer();
		virtual ~GPU_Vertex_buffer();

	public:
		int setup(const Mesh &mesh);

	public:
		int bind() const;
		int unbind() const;
};

#endif /* __GPU_VERTEX_BUFFER_HPP__ */