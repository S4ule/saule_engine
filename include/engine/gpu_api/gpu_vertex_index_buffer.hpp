#ifndef __GPU_VERTEX_INDEX_BUFFER_HPP__
# define __GPU_VERTEX_INDEX_BUFFER_HPP__ 1

# include <glad/glad.h>
# include <stddef.h>
# include <vector>

# include "engine/object_info/mesh.hpp"
# include "saule_engine_define.hpp"
# include "saule_engine_debug_tool.hpp"

class GPU_Vertex_index_buffer
{
	private:
		unsigned int	_id;
		size_t			_count;

	public:
		GPU_Vertex_index_buffer();
		GPU_Vertex_index_buffer(const Mesh &mesh);
		virtual ~GPU_Vertex_index_buffer();

	public:
		int setup(const Mesh &mesh);

	public:
		int bind() const;
		int unbind() const;
		size_t count() const;
};

#endif /* __GPU_VERTEX_INDEX_BUFFER_HPP__ */