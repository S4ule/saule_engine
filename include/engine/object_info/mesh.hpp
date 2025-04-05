#ifndef __MESH_HPP__
# define __MESH_HPP__ 1

# include <vector>

# include "engine/object_info/layout.hpp"
# include "engine_tool/wf_mesh.hpp"

class Mesh
{
	public:
		size_t	id;

	private:
		static size_t	_total_id;

	public:
		const std::vector<float>		*vertices;
		const std::vector<unsigned int>	*index;
		const Layout					*layout;

	public:
		Mesh();
		Mesh(const Mesh &ref);
		Mesh &operator=(const Mesh &ref);
		~Mesh();
};

#endif /* __MESH_HPP__ */