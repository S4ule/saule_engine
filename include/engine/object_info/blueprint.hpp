#ifndef __BLUEPRINT_HPP__
# define __BLUEPRINT_HPP__ 1

# include <vector>

# include "engine/object_info/shader.hpp"
# include "engine/object_info/mesh.hpp"
# include "engine/object_info/material.hpp"

class Blueprint
{
	public:
		const Shader	*shader;
		const Mesh		*mesh;
		const Material	*material;

	public:
		Blueprint();
		~Blueprint();

	public:
		void set_shader(const Shader &user_shader);
		void set_mesh(const Mesh &user_mesh);
		void set_material(const Material &user_material);
};

#endif /* __BLUEPRINT_HPP__ */